#include <ti/sysbios/family/arm/msp432/Seconds.h>
#include <Arduino.h>
#include "MainBoard.h"
#include "config.h"
#include "ConnService.h"
#include "Utils.h"
#include "SerialTransfer.h"
#include "TinyGPS++.h"

TinyGPSPlus gps;
#define GPS_SERIAL (Serial2)
static const uint32_t GPSBaud = 9600;
#define GPS_POWER_ENABLE (ENERGIA_PWM_P2_5)
#define GPS_TIMEPULSE (ENERGIA_GPIO_P7_2)

SerialTransfer myTransfer;
#define SENSOR_BOARD_SERIAL (Serial3)

typedef struct
{
    float latitude;
    float longitude;
    int32_t meters;
} GPSData_t;

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

static SBoardData_t sBoardData;

static GPSData_t Data_GPS;

ConnService connection;

void setup()
{
    board.init();
    board.power(true);
    board.sensorPower(true);

    CONSOLE_START();

    GPS_SERIAL.begin(GPSBaud);
    pinMode(GPS_TIMEPULSE, INPUT);
    pinMode(GPS_POWER_ENABLE, OUTPUT);
    digitalWrite(GPS_POWER_ENABLE, HIGH);

    SENSOR_BOARD_SERIAL.begin(115200);
    myTransfer.begin(SENSOR_BOARD_SERIAL);

    utilsOnReset();

    connection.begin();

    time_t datetime;

    Seconds_set(0);

    if (connection.getServerDateTime(datetime) == CONN_SVC_OK)
    {
        Seconds_set(datetime);
        CONSOLE_PRINTLN(datetime);
    }
}



void loop()
{
    if (myTransfer.available() > 0)
      {
          while (myTransfer.available() < sizeof(SBoardData_t))
          {
              delay(5);
          }

          memcpy(&sBoardData, myTransfer.rxBuff, sizeof(SBoardData_t));

//          CONSOLE_PRINTLN(sBoardData.temperature);
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

                Data_GPS.latitude = gps.location.lat();
                Data_GPS.longitude = gps.location.lng();
                Data_GPS.meters = gps.altitude.meters();
            }
            else
            {
            }
        }
    }
    else
    {
        timepulse = false;
    }



    ProtoMsrData_t data;

    data.timestamp = Seconds_get();
    data.temperature = (int32_t)(sBoardData.temperature * PROTO_DATA_FRACT_VALUE_MULTIPLIER);
    data.humidity = (int32_t)(sBoardData.humidity * PROTO_DATA_FRACT_VALUE_MULTIPLIER);
    data.pressure = (int32_t)(sBoardData.pressure * PROTO_DATA_FRACT_VALUE_MULTIPLIER);
    data.ozone = sBoardData.ozone;
    data.carbonMonoxide = sBoardData.carbonMonoxide;
    data.sulfurDioxide = sBoardData.sulfurDioxide;
    data.nitrogenDioxide = sBoardData.nitrogenDioxide;
    data.pm1_0 = sBoardData.pm1_0;
    data.pm2_5 = sBoardData.pm2_5;
    data.pm4_0 = sBoardData.pm4_0;
    data.pm10 = sBoardData.pm10;
    data.airq = sBoardData.airq;
    data.vbatt = PROTO_DATA_INVALID_VALUE * PROTO_DATA_FRACT_VALUE_MULTIPLIER; // PROTO_DATA_FRACT_VALUE_MULTIPLIER
    data.cbatt = PROTO_DATA_INVALID_VALUE * PROTO_DATA_FRACT_VALUE_MULTIPLIER; // PROTO_DATA_FRACT_VALUE_MULTIPLIER
    data.fixQuality = 10;
    data.latitude = (int32_t)(Data_GPS.latitude * PROTO_DATA_GPS_VALUE_MULTIPLIER);
    data.longitude = (int32_t)(Data_GPS.longitude * PROTO_DATA_GPS_VALUE_MULTIPLIER);
    data.altitude = Data_GPS.meters;

    connection.sendMsrDataSend(&data);

    delay(2000);
}
