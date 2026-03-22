// 设置PWM属性
const int freq = 5000;
const int resolution = 8;
const int ledPin = 26;  // 需要定义LED引脚

void setup() {
    Serial.begin(115200);
    
    // 直接将引脚、频率和分辨率绑定
    ledcAttach(ledPin, freq, resolution);
}

void loop() {
    // 逐渐变亮
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
        ledcWrite(ledPin, dutyCycle);  // 写入PWM值
        delay(10);  // 添加延时，否则变化太快看不到效果
    }
    
    // 逐渐变暗
    for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
        ledcWrite(ledPin, dutyCycle);  // 写入PWM值
        delay(10);  // 添加延时
    }
}