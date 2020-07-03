#ifndef __SBOARD_DEFS_H__
#define __SBOARD_DEFS_H__

// NUCLEO-F091RC

// TODO
#define SBOARD_POWER_ENABLE         (PB5) // PB5_PWR_EN
#define SBOARD_SO2_POWER_ENABLE_N   (PC9) // PC9_EN_SULFUR
#define SBOARD_NO2_POWER_ENABLE_N   (PB8) // PB8_EN_NITROGEN
#define SBOARD_CO_POWER_ENABLE_N    (PA6) // PA6_EN_CARBON
#define SBOARD_O3_POWER_ENABLE_N    (PA7) // PA7_EN_OZONE
#define SBOARD_TH_POWER_ENABLE_N    (PB6) // PB6_EN_TEMP
#define SBOARD_PM_POWER_ENABLE      (PC7) // PC7_EN_HONEY

#define SBOARD_FAN1_ENABLE_N        (PC8) // PC8_FAN1
#define SBOARD_FAN2_ENABLE_N        (PC6) // PC6_FAN2

#define SBOARD_PM_ANALOG            (PC3) // PC3_ADC_VOUT

// RS422 Serial
#define SBOARD_RS422_SERIAL         (Serial7) // TODO check
#define SBOARD_RS422_SERIAL_BAUD    (115200)
#define SBOARD_RS422_TX             (PC2) // PA9_USART1_TX
#define SBOARD_RS422_RX             (PC3) // PA10_USART1_RX

// O3 Serial
#define SBOARD_O3_SERIAL            (Serial1)
#define SBOARD_O3_SERIAL_BAUD       (9600)
#define SBOARD_O3_TX                (PA9) // PA2_USART2_TX
#define SBOARD_O3_RX                (PA10) // PA3_USART2_RX

// CO Serial
#define SBOARD_CO_SERIAL            (Serial3)
#define SBOARD_CO_SERIAL_BAUD       (9600)
#define SBOARD_CO_TX                (PB10) // PB10_USART3_TX
#define SBOARD_CO_RX                (PB11) // PB11_USART3_RX

// SO2 Serial
#define SBOARD_SO2_SERIAL           (Serial4)
#define SBOARD_SO2_SERIAL_BAUD      (9600)
#define SBOARD_SO2_TX               (PA0) // PA0_USART4_TX
#define SBOARD_SO2_RX               (PA1) // PA1_USART4_RX

// NO2 Serial
#define SBOARD_NO2_SERIAL           (Serial5)
#define SBOARD_NO2_SERIAL_BAUD      (9600)
#define SBOARD_NO2_TX               (PB3) // PB3_USART5_TX
#define SBOARD_NO2_RX               (PB4) // PB4_USART5_RX

// PM Serial
#define SBOARD_PM_SERIAL            (Serial6)
#define SBOARD_PM_SERIAL_BAUD       (9600)
#define SBOARD_PM_TX                (PC0) // PC0_USART6_TX  in variant is USART7
#define SBOARD_PM_RX                (PC1) // PC1_USART6_RX

#define SBOARD_I2C_SDA              (PB14) // PB14_SDA
#define SBOARD_I2C_SCL              (PB13) // PB13_SCL

#define SBOARD_BME280_WIRE          (Wire)



// EXTERNS
extern HardwareSerial Serial3;
extern HardwareSerial Serial4;
extern HardwareSerial Serial5;
extern HardwareSerial Serial6;

// STRUCT DATA
typedef struct
{
    float temp;
    float hum;
    float pres; 
    int32_t ozone; 
    int32_t carbo;
    int32_t sulfu;
    int32_t nitro;
    uint32_t pm1_0;
    uint32_t pm2_5;
    uint32_t pm4_0;
    uint32_t pm10;
    int32_t airquality;
} SboardData_t;


#endif //  __SBOARD_DEFS_H__
