int builtin_led = 2;   // 板载蓝灯（GPIO2）
int external_led = 26;  // 外接LED接GPIO4

void setup() {
    pinMode(builtin_led, OUTPUT);
    pinMode(external_led, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    // SOS信号：三短 三长 三短
    
    // 三短
    for(int i=0; i<3; i++) {
        digitalWrite(builtin_led, HIGH);
        digitalWrite(external_led, HIGH);  // 外接LED也亮
        delay(200);
        digitalWrite(builtin_led, LOW);
        digitalWrite(external_led, LOW);   // 外接LED也灭
        delay(200);
    }
    delay(500);
    
    // 三长
    for(int i=0; i<3; i++) {
        digitalWrite(builtin_led, HIGH);
        digitalWrite(external_led, HIGH);
        delay(600);
        digitalWrite(builtin_led, LOW);
        digitalWrite(external_led, LOW);
        delay(200);
    }
    delay(500);
    
    // 再重复三短
    for(int i=0; i<3; i++) {
        digitalWrite(builtin_led, HIGH);
        digitalWrite(external_led, HIGH);
        delay(200);
        digitalWrite(builtin_led, LOW);
        digitalWrite(external_led, LOW);
        delay(200);
    }
    delay(3000);
}