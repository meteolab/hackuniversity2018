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
String Channel = "hack2018";
Meteonet meteonet(Channel);
unsigned long rem;
unsigned long prev = 0;
unsigned long period = 30;
double summa_1_0 = 0.0;
double summa_2_5 = 0.0;
double summa_10_0 = 0.0;
int N = 0;
double PM_1_0;
double PM_2_5;
double PM_10_0;



void setup() {
    Serial.begin(9600);
    PMS7003.begin(9600);
    pinMode(pinLED, OUTPUT);
    delay(500);
    Serial.println();
    // meteonet.begin();
    delay(500);
}


void loop() {

    if(pms.read(data)) {
        digitalWrite(pinLED, HIGH);
        /*
        Serial.println("Data:");
        Serial.print("PM 1.0 (ug/m3): ");
        Serial.println(data.PM_AE_UG_1_0);
        Serial.print("PM 2.5 (ug/m3): ");
        Serial.println(data.PM_AE_UG_2_5);
        Serial.print("PM 10.0 (ug/m3): ");
        Serial.println(data.PM_AE_UG_10_0);
        Serial.println();
        */
        summa_1_0  += data.PM_AE_UG_1_0;
        summa_2_5  += data.PM_AE_UG_2_5;
        summa_10_0 += data.PM_AE_UG_10_0;
        N++;
        delay(300);
        digitalWrite(pinLED, LOW);
    }

    // Find seconds from last measurement
    rem = meteonet.getTimestamp() % period;
    if(rem < prev && N > 0) {
        PM_1_0  = summa_1_0/N;
        PM_2_5  = summa_2_5/N;
        PM_10_0 = summa_10_0/N;
        /*
        Serial.print(meteonet.getTimestamp());
        Serial.print("\t");
        Serial.print(meteonet.getLatitude());
        Serial.print("\t");
        Serial.print(meteonet.getLongitude());
        Serial.print("\t");
        Serial.println(PM25);
        meteonet.send(PM25);
        //meteonet.loop();
        */
        Serial.print(PM_1_0);
        Serial.print("\t");
        Serial.print(PM_2_5);
        Serial.print("\t");
        Serial.println(PM_10_0);
        summa_1_0  = 0.0;
        summa_2_5  = 0.0;
        summa_10_0 = 0.0;
        N = 0;
    }
    prev = rem;

}

