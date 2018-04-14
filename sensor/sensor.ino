#include <SoftwareSerial.h>
#include <meteonet.h>
#include "PMS.h"

/* Plantower PMS7003 Datasheet
 * https://www.pdf-archive.com/2017/04/12/plantower-pms-7003-sensor-data-sheet/plantower-pms-7003-sensor-data-sheet.pdf
 * Library
 * https://github.com/fu-hsi/pms
 * 
 * Some Information
 * https://learn.adafruit.com/pm25-air-quality-sensor/arduino-code
 *
 *
 * Connection
 * 
 *  PMS7003 -> ESP8266
 *  ------------------
 *  VCC (1) -> 5V
 *  GND (3) -> GND
 *  RX  (7) -> D3 (0)
 *  TX  (9) -> D4 (2)
 *  
 *  LED
 *  ---
 *  (+) -> D1 (5)
 *  (-) -> GND
 */

SoftwareSerial PMS7003(2, 0); // (RX = pin 2, TX = pin 0)
PMS pms(PMS7003);
PMS::DATA data;
int pinLED = 5;
int value;


void setup() {
    Serial.begin(9600);
    PMS7003.begin(9600);
    pinMode(pinLED, OUTPUT);
    delay(500);
    Serial.println();
    meteonet.begin();
    delay(500);
}


void loop() {

    if(pms.read(data)) {
        digitalWrite(pinLED, HIGH);
        Serial.println("Data:");
        Serial.print("PM 1.0 (ug/m3): ");
        Serial.println(data.PM_AE_UG_1_0);
        Serial.print("PM 2.5 (ug/m3): ");
        Serial.println(data.PM_AE_UG_2_5);
        Serial.print("PM 10.0 (ug/m3): ");
        Serial.println(data.PM_AE_UG_10_0);
        Serial.println();
        digitalWrite(pinLED, LOW);
    }
    /*
    for(int i=0; i<180; i++) {
        value = int(255*sin(i*3.1415/180.0));
        analogWrite(pinLED, value);
        delay(30);
    }
    digitalWrite(pinLED, LOW);
    delay(800);
    */
}

