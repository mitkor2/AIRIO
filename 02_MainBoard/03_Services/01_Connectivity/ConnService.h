/**
 * \file   ConnService.h
 * \brief  Connectivity Service - An abstraction layer implements server communication
 * \author Emil Kirilov
 * \date   20 Sep 2019
 */
#ifndef __CONN_SERVICE_H__
#define __CONN_SERVICE_H__

#include "Proto.h"
#include "config.h"
#include "HttpClient.h"

/*!
 * \brief enum Connectivity Service API Return values
 */
typedef enum
{
    CONN_SVC_OK = 0,                /**< API call is OK */
    CONN_SVC_PARAM_ERROR,           /**< API error - invalid parameters */
    CONN_SVC_SERIALIZATION_FAILED,  /**< Serialization has failed */
    CONN_SVC_REQUEST_FAILED,        /**< Server request failed */
    CONN_SVC_REQUEST_SRV_ERROR,     /**< Server responded but with error code */
    CONN_SVC_NO_CONNECTION          /**< No connection */
} ConnSvcReturn_t;


/*!
 * \brief enum Modem states
 */
typedef enum
{
    CONN_SVC_MDDEM_STATUS_NO_SIM = -3,      /**< No SIM card */
    CONN_SVC_MDDEM_STATUS_NO_NW = -2,       /**< No Network */
    CONN_SVC_MDDEM_STATUS_GPRS_FAILED = -1, /**< GPRS connection failed */
    CONN_SVC_MDDEM_STATUS_OFF,              /**< Modem is powered off */
    CONN_SVC_MODEM_STATUS_ON,               /**< Modem is powered on, but not connected */
    CONN_SVC_MODEM_STATUS_CONNECTED,        /**< Modem is powered on and connected */
} ConnSvcModemStatus_t;


/*!
 * \brief Keep Connection alive callback function type - used to update connection timeout timer
 */
typedef bool (* ConnSvcTimeoutCallback_t)(void); // return true to keep the connection Alive


/*!
 * \brief Connectivity Service class. Implements the server communication logic
 */
class ConnService
{
public:
    ConnService(ConnSvcTimeoutCallback_t cb = NULL);
    ~ConnService();

public:
    bool begin();
    void loop();
    void end();

    bool ready();

    ConnSvcModemStatus_t getModemStatus() const;

    ConnSvcReturn_t sendMsrDataSend(ProtoMsrData_t * data,
                                    bool debug = false);

    ConnSvcReturn_t getServerDateTime(time_t & datetime,
                                      bool debug = false);

    static size_t msrDataSerialize(ProtoMsrData_t * data,
                                   uint8_t * buff,
                                   size_t size,
                                   bool print = false,
                                   bool debug = false);

    static int16_t getModemSignalQualityDb();
    static int16_t getModemSignalQualityRSSI();


private:
    void modemTurnOn();
    void modemTurnOff();
    void modemHwRestart();
    void modemSwRestart();
    void modemSerialStart();
    void modemSerialStop();

    void keepAlive();

    ConnSvcReturn_t httpGet(const char *resource,
                            int32_t &status,
                            String &body,
                            size_t &length);

    ConnSvcReturn_t httpPostBinary(const char *resource,
                                   uint8_t * data,
                                   size_t length,
                                   String &body);

private:
    bool                    _begun;             /**< prevents multiple calls of begin() and end() functions as well
                                                     as API calls without begin() */
    ConnSvcModemStatus_t    _modemStatus;       /**< current modem status */
    const char *            _serviceHost;       /**< HOST container */
    uint16_t                _servicePort;       /**< PORT container */
    HttpClient              _http;              /**< HttpClient - responsible for connection and HTTP GET/POST */
    uint32_t                _timeout;           /**< used for different timers, depending on the state */
    ConnSvcTimeoutCallback_t _timeoutCallback;  /**< timeout callback - if initialized it allows the upper layer to control
                                                     connection close timeout */
};


#endif // __SKETCH_CONNECTION_H__
