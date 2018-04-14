int pinLED = 5; // D1
int value;

void setup() {
    pinMode(pinLED, OUTPUT);
}

void loop() {

    for(int i=0; i<180; i++) {
        value = int(255*sin(i*3.1415/180.0));
        analogWrite(pinLED, value);
        delay(30);
    }
    digitalWrite(pinLED, LOW);
    delay(800);
}
