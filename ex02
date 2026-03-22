#define led_Pin 2
#define led_Pin1 26

void setup() {
  Serial.begin(115200);
  pinMode(led_Pin, OUTPUT);
  pinMode(led_Pin1, OUTPUT);
}

void loop() {
  digitalWrite(led_Pin, HIGH);
  digitalWrite(led_Pin1, HIGH);
  Serial.println("LED ON");
  delay(1000);  // 原代码缺少 delay(1000) 为点亮状态

  digitalWrite(led_Pin, LOW);
  digitalWrite(led_Pin1, LOW);  // 建议同时熄灭两个LED
  Serial.println("LED OFF");
  delay(1000);
}