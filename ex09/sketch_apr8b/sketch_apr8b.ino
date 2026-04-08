#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "vivo S19";
const char* password = "18700381727";

const int TOUCH_PIN = T0;   // GPIO4 触摸引脚

WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // 连接 WiFi
  WiFi.begin(ssid, password);
  Serial.print("连接 WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi 已连接");
  Serial.print("IP 地址: ");
  Serial.println(WiFi.localIP());

  // 路由设置
  server.on("/", handleRoot);      // 网页页面
  server.on("/value", handleValue); // 数据接口

  server.begin();
  Serial.println("Web 服务器已启动");
  Serial.println("请在浏览器中访问上方 IP 地址");
}

void loop() {
  server.handleClient();
}

// 网页页面
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>实时传感器仪表盘</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 50px;
            background-color: #f0f0f0;
        }
        .container {
            background-color: white;
            padding: 30px;
            border-radius: 20px;
            display: inline-block;
            box-shadow: 0 4px 8px rgba(0,0,0,0.1);
        }
        .value {
            font-size: 80px;
            font-weight: bold;
            color: #0066cc;
            margin: 20px 0;
        }
        .label {
            font-size: 18px;
            color: #666;
        }
        .unit {
            font-size: 24px;
            color: #999;
        }
        .status {
            margin-top: 20px;
            font-size: 16px;
            color: #888;
        }
    </style>
</head>
<body>
    <div class="container">
        <h2>📊 触摸传感器实时数值</h2>
        <div class="value">
            <span id="sensorValue">---</span>
            <span class="unit"></span>
        </div>
        <div class="label">触摸数值（越小表示越靠近）</div>
        <div class="status" id="status">等待数据...</div>
    </div>

    <script>
        function fetchValue() {
            fetch('/value')
                .then(response => response.text())
                .then(data => {
                    document.getElementById('sensorValue').innerText = data;
                    document.getElementById('status').innerHTML = '✅ 实时更新中...';
                    
                    // 根据数值改变颜色
                    let val = parseInt(data);
                    let color = '#0066cc';
                    if (val < 30) color = '#ff0000';      // 红色：触摸中
                    else if (val < 50) color = '#ff6600'; // 橙色：靠近
                    else color = '#0066cc';                // 蓝色：远离
                    document.querySelector('.value').style.color = color;
                })
                .catch(error => {
                    document.getElementById('status').innerHTML = '⚠️ 连接失败';
                });
        }
        
        // 每100毫秒刷新一次（实时更新）
        setInterval(fetchValue, 100);
        
        // 页面加载时立即获取一次
        fetchValue();
    </script>
</body>
</html>
)rawliteral";
  server.send(200, "text/html", html);
}

// 数据接口：返回当前触摸数值
void handleValue() {
  int touchValue = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(touchValue));
}