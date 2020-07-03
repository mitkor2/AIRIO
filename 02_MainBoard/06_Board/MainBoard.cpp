/**
 * \file MainBoard.cpp
 * \brief This file implements handling of the main board -
 *  pin definitions, power supply switching, etc
 * \author Emil Kirilov
 * \date 20 Sep 2019
 */
#include "MainBoard.h"

/*!
 * Global variable declaration
 */
MainBoard board;


/*!
 * \brief Initialization function. Responsible for pin directions and initial states
 * \retval None
 */
void MainBoard::init()
{
    pinMode(LED_YELLOW, OUTPUT);
    digitalWrite(LED_YELLOW, LED_OFF);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, LED_OFF);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LED_OFF);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LED_OFF);

    pinMode(PS_VSYS_ENABLE, OUTPUT);
    digitalWrite(PS_VSYS_ENABLE, LOW);

    pinMode(PS_VBAT_ENABLE, OUTPUT);
    digitalWrite(PS_VBAT_ENABLE, LOW);

    pinMode(PS_3V3_ENABLE, OUTPUT);
    digitalWrite(PS_3V3_ENABLE, LOW);

    pinMode(WL_PWR_EN, OUTPUT);
    digitalWrite(WL_PWR_EN, LOW);

    pinMode(WL_PWR_ON, OUTPUT);
    digitalWrite(WL_PWR_ON, LOW);

    pinMode(WL_RESET, OUTPUT);
    digitalWrite(WL_RESET, LOW);

    pinMode(US0_TRIG, OUTPUT);
    digitalWrite(US0_TRIG, LOW);

    pinMode(FLASH_SPI_CS_, OUTPUT);
    digitalWrite(FLASH_SPI_CS_, HIGH);

    pinMode(WL_SPI_CS_, OUTPUT);
    digitalWrite(WL_SPI_CS_, HIGH);

    pinMode(VBAT_MSRMNT_ON, OUTPUT);
    digitalWrite(VBAT_MSRMNT_ON, LOW);

    pinMode(WL_RTS, OUTPUT);
    digitalWrite(WL_RTS, LOW);

    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);

    pinMode(WL_PWR_MON, INPUT);
    pinMode(WL_RING, INPUT);
    pinMode(WL_CTS, INPUT);
    pinMode(WL_DCD, INPUT);

    pinMode(SPI_CLK, INPUT);
    pinMode(SPI_MOSI, INPUT);
    pinMode(SPI_MISO, INPUT);
    pinMode(FLASH_SPI_CLK, INPUT);
    pinMode(FLASH_SPI_MOSI, INPUT);
    pinMode(FLASH_SPI_MISO, INPUT);

    pinMode(I2C_SDA, INPUT);
    pinMode(I2C_SCL, INPUT);

    pinMode(IMU_INT1, INPUT);
    pinMode(IMU_INT2, INPUT);
    pinMode(BM_GPIO1, INPUT);
    pinMode(BM_GPIO1, INPUT);
    pinMode(DEBUG_DETECT_5V, INPUT);
    pinMode(VBAT_MSRMNT_AIN, INPUT);

    pinMode(US0_ECHO, INPUT);
    pinMode(TEMP_SENSOR0_DQ, INPUT);

    pinMode(GPS_RX, INPUT);
    pinMode(GPS_TX, OUTPUT);

    pinMode(NOT_USED_03, INPUT);
    pinMode(NOT_USED_04, INPUT);
    pinMode(NOT_USED_05, INPUT);
    pinMode(NOT_USED_06, INPUT);
    pinMode(NOT_USED_07, INPUT);
    pinMode(NOT_USED_08, INPUT);
    pinMode(NOT_USED_09, INPUT);
    pinMode(NOT_USED_10, INPUT);
    pinMode(NOT_USED_11, INPUT);
    pinMode(NOT_USED_12, INPUT);
    pinMode(NOT_USED_13, INPUT);
    pinMode(NOT_USED_14, INPUT);
    pinMode(NOT_USED_15, INPUT);
    pinMode(NOT_USED_16, INPUT);
    pinMode(NOT_USED_17, INPUT);
    pinMode(NOT_USED_18, INPUT);
    pinMode(NOT_USED_19, INPUT);
    pinMode(NOT_USED_20, INPUT);
    pinMode(NOT_USED_21, INPUT);
    pinMode(NOT_USED_22, INPUT);
    pinMode(NOT_USED_23, INPUT);
    pinMode(NOT_USED_24, INPUT);
    pinMode(NOT_USED_25, INPUT);
    pinMode(NOT_USED_26, INPUT);
    pinMode(NOT_USED_27, INPUT);
    pinMode(NOT_USED_28, INPUT);
    pinMode(NOT_USED_29, INPUT);
    pinMode(NOT_USED_30, INPUT);
    pinMode(NOT_USED_31, INPUT);
    pinMode(NOT_USED_32, INPUT);
    pinMode(NOT_USED_33, INPUT);
    pinMode(NOT_USED_34, INPUT);
}

/*!
 * \brief Switches power of the main board
 * \param[in] true - power is ON; false - power is OFF
 * \retval None
 */
void MainBoard::power(bool on)
{
    digitalWrite(PS_3V3_ENABLE, on ? HIGH : LOW);
    digitalWrite(PS_VSYS_ENABLE, on ? HIGH : LOW);

    digitalWrite(LED_YELLOW, on ? LED_ON : LED_OFF);

    if (!on)
    {
        pinMode(I2C_SDA, INPUT);
        pinMode(I2C_SCL, INPUT);
        pinMode(FLASH_SPI_CS_, INPUT);
    }

    // add some delay in order to give time for the levels to become stable
    delay(100);
}

/*!
 * \brief Switches power of the radio module. It performs all additional conditions
 * \param[in] true - power is ON; false - power is OFF
 * \retval None
 */
void MainBoard::gsmPower(bool on)
{
#if (WIRELESS_MODULE == WIRELESS_MODULE_GSM_SIM800C)

    if (on)
    {
        if (getGSMStatus())
        {
            return;
        }

        if (digitalRead(WL_PWR_EN) == LOW)
        {
            digitalWrite(WL_PWR_EN, HIGH);
            delay(500); // According to figure 13 from datasheet
        }

        uint32_t retries = 3;

        while (!getGSMStatus() && (retries > 0) )
        {
            digitalWrite(WL_PWR_ON, HIGH);
            delay(1000);
            digitalWrite(WL_PWR_ON, LOW);

            uint32_t timeout = millis() + (5 * 1000);

            while (!getGSMStatus() && (millis() < timeout) )
            {
                delay(250);
            }

            if (!getGSMStatus())
            {
                retries--;
            }
        }
    }
    else
    {
        digitalWrite(WL_PWR_EN, LOW);
    }

#else
#error Define CONNECTIVITY MODULE
#endif // #if (WIRELESS_MODULE == WIRELESS_MODULE_GSM_SIM800C)
}

/*!
 * \brief Switches power of the Sensors. It performs all additional conditions
 * \param[in] true - power is ON; false - power is OFF
 * \retval None
 */
void MainBoard::sensorPower(bool on)
{
    digitalWrite(PS_VBAT_ENABLE, on ? HIGH : LOW);
}

/*!
 * \brief Returns the power status of the GSM module
 * \retval true - Powered ON
 * \retval false - Powered OFF
 */
bool MainBoard::getGSMStatus()
{
    return (digitalRead(WL_PWR_MON) == HIGH) ? true : false;
}
