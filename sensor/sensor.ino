#include "SoftwareSerial.h"
#include "PMS.h"

/* Plantower PMS7003 Datasheet
 * https://www.pdf-archive.com/2017/04/12/plantower-pms-7003-sensor-data-sheet/plantower-pms-7003-sensor-data-sheet.pdf
 * Library
 * https://github.com/fu-hsi/pms
 * 
 * Some
 * https://learn.adafruit.com/pm25-air-quality-sensor/arduino-code
 */

/* Connection PMS7003 -> ESP8266:
 *  TX  (9) -> D4 (2)
 *  VCC (1) -> 5V
 *  GND (3) -> GND
 */
 
SoftwareSerial PMS7003(2, 3);
PMS pms(PMS7003);
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
