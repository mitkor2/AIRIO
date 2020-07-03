/**
 * \file config.h
 * \brief Configuration interface header file
 * \author Emil Kirilov
 * \date 20 Sep 2019
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <time.h>
#include "Arduino.h"


#define CONFIG_PARAM_GENERAL_UID_SIZE (12)



#define CONSOLE_SERIAL                  (Serial)
#define CONSOLE_SERIAL_BAUD_RATE        (115200)



#define WIRELESS_MODULE_GSM_SIM800C     (1)
#define WIRELESS_MODULE_GSM_SARA_G340   (2) // NOT USED

#define WIRELESS_MODULE                 (WIRELESS_MODULE_GSM_SIM800C)
#define WIRELESS_SERIAL                 (Serial1)
#define WIRELESS_SERIAL_BAUD_RATE       (115200)

#define CONFIG_SIM_PIN                  ("0000")
#define CONFIG_GPRS_APN                 ("")
#define CONFIG_GPRS_USER                ("")
#define CONFIG_GPRS_PASS                ("")


#define CONFIG_SERVER_URL                   ("zoro-api.gizmos.link")
#define CONFIG_SERVER_PORT                  ("80")
#define CONFIG_SERVER_GET_TIMESTAMP_HTTP_PREFIX       ("/api/v1/connbin/")
#define CONFIG_SERVER_POST_DATA_HTTP_PREFIX       ("/api/v1/airio/")
#define CONFIG_HTTP_GET_TIMESTAMP_API       ("getTimestamp")
#define CONFIG_HTTP_ADD_MEASUREMENTS_API    ("postData")
#define CONFIG_HTTP_CONTENT_TYPE            ("application/octet-stream")
//#define CONFIG_HTTP_CONTENT_TYPE            ("application/json")


//#define CONFIG_SUSPEND_TIME_MS          (         60 * 1000)    /**< DEBUG: Connection suspend time in MILISECONDS */
#define CONFIG_KEEP_CONNECTION_TIME_MS  (          5 * 1000)    /**< DEBUG: Connection keep alive timeout in MILISECONDS */
//#define CONFIG_SENSORS_WARMUP_TIME_MS   (          2  *1000)    /**< DEBUG: Sensor warm-up time after power on in MILISECONDS */

//#define CONFIG_SEND_RETRIES_COUNT       (3)                     /**< DEBUG: Number of server connection retries */
//#define CONFIG_SEND_RETRY_INTERVAL_MS   (          5 * 1000)    /**< DEBUG: Time interval between connection retries in MILLISECONDS */

//#define CONFIG_GET_SRVTIME_INTERVAL_MS  (24 * 60 * 60 * 1000)   /**< DEBUG: Server time update interval in MILLISECONDS */

//#define CONFIG_SEND_DATA_READINGS_COUNT         (100)               /**< Maximum number of readings to be sent to the server in one request */

//#define CONFIG_LOW_BATT_VOLTAGE_MV              (4000)              /**< Low battery voltage in MILLIVOLTS */
//#define CONFIG_FULL_BATT_VOLTAGE_MV             (6000)              /**< Full battery voltage in MILLIVOLTS */

//#define CONFIG_RESET_AFTER_SUSPEND_ENABLE       (1)


//                                                           HH * MM * SS
#define CONFIG_GENERAL_DATA_SEND_INTERVAL_DEFAULT           (      5 * 60)  /**< DEBUG: Default Send Interval in SECONDS */
#define CONFIG_GENERAL_DATA_SEND_INTERVAL_MIN               (      1 * 60)  /**< DEBUG: Send Interval MINIMUM in SECONDS. Values below that minimum are not allowed! */
#define CONFIG_GENERAL_DATA_SEND_INTERVAL_MAX               (12 * 60 * 60)  /**< DEBUG: Send Interval MAXIMUM in SECONDS. Values above that maximum are not allowed! */

//#define CONFIG_RUNTIME_GENERAL_GET_UID(uid)             config.getUID(uid)
//#define CONFIG_RUNTIME_GENERAL_DEBUG_LEVEL              config.getDebugLevel()
//#define CONFIG_RUNTIME_GENERAL_DATA_SEND_INTERVAL       config.getDataSendInterval()
//#define CONFIG_RUNTIME_GENERAL_SENSOR_READ_INTERVAL     config.getSensorReadInterval()

/*
#define CONFIG_RUNTIME_CONN_HTTP_PREFIX                 config.getHttpPrefix()
#define CONFIG_RUNTIME_CONN_URL                         config.getUrl()
#define CONFIG_RUNTIME_CONN_PORT                        config.getPort()
#define CONFIG_RUNTIME_CONN_SIM_PIN                     config.getSimPin()
#define CONFIG_RUNTIME_CONN_GPRS_APN                    config.getGprsAPN()
#define CONFIG_RUNTIME_CONN_GPRS_USER                   config.getGprsUser()
#define CONFIG_RUNTIME_CONN_GPRS_PASS                   config.getGprsPass()
*/

/********************************************************/
/*                    DEBUG CONFIG                      */
/********************************************************/

#define DUMP_AT_COMMANDS                    (0)                     /**< When this define is set to 1 it will dump GSM AT communication to Debug Serial */
#define CONNECTION_CLIENT_STUB              (0)                     /**< When set to 1 the connection client is stubed. It is used to debug serialization */

/*!
 * This macro should be called before using the DEBUG API - DEBUG_PRINT() OR DEBUG_PRINTLN()
 */
#define CONSOLE_START()       { CONSOLE_SERIAL.begin(CONSOLE_SERIAL_BAUD_RATE); }

/*
 * This macro should be called when DEBUG console log is not needed anymore. It ensures that
 * the module is stopped after all send queue is flushed. UART pins are set in high Z for LP mode.
 */
#define CONSOLE_STOP()        { delay(200); CONSOLE_SERIAL.end(); pinMode(BHS_DBG_RX, INPUT); pinMode(BHS_DBG_TX, INPUT); }

/*!
 * This macro is similar to Serial.print() but ensures the call of the proper Serial object
 */
#define CONSOLE_PRINT(...)    { CONSOLE_SERIAL.print(__VA_ARGS__); }

/*!
 * This macro is similar to Serial.println() but ensures the call of the proper Serial object
 */
#define CONSOLE_PRINTLN(...)  { CONSOLE_SERIAL.println(__VA_ARGS__); }


/*!
 * This macro is similar to Serial.read() but ensures the call of the proper Serial object
 */
#define CONSOLE_READ()        CONSOLE_SERIAL.read()


/*!
 * This macro is similar to Serial.available() but ensures the call of the proper Serial object
 */
#define CONSOLE_AVAILABLE()   CONSOLE_SERIAL.available()


/*!
 * This macro can be called before using DEBUG_PRINT() OR DEBUG_PRINTLN()
 * in order to dump module and line in debug console
 */
#define DEBUG_BEGIN_PRINT(module) \
                                { \
                                    CONSOLE_SERIAL.print("["); \
                                    CONSOLE_SERIAL.print(module); \
                                    CONSOLE_SERIAL.print("] "); \
                                    CONSOLE_SERIAL.print("(L: "); \
                                    CONSOLE_SERIAL.print(__LINE__); \
                                    CONSOLE_SERIAL.print(") - "); \
                                }

/*!
 * This macro should be called before using the DEBUG API - DEBUG_PRINT() OR DEBUG_PRINTLN()
 */
//#define DEBUG_START()       { CONSOLE_SERIAL_START(); }

/*
 * This macro should be called when DEBUG console log is not needed anymore. It ensures that
 * the module is stopped after all send queue is flushed. UART pins are set in high Z for LP mode.
 */
//#define DEBUG_STOP()        { CONSOLE_SERIAL_STOP(); }

/*!
 * This macro is similar to Serial.print() but ensures the call of the proper Serial object
 */
#define DEBUG_PRINT(...)    { CONSOLE_SERIAL.print(__VA_ARGS__); }

/*!
 * This macro is similar to Serial.println() but ensures the call of the proper Serial object
 */
#define DEBUG_PRINTLN(...)  { CONSOLE_SERIAL.println(__VA_ARGS__); }


#ifdef __DEBUG
    #define GENERAL_DEBUG               (1)
    #define BEEHIVE_SCALE_APP_DEBUG     (1)
    #define CONFIG_DEBUG                (1)
    #define UTLS_DEBUG                  (1)
    #define WEIGHT_SVC_DEBUG            (1)
    #define CONN_SERVICE_DEBUG          (1)
#else
    #define GENERAL_DEBUG               (0)
    #define BEEHIVE_SCALE_APP_DEBUG     (0)
    #define CONFIG_DEBUG                (0)
    #define UTLS_DEBUG                  (0)
    #define WEIGHT_SVC_DEBUG            (0)
    #define CONN_SERVICE_DEBUG          (0)
#endif




#if (GENERAL_DEBUG)
    #define GEN_DEBUG_PRINT             DEBUG_PRINT
    #define GEN_DEBUG_PRINTLN           DEBUG_PRINTLN
#else
    #define GEN_DEBUG_PRINT(...)
    #define GEN_DEBUG_PRINTLN(...)
#endif


#if (BEEHIVE_SCALE_APP_DEBUG != 0)
    #define BHSA_DEBUG_PRINT            DEBUG_PRINT
    #define BHSA_DEBUG_PRINTLN          DEBUG_PRINTLN
    #define BHSA_DEBUG_SERIAL_FLUSH()   { CONSOLE_SERIAL.flush(); }
#else
    #define BHSA_DEBUG_PRINT(...)
    #define BHSA_DEBUG_PRINTLN(...)
    #define BHSA_DEBUG_SERIAL_FLUSH()
#endif



#if (CONFIG_DEBUG != 0)
    #define CFG_DEBUG_PRINT             DEBUG_PRINT
    #define CFG_DEBUG_PRINTLN           DEBUG_PRINTLN
#else
    #define CFG_DEBUG_PRINT(...)
    #define CFG_DEBUG_PRINTLN(...)
#endif




#if (UTLS_DEBUG != 0)
    #define UTLS_DEBUG_PRINT            DEBUG_PRINT
    #define UTLS_DEBUG_PRINTLN          DEBUG_PRINTLN
#else
    #define UTLS_DEBUG_PRINT(...)
    #define UTLS_DEBUG_PRINTLN(...)
#endif




#if (WEIGHT_SVC_DEBUG != 0)
    #define WS_DEBUG_PRINT              DEBUG_PRINT
    #define WS_DEBUG_PRINTLN            DEBUG_PRINTLN
#else
    #define WS_DEBUG_PRINT(...)
    #define WS_DEBUG_PRINTLN(...)
#endif



#if (CONN_SERVICE_DEBUG != 0)
    #define CS_DEBUG_PRINT              DEBUG_PRINT
    #define CS_DEBUG_PRINTLN            DEBUG_PRINTLN
#else
    #define CS_DEBUG_PRINT(...)
    #define CS_DEBUG_PRINTLN(...)
#endif



#endif // __CONFIG_H__
