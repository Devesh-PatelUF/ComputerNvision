#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

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
void startCameraServer();
WiFiServer server(80);

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
  if (psramFound())
  {
    cout << "psram found" << endl;
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  }
  else
  {
    cout << "psram not found" << endl;
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    printf("Camera init failed with error 0x%x", err);
    cout << endl;
    return;
  }

  sensor_t *s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  // if (s->id.PID == OV3660_PID)
  {
    cout << "OV3660" << endl;
    s->set_vflip(s, 1);          // flip it back
    s->set_brightness(s, 4);     // up the blightness just a bit
    s->set_saturation(s, 2);     // lower the saturation
    s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)  server.begin();
    s->set_colorbar(s, 0);       // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)  server.begin();
  }
  // drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

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

  auto raw_address = WiFi.localIP();
  cout << "Camera Ready! Use 'http://";
  cout << (int)raw_address[0] << "." << (int)raw_address[1] << "." << (int)raw_address[2] << "." << (int)raw_address[3];
  cout << "' to connect" << endl;
  pinMode(4, OUTPUT); // Specify that LED pin is output
  server.begin();
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

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  {
    // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    vector<uint8_t> bytes;
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { // loop while the client's connected
      currentTime = millis();
      if (client.available())
      {
        uint8_t byte = client.read();
        bytes.emplace_back(byte);
      }
      std::string header(bytes.begin(), bytes.end());
      cout << "Header: " << header << "|Header" << endl;
      if (ends_with(header, "\r\n\r\n") || ends_with(header, "\n\n"))
      {
        string content_type = "Content-type: text/html";
        int code = 200;
        camera_fb_t *camera_buf = NULL;
        if (header.find("GET /api/v0/flash_on") != std::string::npos)
        {
          digitalWrite(4, HIGH);
        }
        if (header.find("GET /api/v0/flash_off") != std::string::npos)
        {
          digitalWrite(4, LOW);
        }
        if (header.find("GET /api/v0/take_picture") != std::string::npos)
        {
          digitalWrite(4, HIGH);
          vTaskDelay(500 / portTICK_PERIOD_MS);

          for (int i = 0;i<1000;i++)
          {
            camera_buf = esp_camera_fb_get();
            if (!camera_buf)
            {
              cout << "Camera capture failed" << endl;
              code = 500;
            }
            else
            {
              content_type = "Content-type: image/jpeg";
            }
            esp_camera_fb_return(camera_buf);
          }
          digitalWrite(4, LOW);
        }
        string return_string = (string("HTTP/1.1 ") + to_string(code) + " OK");
        client.println(return_string.c_str());
        client.println(content_type.c_str());
        client.println();
        if (camera_buf != nullptr)
        {
          cout << "Camera buf not null" << endl;
          client.write(camera_buf->buf, camera_buf->len);
        }
        client.println();
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
      }
    }
  }
}
