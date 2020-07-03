/*
 * ConnServiceConfig.h
 *
 *  Created on: May 5, 2020
 *      Author: Emil Kirilov
 */

#ifndef __CONN_SERVICE_CONFIG_H__
#define __CONN_SERVICE_CONFIG_H__

#include "config.h"

#define CS_WIRELESS_SERIAL                  (WIRELESS_SERIAL)
#define CS_WIRELESS_SERIAL_BAUD_RATE        (WIRELESS_SERIAL_BAUD_RATE)
#define CS_WIRELESS_RX                      (WL_RX)
#define CS_WIRELESS_TX                      (WL_TX)

#define CS_DEBUG_SERIAL                     (CONSOLE_SERIAL)

#define CS_STATUS_OK                        (200) // HTTP

#define CS_KEEP_CONNECTION_TIME_MS          (CONFIG_KEEP_CONNECTION_TIME_MS)
#define CS_MODEM_POWER_ON_RETRIES           (0)


#define CS_URL                              (CONFIG_SERVER_URL)
#define CS_PORT                             (CONFIG_SERVER_PORT)

#define CS_GPRS_APN                         (CONFIG_GPRS_APN)
#define CS_GPRS_USER                        (CONFIG_GPRS_USER)
#define CS_GPRS_PASS                        (CONFIG_GPRS_PASS)

#define CS_HTTP_PREFIX_GET_TIMESTAMP        (CONFIG_SERVER_GET_TIMESTAMP_HTTP_PREFIX)
#define CS_HTTP_PREFIX_POST_DATA            (CONFIG_SERVER_POST_DATA_HTTP_PREFIX)

#define CS_HTTP_GET_TIMESTAMP_API           (CONFIG_HTTP_GET_TIMESTAMP_API)
#define CS_HTTP_ADD_MEASUREMENTS_API        (CONFIG_HTTP_ADD_MEASUREMENTS_API)
#define CS_HTTP_GET_SETTINGS_API            (CONFIG_HTTP_GET_SETTINGS_API)

#define CS_HTTP_CONTENT_TYPE                (CONFIG_HTTP_CONTENT_TYPE)

#endif /* __CONN_SERVICE_CONFIG_H__ */
