/**
 * \file   Utils.cpp
 * \brief  Implements utility functions
 * \author Emil Kirilov
 * \date   20 Sep 2019
 */
#include <ti/devices/msp432p4xx/driverlib/sysctl.h>
#include <stdio.h>
#include "Utils.h"
#include "config.h"
#include "MainBoard.h"



/*!
 * \brief Performs some indication activities on reset
 * \retval None
 */
void utilsOnReset()
{
    UTLS_DEBUG_PRINTLN("!!!!!!!!!!!!!!!!! RESET !!!!!!!!!!!!!!!!!");
    UTLS_DEBUG_PRINTLN();

    for (int i = 0; i < 10; i++)
    {
        digitalWrite(LED_YELLOW, !digitalRead(LED_YELLOW));
        delay(100);
    }

    utilsPrintUID();
}



/*!
 * \brief Fills destination with randnum.
 * \detailed Actually it is not a randnum but a CPU unique ID. Used for generating device UID
 * \param[out] dest - Pointer to the destination buffer
 * \param[in] len - Buffer size in Bytes
 * \retval None
 */
void utilsGetRandnum(uint8_t *dest, size_t len)
{
    uint_fast8_t length;
    uint32_t *data;

    SysCtl_getTLVInfo(
            TLV_TAG_RANDNUM,
            0,
            &length,
            &data);

    if (len > length)
    {
        len = length;
    }

    if (data != NULL)
    {
        memcpy(dest, (uint8_t *) data, len);
    }
}


/*!
 * \brief Performs console print of a binary array in hex format
 * \param[in] array - Pointer to the array to be printed
 * \param[in] len - Array size in Bytes
 * \param[in] ln - If true a new line is added at the end
 * \retval None
 */
void utilsPrintArray(const uint8_t *array, size_t len, bool ln /* = true */)
{
#if (UTLS_DEBUG != 0)
    for (int i = len; i > 0; i--)
    {
        int low  = ((array[i - 1]) >> 0) & 0x0F;
        int high = ((array[i - 1]) >> 4) & 0x0F;
        UTLS_DEBUG_PRINT(high, 16);
        UTLS_DEBUG_PRINT(low, 16);
    }

    if (ln)
    {
        UTLS_DEBUG_PRINTLN();
    }
#endif
}


/*!
 * \brief Prints device UID in console
 * \retval None
 */
void utilsPrintUID()
{
#if (UTLS_DEBUG != 0)
    UTLS_DEBUG_PRINTLN(utilsGetUID());
#endif
}


/*!
 * \brief Returns device UID as a string
 * \retval String - Device UID
 */
String utilsGetUID()
{

    uint8_t uid[CONFIG_PARAM_GENERAL_UID_SIZE];

    utilsGetRandnum(uid, sizeof(uid));

    char temp[3];

    String suid = "";

    for (int i = 0; i < CONFIG_PARAM_GENERAL_UID_SIZE; i++)
    {
        sprintf(temp, "%02X", uid[i]);
        suid += temp;
    }

    return suid;
}



void utilsGetUID(uint8_t * uid)
{
    utilsGetRandnum(uid, CONFIG_PARAM_GENERAL_UID_SIZE);
}


/*!
 * \brief Converts hex character to numerical value
 * \retval uint8_t - Numerical value of the hex char
 */
uint8_t utilsHexChar2Uint(char hex)
{
    switch (hex)
    {
        case '0': return  0;
        case '1': return  1;
        case '2': return  2;
        case '3': return  3;
        case '4': return  4;
        case '5': return  5;
        case '6': return  6;
        case '7': return  7;
        case '8': return  8;
        case '9': return  9;
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
        default:
            return  0;
    }
}


/*!
 * \brief Converts hex string to integer.
 * \detailed Used to convert the EPOCH timestamp from HTTP response to 32 bit int
 * \param[in] str - String that contains the number, e.g. "12345"
 * \retval uint32_t - Numerical value of the hex string
 */
uint32_t utilsHexString2Uint(const String str)
{
    uint32_t value = 0;

    for (int i = 0; i < str.length(); i++)
    {
        uint32_t n = utilsHexChar2Uint(str[i]);
        value |= n << ((7 - i) * 4);
    }

    return value;
}


/*!
 * \brief Parses date-time from string and stores it to time_t structure
 * \param[in] str - date-time string
 * \param[out] dateTime - a reference to time_t variable
 * \retval None
 */
void utilsParseDateTime(const char * str, time_t & dateTime)
{
    const char months[12][4] =
    {
     "Jan",
     "Feb",
     "Mar",
     "Apr",
     "May",
     "Jun",
     "Jul",
     "Aug",
     "Sep",
     "Oct",
     "Nov",
     "Dec"
    };

    char day[3];
    char month[4];
    char year[5];
    char hour[3];
    char minutes[3];
    char seconds[3];

    char *pc = (char *) str;

    memcpy(day, pc, 2);
    pc += 3;
    day[2] = '\0';

    memcpy(month, pc, 3);
    pc += 4;
    month[3] = '\0';

    memcpy(year, pc, 4);
    pc += 5;
    year[4] = '\0';

    memcpy(hour, pc, 2);
    pc += 3;
    hour[2] = '\0';

    memcpy(minutes, pc, 2);
    pc += 3;
    minutes[2] = '\0';

    memcpy(seconds, pc, 2);
    pc += 3;
    seconds[2] = '\0';

    struct tm stm;

    stm.tm_mday = atol(day);

    int i;

    for (i = 0; i < 12; i++)
    {
        if (strncmp(month, months[i], 4) == 0)
        {
            break;
        }
    }

    stm.tm_mon = i;
    stm.tm_year = atol(year) - 1900;
    stm.tm_hour = atol(hour);
    stm.tm_min = atol(minutes);
    stm.tm_sec = atol(seconds);
    stm.tm_wday = 0;
    stm.tm_isdst = false;

    /*
     * mktime is messing up leap years because it starts computing them from 1900 because it assumes year 0 is 1900,
     * and your code assumes year 0 is 1970.  The tm_year field in mktime uses an epoch of 1900, as required by the C
     * standard, so you can't use 1970 as the bias. You must use 'year - 1900' as the value of tm_year. Then, if you
     * want to convert the return value to the POSIX 1970-biased number of seconds, subtract 2208988800L seconds (the
     * number of seconds from midnight January 1, 1900 to the POSIX epoch, as defined in RFC 868).
     */
    dateTime = mktime(&stm) - 2208988800L;
}


/*!
 * \brief Waits until user button 1 is pressed and released (clicked)
 * \retval None
 */
void utilsWaitButton1()
{
    while(digitalRead(BUTTON1))
    {
        delay(50);
    }

    while(!digitalRead(BUTTON1))
    {
        delay(50);
    }
}


/*!
 * \brief Waits until user button 2 is pressed and released (clicked)
 * \retval None
 */
void utilsWaitButton2()
{
    while(digitalRead(BUTTON2))
    {
        delay(50);
    }

    while(!digitalRead(BUTTON2))
    {
        delay(50);
    }
}


/*!
 * \brief Checks whether button 1 is pressed for longer time
 * \retval None
 */
bool utilsCheckButton1()
{
    if (!digitalRead(BUTTON1))
    {
        uint32_t timeout = millis() + 500;

        while (!digitalRead(BUTTON1) && millis() < timeout)
        {
            delay(50);
        }

        return !digitalRead(BUTTON1) ? true : false;
    }

    return false;
}


/*!
 * \brief Checks whether button 2 is pressed for longer time
 * \retval None
 */
bool utilsCheckButton2()
{
    if (!digitalRead(BUTTON2))
    {
        uint32_t timeout = millis() + 500;

        while (!digitalRead(BUTTON2) && millis() < timeout)
        {
            delay(50);
        }

        return !digitalRead(BUTTON2) ? true : false;
    }

    return false;
}


/*!
 * \brief Checks whether both user buttons are held together
 * \retval None
 */
bool utilsCheckBothButtons()
{
    if (!digitalRead(BUTTON1) && !digitalRead(BUTTON2))
    {
        uint32_t timeout = millis() + 500;

        while (!digitalRead(BUTTON1) && !digitalRead(BUTTON2) && millis() < timeout)
        {
            delay(50);
        }

        return (!digitalRead(BUTTON1) && !digitalRead(BUTTON2)) ? true : false;
    }

    return false;
}



/*!
 * \brief Wrapper function
 * \retval None
 */
void utilsCRC32setSeed(uint32_t seed, uint_fast8_t crcType)
{
    MAP_CRC32_setSeed(seed, crcType);
}



/*!
 * \brief Wrapper function
 * \retval None
 */
void utilsCRC32set32BitData(uint32_t dataIn)
{
    MAP_CRC32_set32BitData(dataIn);
}



/*!
 * \brief Wrapper function
 * \retval None
 */
uint32_t utilsCRC32getResult(uint_fast8_t crcType)
{
    return MAP_CRC32_getResult(crcType);
}



/*!
 * \brief readLine function. Reads the user's input until the \n enter character is found
 * Allows user to use the backspace key
 * \param[in] buffer , when the entered string is stored
 * \param[in] size - the size of the buffer
 * \param[in] timeout - time interval within the user has to enter the password. 0 is for infinity
 * \retval readIndex - returns the size of the string entered by the user
 */
bool utilsReadLine(char * buffer, const size_t size, const uint32_t timeout /* = 0 */)
{
    CONSOLE_READ(); // flush the serial buffer with one char

    buffer[0] = '\0';

    size_t readIndex = 0;
    uint32_t timer;

    if (timeout != 0)
    {
        timer = millis() + timeout;
    }
    else
    {
        timer = 0xFFFFFFFF; // infinity
    }

    while (millis() < timer)
    {
        int c = CONSOLE_READ();

        if (c == -1)
        {
            delay(1);
            continue;
        }

        if (c == ASCII_BACKSPACE || c == ASCII_DELETE)   // Backspace/Delete characters
        {
            if (readIndex < 1)
            {
                continue;
            }

            readIndex--;

            buffer[readIndex] = '\0'; // Put a terminator on the string in case we are finished

            CONSOLE_PRINT((char) ASCII_BACKSPACE); // Move back one space
            CONSOLE_PRINT(' '); // Put a blank there to erase the letter from the terminal
            CONSOLE_PRINT((char) ASCII_BACKSPACE); // Move back again

            continue;
        }


        CONSOLE_PRINT((char)c); // Echo the user's input


        if (c == ASCII_ESC)
        {
            CONSOLE_PRINTLN('A');       //Dummy printing to overload the Escape char, which is printed and result in deleting the first symbol from the console print.
            return false;
        }
        else if (c == '\r' || c == '\n')
        {
            buffer[readIndex] = '\0';

            break;
        }
        else if (readIndex < size)
        {
            buffer[readIndex] = (char) c;
            readIndex++;
        }
    }

    CONSOLE_PRINTLN();

    return true;
}



/*!
 * \brief printLine function. Prints dash line on the serial console to distinguish
 * different menu pages
 * \retval None
 */
void utilsPrintLine()
{
    CONSOLE_PRINTLN("\n----------------------------------------\n");
}


/*!
 * \brief readPress function. Checks input from the user via the Serial console.
 * \param[in] waitForInput flag, if true the function will exit only after keyboard key is pressed,
 *  if false will check and if no key will return SPACE
 * \retval returns the pressed char
 */
char utilsReadKey(bool waitForInput)
{
    if (CONSOLE_AVAILABLE())
    {
        return(CONSOLE_READ());
    }
    else if (waitForInput)
    {
        while(!CONSOLE_AVAILABLE())
        {
            delay(1);
        }
        return(CONSOLE_READ());
    }
    else
    {
        return(' ');
    }
}


/*!
 * \brief strtolong function. Convert a string to a long 32 bit integer
 * \retval long 32 bit integer
 */
uint32_t utilsStr2Long(const char* str)
{
    uint32_t l = 0;

    while (*str >= '0' && *str <= '9')
    {
        l = l * 10 + (*str++ - '0');
    }

    return l;
}


/*!
 * \brief Restarts the McU
 * \retval None
 */
void utilsSystemSwReset()
{
    MAP_Interrupt_disableMaster();
    MAP_SysCtl_rebootDevice();
}
