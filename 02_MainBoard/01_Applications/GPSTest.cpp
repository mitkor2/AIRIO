/*
 * GPSTest.cpp
 *
 *  Created on: Jun 22, 2020
 *      Author: User
 */
#include <Arduino.h>
#include "MainBoard.h"
#include "config.h"
#include "Utils.h"
#include "TinyGPS++.h"

TinyGPSPlus gps;
#define GPS_SERIAL (Serial2)

static const uint32_t GPSBaud = 9600;
//void displayInfo();
#define GPS_POWER_ENABLE (ENERGIA_PWM_P2_5)
#define GPS_TIMEPULSE (ENERGIA_GPIO_P7_2)
//#define GPS_RESET (ENERGIA_GPIO_P7_5)



void setup()
{
    board.init();
    board.power(true);
    board.sensorPower(true);

    CONSOLE_START();

    GPS_SERIAL.begin(GPSBaud);

    pinMode(GPS_TIMEPULSE, INPUT);

//    pinMode(GPS_RESET, OUTPUT);
//    digitalWrite(GPS_RESET, LOW);

    pinMode(GPS_POWER_ENABLE, OUTPUT);
    digitalWrite(GPS_POWER_ENABLE, HIGH);

//    delay(100);
//    digitalWrite(GPS_RESET, HIGH);
//    delay(100);
//    digitalWrite(GPS_RESET, LOW);


    CONSOLE_PRINTLN("GPS STARTED");

}
void loop()
{
    static bool timepulse = false;

    if (digitalRead(GPS_TIMEPULSE) == HIGH)
    {
        if (!timepulse)
        {
            timepulse = true;
            while (GPS_SERIAL.available() > 0)
            {
                gps.encode(GPS_SERIAL.read());
            }

            if (gps.location.isValid())
            {
                CONSOLE_PRINTLN(gps.location.lat(), 7);
                CONSOLE_PRINTLN(gps.location.lng(), 7);
                CONSOLE_PRINTLN(gps.altitude.meters());
            }
            else
            {
        //        CONSOLE_PRINTLN("GPS IS NOT AVAILABLE");
            }
        }
    }
    else
    {
        timepulse = false;
    }
}


//void displayInfo()
//{
//  CONSOLE_PRINT(F("Location: "));
//  if (gps.location.isValid())
//  {
//    CONSOLE_PRINT(gps.location.lat(), 6);
//    CONSOLE_PRINT(F(","));
//    CONSOLE_PRINT(gps.location.lng(), 6);
//  }
//  else
//  {
//    CONSOLE_PRINT(F("INVALID"));
//  }
//
//  CONSOLE_PRINT(F("  Date/Time: "));
//  if (gps.date.isValid())
//  {
//    CONSOLE_PRINT(gps.date.month());
//    CONSOLE_PRINT(F("/"));
//    CONSOLE_PRINT(gps.date.day());
//    CONSOLE_PRINT(F("/"));
//    CONSOLE_PRINT(gps.date.year());
//  }
//  else
//  {
//    CONSOLE_PRINT(F("INVALID"));
//  }
//
//  CONSOLE_PRINT(F(" "));
//  if (gps.time.isValid())
//  {
//    if (gps.time.hour() < 10) CONSOLE_PRINT(F("0"));
//    CONSOLE_PRINT(gps.time.hour());
//    CONSOLE_PRINT(F(":"));
//    if (gps.time.minute() < 10) CONSOLE_PRINT(F("0"));
//    CONSOLE_PRINT(gps.time.minute());
//    CONSOLE_PRINT(F(":"));
//    if (gps.time.second() < 10) CONSOLE_PRINT(F("0"));
//    CONSOLE_PRINT(gps.time.second());
//    CONSOLE_PRINT(F("."));
//    if (gps.time.centisecond() < 10) CONSOLE_PRINT(F("0"));
//    CONSOLE_PRINT(gps.time.centisecond());
//  }
//  else
//  {
//    CONSOLE_PRINT(F("INVALID"));
//  }
//
//  CONSOLE_PRINTLN();
//}
