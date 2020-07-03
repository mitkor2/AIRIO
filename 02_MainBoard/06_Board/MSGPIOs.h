/**
 * \file MSGPIOs.h
 * \brief This file defines all GPIOs used in the project
 * \author Emil Kirilov
 * \date 20 Sep 2019
 */
#ifndef __MS_GPIOS_H__
#define __MS_GPIOS_H__

#include "EnergiaPins.h"

/********************************************************/
/*                  MBOARD GPIOS                        */
/********************************************************/

// LEDS
#define LED_YELLOW          (ENERGIA_GIPO_P1_0)
#define LED_RED             (ENERGIA_PWM_P2_0)
#define LED_GREEN           (ENERGIA_PWM_P2_1)
#define LED_BLUE            (ENERGIA_PWM_P2_2)

// BUTTONS
#define BUTTON1             (ENERGIA_GIPO_P1_1)
#define BUTTON2             (ENERGIA_GIPO_P1_4)

// SPI
#define SPI_CLK             (ENERGIA_SPI1_CLK_P3_5)
#define SPI_MOSI            (ENERGIA_SPI1_MOSI_P3_6)
#define SPI_MISO            (ENERGIA_SPI1_MISO_P3_7)

// I2C
#define I2C_SDA             (ENERGIA_I2C_SDA_P6_4)
#define I2C_SCL             (ENERGIA_I2C_SCL_P6_5)

// FLASH
#define FLASH_SPI_CLK       (ENERGIA_SPI0_CLK_P1_5)
#define FLASH_SPI_MOSI      (ENERGIA_SPI0_MOSI_P1_6)
#define FLASH_SPI_MISO      (ENERGIA_SPI0_MISO_P1_7)
#define FLASH_SPI_CS_       (ENERGIA_GPIO_P9_2)

// POWER
#define PS_3V3_ENABLE       (ENERGIA_GPIO_P5_0)
#define PS_VSYS_ENABLE      (ENERGIA_GPIO_P5_1)
#define PS_VBAT_ENABLE      (ENERGIA_GPIO_P5_2)

// BATTERY
#define VBAT_MSRMNT_AIN     (ENERGIA_GPIO_P5_5)
#define VBAT_MSRMNT_ON      (ENERGIA_GPIO_P8_0)
#define BM_GPIO1            (ENERGIA_GPIO_P10_2)
#define BM_GPIO2            (ENERGIA_GPIO_P10_3)

// IMU
#define IMU_INT1            (ENERGIA_GPIO_P5_6)
#define IMU_INT2            (ENERGIA_GPIO_P5_7)

// WIRELESS
#define WL_RX               (ENERGIA_UART1_RX_P3_2)
#define WL_TX               (ENERGIA_UART1_TX_P3_3)
#define WL_CTS              (ENERGIA_GPIO_P7_0)
#define WL_RTS              (ENERGIA_GPIO_P7_1)
#define WL_DCD              (ENERGIA_GPIO_P7_2)
#define WL_PWR_EN           (ENERGIA_GPIO_P7_3)
#define WL_PWR_ON           (ENERGIA_GPIO_P7_4)
#define WL_RESET            (ENERGIA_GPIO_P7_5)
#define WL_PWR_MON          (ENERGIA_GPIO_P7_6)
#define WL_RING             (ENERGIA_GPIO_P7_7)
#define WL_SPI_CS_          (ENERGIA_GPIO_P9_3)

// ULTRASONIC
#define US0_TRIG            (ENERGIA_GPIO_P10_4)
#define US0_ECHO            (ENERGIA_GPIO_P3_0)

// OTHER
#define DEBUG_DETECT_5V     (ENERGIA_GPIO_P9_4)
#define TEMP_SENSOR0_DQ     (ENERGIA_GPIO_P2_7)
#define WDT_CLEAR_PIN       (ENERGIA_GPIO_P9_7)

// ALIASES
#define LED_RED0            (LED_YELLOW)

#define LED_ON                  (HIGH)
#define LED_OFF                 (LOW)
#define ENABLED                 (HIGH)
#define DISABLED                (LOW)

// UART GPS
#define GPS_TX              (ENERGIA_PWM_P2_3)
#define GPS_RX              (ENERGIA_PWM_P2_4)



// NOT USED
#define NOT_USED_03             (ENERGIA_PWM_P2_5)           // P2.5
#define NOT_USED_04             (ENERGIA_PWM_P2_6)           // P2.6
#define NOT_USED_05             (ENERGIA_A13_P4_0)           // P4.0
#define NOT_USED_06             (ENERGIA_A12_P4_1)           // P4.1
#define NOT_USED_07             (ENERGIA_A11_P4_2)           // P4.2
#define NOT_USED_08             (ENERGIA_A10_P4_3)           // P4.3
#define NOT_USED_09             (ENERGIA_A09_P4_4)           // P4.4
#define NOT_USED_10             (ENERGIA_A08_P4_5)           // P4.5
#define NOT_USED_11             (ENERGIA_A07_P4_6)           // P4.6
#define NOT_USED_12             (ENERGIA_A06_P4_7)           // P4.7
#define NOT_USED_13             (ENERGIA_A02_P5_3)           // P5.3
#define NOT_USED_14             (ENERGIA_A01_P5_4)           // P5.4
#define NOT_USED_15             (ENERGIA_A15_P6_0)           // P6.0
#define NOT_USED_16             (ENERGIA_A14_P6_1)           // P6.1
#define NOT_USED_17             (ENERGIA_GPIO_P6_2)          // P6.2
#define NOT_USED_18             (ENERGIA_GPIO_P6_3)          // P6.3
#define NOT_USED_19             (ENERGIA_GPIO_P6_6)          // P6.6
#define NOT_USED_20             (ENERGIA_GPIO_P6_7)          // P6.7
#define NOT_USED_21             (ENERGIA_A24_P8_2)           // P8.2
#define NOT_USED_22             (ENERGIA_A22_P8_3)           // P8.3
#define NOT_USED_23             (ENERGIA_A21_P8_4)           // P8.4
#define NOT_USED_24             (ENERGIA_A20_P8_5)           // P8.5
#define NOT_USED_25             (ENERGIA_A19_P8_6)           // P8.6
#define NOT_USED_26             (ENERGIA_A18_P8_7)           // P8.7
#define NOT_USED_27             (ENERGIA_A17_P9_0)           // P9.0
#define NOT_USED_28             (ENERGIA_A16_P9_1)           // P9.1
#define NOT_USED_29             (ENERGIA_GPIO_P9_5)          // P9.5
#define NOT_USED_30             (ENERGIA_GPIO_P9_6)          // P9.6
#define NOT_USED_31             (ENERGIA_GPIO_P9_7)          // P9.7
#define NOT_USED_32             (ENERGIA_GPIO_P10_0)         // P10.0
#define NOT_USED_33             (ENERGIA_GPIO_P10_1)         // P10.1
#define NOT_USED_34             (ENERGIA_GPIO_P10_5)         // P10.5




/********************************************************/
/* NOT USED                                             */
/********************************************************/




#endif // __MS_GPIOS_H__
