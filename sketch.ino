#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_HOTSPOT";
const char* password = "12345678";

const int turbidityPin = 34;

WebServer server(80);

void handleRoot() {

  int turbidityValue = analogRead(turbidityPin);

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Water Quality</title>

  <style>
    body {
      font-family: Arial, sans-serif;
      background: #f2f6f8;
      text-align: center;
      margin: 0;
      padding: 30px;
    }

    .card {
      max-width: 450px;
      margin: auto;
      background: white;
      padding: 30px;
      border-radius: 20px;
      box-shadow: 0 5px 20px rgba(0,0,0,0.1);
    }

    h1 {
      color: #123;
    }

    .value {
      font-size: 60px;
      font-weight: bold;
      margin: 20px 0;
    }

    .unit {
      font-size: 20px;
      color: #777;
    }

    .status {
      margin-top: 25px;
      padding: 12px;
      border-radius: 10px;
      background: #d9f7df;
      color: #176b2c;
    }

    .refresh {
      margin-top: 20px;
      color: #777;
    }
  </style>
</head>

<body>

  <div class="card">

    <h1>Water Quality</h1>

    <div class="value">
      )rawliteral";

  html += turbidityValue;

  html += R"rawliteral(
    </div>

    <div class="unit">
      Raw Turbidity Sensor Value
    </div>

    <div class="status">
      ● Sensor Online
    </div>

    <div class="refresh">
      Refreshing every 1 second
    </div>

  </div>

<script>
  setTimeout(function() {
    location.reload();
  }, 1000);
</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_AP);

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("ESP32 Hotspot Started");
  Serial.print("WiFi Name: ");
  Serial.println(ssid);

  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);

  server.begin();

  Serial.println("Web server started");
}

void loop() {

  server.handleClient();

}
