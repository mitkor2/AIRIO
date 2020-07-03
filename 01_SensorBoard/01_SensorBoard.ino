#include "DGS.h"
#include "SBoardDefs.h"
#include "SerialTransfer.h"
#include "SoftwareSerial.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <hpma115C0.h>

SerialTransfer myTransfer;

static SboardData_t data;

Adafruit_BME280 bme280;

HPMA115C0 pmsensor(SBOARD_PM_SERIAL);

DGS cosensor(&SBOARD_CO_SERIAL);
DGS nosensor(&SBOARD_NO2_SERIAL);
DGS ozonsensor(&SBOARD_O3_SERIAL);
DGS sosensor(&SBOARD_SO2_SERIAL);

void setup()
{
  
  pinMode(SBOARD_POWER_ENABLE , OUTPUT);
  pinMode(SBOARD_SO2_POWER_ENABLE_N, OUTPUT);
  pinMode(SBOARD_NO2_POWER_ENABLE_N, OUTPUT);
  pinMode(SBOARD_CO_POWER_ENABLE_N, OUTPUT); 
  pinMode(SBOARD_O3_POWER_ENABLE_N , OUTPUT); 
  pinMode(SBOARD_TH_POWER_ENABLE_N, OUTPUT); 
  pinMode(SBOARD_PM_POWER_ENABLE, OUTPUT);   
      
  digitalWrite(SBOARD_POWER_ENABLE, HIGH);
  digitalWrite(SBOARD_SO2_POWER_ENABLE_N, LOW);
  digitalWrite(SBOARD_NO2_POWER_ENABLE_N, LOW);
  digitalWrite(SBOARD_CO_POWER_ENABLE_N, LOW);
  digitalWrite(SBOARD_O3_POWER_ENABLE_N, LOW);
  digitalWrite(SBOARD_TH_POWER_ENABLE_N, LOW);
  
  Serial.begin(115200);

  SBOARD_RS422_SERIAL.setTx(SBOARD_RS422_TX);
  SBOARD_RS422_SERIAL.setRx(SBOARD_RS422_RX);
  SBOARD_RS422_SERIAL.begin(SBOARD_RS422_SERIAL_BAUD);
  // MyTransfer init
  myTransfer.begin(SBOARD_RS422_SERIAL);

  //PM Sensor init
  SBOARD_PM_SERIAL.begin(SBOARD_PM_SERIAL_BAUD);
  digitalWrite(SBOARD_PM_POWER_ENABLE, HIGH);
  delay(2000);
  pmsensor.Init();
  
  //CO Sensor init
  SBOARD_CO_SERIAL.begin(SBOARD_CO_SERIAL_BAUD);
  SBOARD_CO_SERIAL.flush();
  cosensor.DEBUG = false;
  SBOARD_CO_SERIAL.write('\n');

  //NO2 Sensor init
  SBOARD_NO2_SERIAL.begin(SBOARD_NO2_SERIAL_BAUD);
  SBOARD_NO2_SERIAL.flush();
  nosensor.DEBUG = false;
  SBOARD_NO2_SERIAL.write('\n');

  //O3 Sensor init
  SBOARD_O3_SERIAL.begin(SBOARD_O3_SERIAL_BAUD);
  SBOARD_O3_SERIAL.flush();
  ozonsensor.DEBUG = false;
  SBOARD_O3_SERIAL.write("c");  

  //SO2 Sensor init
  SBOARD_SO2_SERIAL.begin(SBOARD_SO2_SERIAL_BAUD);
  SBOARD_SO2_SERIAL.flush();
  sosensor.DEBUG = false;
  SBOARD_SO2_SERIAL.write('\n');

  //Init Wire  
  Wire.setSCL(SBOARD_I2C_SCL);
  Wire.setSDA(SBOARD_I2C_SDA);
  Wire.begin(); 

  // BME280 init
  bme280.begin(BME280_ADDRESS_ALTERNATE, &Wire);

}


void loop() 
{ 
    // BME280 SENSOR
    data.temp = bme280.readTemperature();
    data.hum = bme280.readHumidity();
    data.pres = bme280.readPressure()/ 100.0F;

    // NO2 SENSOR
    nosensor.getData('\r');
    data.nitro = nosensor.getConc('p'); //measured ppb

    // CO SENSOR
    cosensor.getData('\r');
    data.carbo = cosensor.getConc('p');

    // SO2 SENSOR
    sosensor.getData('\r');
    data.sulfu = sosensor.getConc('p');

    // O3 SENSOR
    ozonsensor.getData('\r');
    data.ozone = ozonsensor.getConc('p');

    // PM SENSOR
    pmsensor.ReadParticleMeasurement(&data.pm1_0,&data.pm2_5, &data.pm4_0, &data.pm10);

    Serial.println("Temp: " + String(data.temp) + " HUM: " + String(data.hum) + " PRES: " + String(data.pres) );
    Serial.println("NO2: " + String(data.nitro) + " CO: " + String(data.carbo) + " SO2: " + String(data.sulfu) + " O3: " + String(data.ozone));    
    Serial.println("PM 1.0: " + String(data.pm1_0) + " ug/m3" );
    Serial.println("PM 2.5: " + String(data.pm2_5) + " ug/m3" );
    Serial.println("PM 4.0: " + String(data.pm4_0) + " ug/m3" );
    Serial.println("PM 10: " + String(data.pm10) + " ug/m3" );

    //RS422 Communicaiton
    memcpy(myTransfer.txBuff, &data, sizeof(SboardData_t));
    myTransfer.sendData(sizeof(SboardData_t));

}
