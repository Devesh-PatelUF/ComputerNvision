#ifndef _PAGE_H_
#define _PAGE_H_
// page.h
static const char* page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32-CAM Photo Capture</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin: 0 auto; padding-top: 20px; }
        img { max-width: 100%; height: auto; }
        .container { margin: 20px auto; }
        .button { padding: 10px 20px; font-size: 20px; cursor: pointer; }
    </style>
</head>
<body>
    <h2>ESP32-CAM Photo Capture</h2>
    <div class="container" id="stream-container">
        <img src="stream" id="stream" crossorigin="anonymous">
    </div>
    <button class="button" id="capture">Capture Photo</button>
    <div class="container">
        <img id="photo" src="" alt="Captured photo will appear here...">
    </div>
    <script>
        document.getElementById('capture').addEventListener('click', function() {
            fetch('/capture')
                .then(response => response.blob())
                .then(blob => {
                    var imageUrl = URL.createObjectURL(blob);
                    document.getElementById('photo').src = imageUrl;
                })
                .catch(error => console.error('Error capturing photo:', error));
        });
    </script>
</body>
</html>
)rawliteral";

#endif
