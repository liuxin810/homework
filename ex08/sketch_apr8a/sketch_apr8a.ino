#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "vivo S19";
const char* password = "18700381727";

const int LED_PIN = 2;
const int TOUCH_PIN = T0;

bool armed = false;
bool alarming = false;
unsigned long lastBlink = 0;
bool ledState = false;

WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("连接 WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi 已连接");
  Serial.print("IP 地址: ");
  Serial.println(WiFi.localIP());

  // 网页路由
  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);

  server.begin();
  Serial.println("Web 服务器已启动");
}

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>安防报警器</title>
    <style>
        button { font-size: 24px; padding: 10px 20px; margin: 10px; }
        .status { margin-top: 20px; font-size: 18px; }
    </style>
</head>
<body>
    <h2>ESP32 安防主机</h2>
    <button id="armBtn" style="background-color:#4CAF50; color:white;">🔒 布防</button>
    <button id="disarmBtn" style="background-color:#f44336; color:white;">🔓 撤防</button>
    <div class="status" id="statusMsg"></div>

    <script>
        document.getElementById('armBtn').onclick = function() {
            fetch('/arm')
                .then(response => response.text())
                .then(data => {
                    document.getElementById('statusMsg').innerHTML = data;
                    setTimeout(() => {
                        document.getElementById('statusMsg').innerHTML = '';
                    }, 2000);
                });
        };
        
        document.getElementById('disarmBtn').onclick = function() {
            fetch('/disarm')
                .then(response => response.text())
                .then(data => {
                    document.getElementById('statusMsg').innerHTML = data;
                    setTimeout(() => {
                        document.getElementById('statusMsg').innerHTML = '';
                    }, 2000);
                });
        };
    </script>
</body>
</html>
)rawliteral";
  server.send(200, "text/html", html);
}

void handleArm() {
  armed = true;
  alarming = false;
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "✅ 已布防！");
  Serial.println("布防");
}

void handleDisarm() {
  armed = false;
  alarming = false;
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "✅ 已撤防！");
  Serial.println("撤防");
}

void loop() {
  server.handleClient();

  // 布防状态下检测触摸
  if (armed && !alarming) {
    int touchVal = touchRead(TOUCH_PIN);
    if (touchVal < 30) {
      alarming = true;
      Serial.println("⚠️ 报警触发！");
    }
  }

  // 报警闪烁
  if (alarming) {
    unsigned long now = millis();
    if (now - lastBlink > 200) {
      lastBlink = now;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}