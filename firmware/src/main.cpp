#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

// Also based on https://www.geeksforgeeks.org/udp-server-client-implementation-c/#
/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <iostream>
#include "esp_camera.h"
#include <WiFiManager.h>

using namespace std;

WiFiManager wifiManager;

#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"
#include <optional>
#include <thread>
#include <lwip/sockets.h>
void startCameraServer();

std::optional<std::string> remote_ip;
int sock_fd;

int my_bind(uint32_t port)
{
  int sockfd;
  const char *hello = "Hello from server";
  struct sockaddr_in servaddr;

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(port);

  // Bind the socket with the server address
  if (bind(sockfd, (const struct sockaddr *)&servaddr,
           sizeof(servaddr)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  return sockfd;
}

void setup()
{
  cout << "Starting" << endl;

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  // init with high specs to pre-allocate larger buffers
  config.frame_size = FRAMESIZE_SVGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    printf("Camera init failed with error 0x%x", err);
    cout << endl;
    return;
  }

  sensor_t *s = esp_camera_sensor_get();

  cout << "OV3660" << endl;
  s->set_vflip(s, 1);          // flip it back
  s->set_brightness(s, 4);     // up the blightness just a bit
  s->set_saturation(s, 2);     // lower the saturation
  s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)  server.begin();
  s->set_colorbar(s, 0);       // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)  server.begin();

  // drop down frame size for higher initial frame rate
  // s->set_framesize(s, FRAMESIZE_QVGA);

  WiFiManager wm;                                         // global wm instance
  bool res = wm.autoConnect("AutoConnectAP", "password"); // password protected ap
  if (!res)
  {
    Serial.println("Failed to connect or hit timeout");
    ESP.restart();
  }
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    cout << ".";
  }
  cout << "" << endl;
  cout << "WiFi connected" << endl;
  cout << ("About to set pinmode\n") << endl;

  auto raw_address = WiFi.localIP();
  cout << (int)raw_address[0] << "." << (int)raw_address[1] << "." << (int)raw_address[2] << "." << (int)raw_address[3] << endl;
  pinMode(4, OUTPUT); // Specify that LED pin is output
  sock_fd = my_bind(61235);
}

String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
// https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
inline bool ends_with(std::string const &value, std::string const &ending)
{
  if (ending.size() > value.size())
    return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::optional<std::string> get_remote_ip(int sockfd, uint32_t remote_port)
{
  // https://www.geeksforgeeks.org/udp-server-client-implementation-c/
  struct sockaddr_in cliaddr;
  memset(&cliaddr, 0, sizeof(cliaddr));

  socklen_t len;
  int n;

  const int buf_size = 8;
  char buffer[buf_size];

  len = sizeof(cliaddr); // len is value/result
  n = recvfrom(sockfd, (char *)buffer, buf_size,
               MSG_DONTWAIT, (struct sockaddr *)&cliaddr,
               &len);
  if (n == -1 && errno != EAGAIN)
  {
    cout << "Error: " << (std::to_string(errno)) << endl;
    exit(-1);
  }
  else if (n != -1)
  {
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    string msg = "OK";
    cliaddr.sin_port = htons(remote_port);
    for (int i = 0; i < 100; i++)
    {
      int a = sendto(sockfd, (const char *)msg.c_str(), msg.size(),
                     0, (const struct sockaddr *)&cliaddr,
                     len);
    }
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &cliaddr.sin_addr, str, INET_ADDRSTRLEN);

    return std::string(str);
  }
  return std::nullopt;
}

void send_camera_data(int sock_fd, std::string addr_string, uint32_t port, uint8_t *buf, size_t len)
{
  // https://www.geeksforgeeks.org/udp-server-client-implementation-c/
  int sockfd;
  struct sockaddr_in servaddr;

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(61236);
  if (inet_aton(addr_string.c_str(), &servaddr.sin_addr) == 0)
  {
    perror("inet_aton");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  int n;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }
  int in = sendto(sockfd, (const char *)buf, len,
                  0, (const struct sockaddr *)&servaddr,
                  sizeof(servaddr));
  if (in < 0)
  {
    cout << "Error: " << errno << endl;
    exit(0);
  }

  close(sockfd);
}
void loop()
{
  if (remote_ip.has_value())
  {
    camera_fb_t *camera_buf = esp_camera_fb_get();
    if (!camera_buf)
    {
      exit(1);
    }
    send_camera_data(sock_fd, remote_ip.value(), 61236, camera_buf->buf, camera_buf->len);
    esp_camera_fb_return(camera_buf);
  }
  else
  {
    auto remote_ping = get_remote_ip(sock_fd, 61234);
    if (remote_ping.has_value())
    {
      digitalWrite(4, HIGH);
      remote_ip.emplace(remote_ping.value());
    }
  }
}
