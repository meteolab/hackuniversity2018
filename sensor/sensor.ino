#include "PMS.h"

PMS pms(Serial);
PMS::DATA data;

int pinLED = 5; // D1
int value;

void setup() {
    Serial.begin(9600);   // GPIO1, GPIO3 (TX/RX pin on ESP-12E Development Board)
    Serial1.begin(9600);  // GPIO2 (D4 pin on ESP-12E Development Board)
    pinMode(pinLED, OUTPUT);
}

void loop() {

    if(pms.read(data)) {
        Serial1.println("Data:");
        Serial1.print("PM 1.0 (ug/m3): ");
        Serial1.println(data.PM_AE_UG_1_0);
        Serial1.print("PM 2.5 (ug/m3): ");
        Serial1.println(data.PM_AE_UG_2_5);
        Serial1.print("PM 10.0 (ug/m3): ");
        Serial1.println(data.PM_AE_UG_10_0);
        Serial1.println();
    }

    for(int i=0; i<180; i++) {
        value = int(255*sin(i*3.1415/180.0));
        analogWrite(pinLED, value);
        delay(30);
    }
    digitalWrite(pinLED, LOW);
    delay(800);
}
