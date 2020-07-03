/*
 * SBoardTest.cpp
 *
 *  Created on: Jun 22, 2020
 *      Author: User
 */
#include <Arduino.h>
#include "MainBoard.h"
#include "config.h"
#include "Utils.h"
#include "SerialTransfer.h"

SerialTransfer myTransfer;
#define SENSOR_BOARD_SERIAL (Serial3)

typedef struct
{
    float temperature;
    float humidity;
    float pressure;
    int32_t ozone;
    int32_t carbonMonoxide;
    int32_t sulfurDioxide;
    int32_t nitrogenDioxide;
    uint32_t pm1_0;
    uint32_t pm2_5;
    uint32_t pm4_0;
    uint32_t pm10;
    int32_t airq;
} SBoardData_t;

static SBoardData_t data;

void setup()
{
    board.init();
    board.power(true);
    board.sensorPower(true);

    CONSOLE_START();

    SENSOR_BOARD_SERIAL.begin(115200);
    myTransfer.begin(SENSOR_BOARD_SERIAL);
}
void loop()
{
   if (myTransfer.available() > 0)
    {
        while (myTransfer.available() < sizeof(SBoardData_t))
        {
            delay(5);
        }

        memcpy(&data, myTransfer.rxBuff, sizeof(SBoardData_t));

        CONSOLE_PRINTLN(data.temperature);
    }
    else if(myTransfer.status < 0)
    {
        CONSOLE_PRINTLN("ERROR: ");

      if(myTransfer.status == -1)
      {
          CONSOLE_PRINTLN(F("CRC_ERROR"));
      }
      else if(myTransfer.status == -2)
      {
          CONSOLE_PRINTLN(F("PAYLOAD_ERROR"));
      }
      else if(myTransfer.status == -3)
      {
          CONSOLE_PRINTLN(F("STOP_BYTE_ERROR"));
      }
    }
}
