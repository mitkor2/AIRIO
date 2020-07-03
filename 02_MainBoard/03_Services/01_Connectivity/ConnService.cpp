/**
 * \file   ConnService.h
 * \brief  Connectivity Service Source Code
 * \author Emil Kirilov
 * \date   20 Sep 2019
 */
#include <ti/sysbios/hal/Seconds.h>
#include <stdlib.h>
#include "config.h"
#include "ConnService.h"
#include "ConnServiceConfig.h"
#include "string.h"
#include "utils.h"
#include "MainBoard.h"


/******************************************************************************/
/* MODEM SWITCH                                                               */
/******************************************************************************/
#if (WIRELESS_MODULE == WIRELESS_MODULE_GSM_SIM800C)
    #define TINY_GSM_MODEM_SIM800
#else
    #error "Modem not defined or not supported"
#endif

#include "TinyGsmClient.h"


/******************************************************************************/
/* STREAM DEBUG                                                               */
/******************************************************************************/
#if (CONNECTION_CLIENT_STUB != 0)
    #include "ClientStub.h"
    static ClientStub client;
#else
    #if (DUMP_AT_COMMANDS != 0)
      #include "StreamDebugger.h"
      static StreamDebugger debugger(CS_WIRELESS_SERIAL, CS_DEBUG_SERIAL);
      static TinyGsm modem(debugger);
    #else
      static TinyGsm modem(CS_WIRELESS_SERIAL);
    #endif

    static TinyGsmClient client(modem);
#endif


/*!
 * \brief Constructor
 * \param cb - pointer to connection timeout callback
 * \retval None
 */
ConnService::ConnService(ConnSvcTimeoutCallback_t cb /* = NULL */) :
        _begun(false),
        _modemStatus(CONN_SVC_MDDEM_STATUS_OFF),
        _http(client),
        _timeout(0),
        _timeoutCallback(cb)
{
}


/*!
 * \brief Destructor
 * \retval None
 */
ConnService::~ConnService()
{
}


/*!
 * \brief Module begin function. Should be called to establish connection with network.
 * \detailed This function starts and initializes the modem, waits for the network connection
 * and opens GPRS connection.
 * \retval true in case of success
 */
bool ConnService::begin()
{
    if (_begun)
    {
        return true;
    }

    _modemStatus = CONN_SVC_MDDEM_STATUS_OFF;

    CS_DEBUG_PRINTLN("Initializing modem... ");

#if (CONNECTION_CLIENT_STUB == 0)

    modemTurnOn();
    delay(100);

    modemSerialStart();

#if (CS_MODEM_POWER_ON_RETRIES > 0)

    uint32_t retries = CS_MODEM_POWER_ON_RETRIES;

    while (!modem.restart())
    {
        // Software restart failed. Try hardware restart
        modemTurnOff();
        modemTurnOn();

        retries--;

        if (retries == 0)
        {
            // RESTART the system !!!!!
            CS_DEBUG_PRINTLN("Not responding! Restart the system!");

            delay(100);

            utilsSystemSwReset();
        }
    }

#endif // (CS_MODEM_POWER_ON_RETRIES > 0)

    CS_DEBUG_PRINT("Modem: ");

    String modemInfo;

    while (modemInfo.length() == 0)
    {
        modemInfo = modem.getModemInfo();
    }

    CS_DEBUG_PRINTLN(modemInfo);


    CS_DEBUG_PRINT("Check SIM... ");

    enum SimStatus sts = modem.getSimStatus(3 * 1000);

    if (sts == SIM_READY)
    {
        CS_DEBUG_PRINTLN("OK");
    }
    else
    {
        CS_DEBUG_PRINTLN("NO SIM CARD!");
        _modemStatus = CONN_SVC_MDDEM_STATUS_NO_SIM;
        board.gsmPower(false);
        modemSerialStop();
        return false;
    }



    CS_DEBUG_PRINT("Connecting to the network... ");

    if (!modem.waitForNetwork())
    {
        CS_DEBUG_PRINTLN("FAILED");
        board.gsmPower(false);
        _modemStatus = CONN_SVC_MDDEM_STATUS_NO_NW;
        return false;
    }

    CS_DEBUG_PRINTLN("OK");


    CS_DEBUG_PRINT("Connecting to ");
    CS_DEBUG_PRINT(CS_GPRS_APN);
    CS_DEBUG_PRINT("... ");

    if (!modem.gprsConnect(CS_GPRS_APN,
                           CS_GPRS_USER,
                           CS_GPRS_PASS))
    {
        CS_DEBUG_PRINTLN("FAILED");
        board.gsmPower(false);
        _modemStatus = CONN_SVC_MDDEM_STATUS_GPRS_FAILED;
        return false;
    }

#endif // (CONNECTION_CLIENT_STUB == 0)

    CS_DEBUG_PRINTLN("OK");
    _modemStatus = CONN_SVC_MODEM_STATUS_CONNECTED;

    _http.setServerName(CS_URL);
    _http.setServerPort(atoi(CS_PORT));

    _begun = true;

    return true;
}


/*!
 * \brief Module end function - closes the network connection and shuts down the modem
 * \retval None
 */
void ConnService::end()
{
    if (!_begun)
    {
        return;
    }

    _begun = false;

    modemTurnOff();
    modemSerialStop();
}


/*!
 * \brief Module loop function - should be called periodically in the main loop
 * \retval None
 */
void ConnService::loop()
{
    if (_begun && millis() > _timeout)
    {
        CS_DEBUG_PRINTLN("Connection Timeout");

        bool keep = false;

        if (_timeoutCallback != NULL)
        {
            keep = _timeoutCallback();
        }

        if (keep)
        {
            keepAlive();
            CS_DEBUG_PRINTLN("Keep Alive");
        }
        else
        {
            // shut down the connection
            CS_DEBUG_PRINTLN("Shut down the connection");

            end();
        }
    }
}


/*!
 * \brief Keeps the connection alive
 * \detailed This function should be called to keep the connection alive. If not called within certain time
 * the ConnService will shutdown the modem automatically if the callback allows that.
 * \retval None
 */
void ConnService::keepAlive()
{
    _timeout = millis() + CS_KEEP_CONNECTION_TIME_MS;
}


/*!
 * \brief This function gets the server time in EPOCH timestamp format
 * \detailed
 * \retval CONN_SVC_OK - API call is OK
 * \retval CONN_SVC_PARAM_ERROR - API error - invalid parameters
 * \retval CONN_SVC_REQUEST_FAILED - Server request failed
 * \retval CONN_SVC_REQUEST_SRV_ERROR - Server responded but with error code
 * \retval CONN_SVC_NO_CONNECTION - No connection
 */
ConnSvcReturn_t ConnService::getServerDateTime(time_t & datetime, bool debug /* = false */)
{
#if (CONNECTION_CLIENT_STUB == 0)
    keepAlive();

    int32_t status;
    String body;
    size_t length;

    ConnSvcReturn_t result;
    String resource = CS_HTTP_PREFIX_GET_TIMESTAMP;

    resource += CS_HTTP_GET_TIMESTAMP_API;
    result = httpGet(resource.c_str(), status, body, length);

    if (result == CONN_SVC_OK)
    {
        if (length >= 10)
        {
            datetime = body.toInt();
        }
        else
        {
            result = CONN_SVC_REQUEST_SRV_ERROR;
        }
    }

    keepAlive();

    return result;
#else
    datetime = 0;
    return CONN_SVC_OK;
#endif
}



/*!
 * \brief Serializes Measurement Data Message
 * \detailed
 * \param[in] data - Pointer to Measurement Data
 * \param[in] readings - Pointer to Measurement Readings. The count of reading is contained in data @see numberOfReadings in ProtoMsrData_t
 * \param[out] buff - pointer to destination buffer
 * \param[in] size - size of the destination buffer
 * \param[in] print - flag that allows data printing in debug console
 * \param[in] debug - flag that shows whether the application is build in DEBUG
 * \retval size_t - the size in bytes of the serialized data
 */
size_t ConnService::msrDataSerialize(ProtoMsrData_t * data,
                                     uint8_t * buff,
                                     size_t size,
                                     bool print /* = false */,
                                     bool debug /* = false */)
{
    if ( (data == NULL) || (buff == NULL) )
    {
        // invalid pointers
        return 0;
    }

    if ( (sizeof(ProtoHeader_t) + sizeof(ProtoMsrData_t)) > size)
    {
        // not enough space in buffer
        return 0;
    }

    memset(buff, 0xEE, size);

    ProtoHeader_t hdr;

    utilsGetUID(hdr.uid);
    hdr.dataSize = sizeof(ProtoMsrData_t);

    if (print)
    {
        CS_DEBUG_PRINTLN("ProtoHeader_t");
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("UID = ");
        for (int i = 0; i < CONFIG_PARAM_GENERAL_UID_SIZE; i++)
        {
            if (hdr.uid[i] < 0x10)
            {
                CS_DEBUG_PRINT('0');
            }
            CS_DEBUG_PRINT(hdr.uid[i], HEX);
        }
        CS_DEBUG_PRINTLN();
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("msgDataSize = "); CS_DEBUG_PRINTLN(hdr.dataSize);
        CS_DEBUG_PRINTLN();

        CS_DEBUG_PRINTLN("ProtoMsrData_t");
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("timestamp = "); CS_DEBUG_PRINTLN(data->timestamp);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("temperature = "); CS_DEBUG_PRINTLN(data->temperature);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("humidity = "); CS_DEBUG_PRINTLN(data->humidity);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("pressure = "); CS_DEBUG_PRINTLN(data->pressure);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("ozone = "); CS_DEBUG_PRINTLN(data->ozone);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("carbonMonoxide = "); CS_DEBUG_PRINTLN(data->carbonMonoxide);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("sulfurDioxide = "); CS_DEBUG_PRINTLN(data->sulfurDioxide);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("nitrogenDioxide = "); CS_DEBUG_PRINTLN(data->nitrogenDioxide);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("pm1_0 = "); CS_DEBUG_PRINTLN(data->pm1_0);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("pm2_5 = "); CS_DEBUG_PRINTLN(data->pm2_5);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("pm4_0 = "); CS_DEBUG_PRINTLN(data->pm4_0);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("pm10 = "); CS_DEBUG_PRINTLN(data->pm10);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("airq = "); CS_DEBUG_PRINTLN(data->airq);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("vbatt = "); CS_DEBUG_PRINTLN(data->vbatt);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("cbatt = "); CS_DEBUG_PRINTLN(data->cbatt);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("fixQuality = "); CS_DEBUG_PRINTLN(data->fixQuality);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("latitude = "); CS_DEBUG_PRINTLN(data->latitude);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("longitude = "); CS_DEBUG_PRINTLN(data->longitude);
        CS_DEBUG_PRINT("\t"); CS_DEBUG_PRINT("altitude = "); CS_DEBUG_PRINTLN(data->altitude);


        CS_DEBUG_PRINTLN();

        CS_DEBUG_PRINTLN();
    }

    size_t offset = 0;
    memcpy(&buff[offset], &hdr, sizeof(ProtoHeader_t));
    offset += sizeof(ProtoHeader_t);

    memcpy(&buff[offset], data, sizeof(ProtoMsrData_t));
    offset += sizeof(ProtoMsrData_t);

    CS_DEBUG_PRINT("BYTES: ");

    for (int i = 0; i < offset; i++)
    {
        CS_DEBUG_PRINT("0x");
        CS_DEBUG_PRINT(buff[i], HEX);

        if (i + 1 < offset)
        {
            CS_DEBUG_PRINT(", ");
        }
    }

    CS_DEBUG_PRINTLN();
    CS_DEBUG_PRINTLN();

    return offset;
}


/*!
 * \brief Sends Measurement Data Post Request to the Server
 * \detailed
 * \param[in] data - Pointer to Measurement Data
 * \param[in] readings - Pointer to Measurement Readings.
 * \param[in] count - readings count. The count of reading is contained in data @see numberOfReadings in ProtoMsrData_t
 * \param[in] debug - flag that shows whether the application is build in DEBUG
 * \retval CONN_SVC_OK - API call is OK
 * \retval CONN_SVC_PARAM_ERROR - API error - invalid parameters
 * \retval CONN_SVC_SERIALIZATION_FAILED - Serialization has failed
 * \retval CONN_SVC_REQUEST_FAILED - Server request failed - server responded but with error
 * \retval CONN_SVC_NO_CONNECTION - No connection
 */
ConnSvcReturn_t ConnService::sendMsrDataSend(ProtoMsrData_t * data, bool debug /* = false */)
{
    keepAlive();

    if (data == NULL)
    {
        return CONN_SVC_PARAM_ERROR;
    }

    static uint8_t buffer[sizeof(ProtoHeader_t) + sizeof(ProtoMsrData_t)];


    size_t bytes = msrDataSerialize(data, buffer, sizeof(buffer), debug, debug);

    if (bytes == 0)
    {
        return CONN_SVC_SERIALIZATION_FAILED;
    }

    String response;
    ConnSvcReturn_t result;
    String resource = CS_HTTP_PREFIX_POST_DATA;

    resource += CS_HTTP_ADD_MEASUREMENTS_API;
    result = httpPostBinary(resource.c_str(), buffer, bytes, response);


   	if (result == CONN_SVC_OK && response.length() > 0)
    {
    	// TODO parse response
   	    CS_DEBUG_PRINT("Response: ");
   	    CS_DEBUG_PRINTLN(response);
    }

    keepAlive();

    return result;
}


/*!
 * \brief Gets Data from the Server by GET Request
 * \detailed
 * \param[in] resource - Pointer to the resource (string)
 * \param[out] status - Request status. 200 for SUCCESS
 * \param[out] body - Response body (string)
 * \param[out] length - Response length in chars
 * \retval CONN_SVC_OK - API call is OK
 * \retval CONN_SVC_PARAM_ERROR - API error - invalid parameters
 * \retval CONN_SVC_SERIALIZATION_FAILED - Serialization has failed
 * \retval CONN_SVC_REQUEST_FAILED - Server request failed - server responded but with error
 * \retval CONN_SVC_NO_CONNECTION - No connection
 */
ConnSvcReturn_t ConnService::httpGet(const char *resource, int32_t &status, String &body, size_t &length)
{
    if (_modemStatus != CONN_SVC_MODEM_STATUS_CONNECTED)
    {
        CS_DEBUG_PRINTLN("HTTP request cannot be done. Modem is not connected!");
        return CONN_SVC_NO_CONNECTION;
    }

    CS_DEBUG_PRINTLN();
    CS_DEBUG_PRINT("Requesting resource ");
    CS_DEBUG_PRINT(resource);
    CS_DEBUG_PRINT("... ");

    int err = _http.get(resource);

    if (err != 0)
    {
        CS_DEBUG_PRINTLN("FAILED");
        _modemStatus = CONN_SVC_MDDEM_STATUS_NO_NW;
        return CONN_SVC_REQUEST_FAILED;
    }

    CS_DEBUG_PRINTLN("OK");

    status = _http.responseStatusCode();

    CS_DEBUG_PRINT("Status: ");
    CS_DEBUG_PRINT(status);
    CS_DEBUG_PRINT(" (");

    if (status == CS_STATUS_OK)
    {
        CS_DEBUG_PRINT("SUCCESS");
    }
    else
    {
        CS_DEBUG_PRINT("ERROR");
    }
    CS_DEBUG_PRINTLN(")");
    CS_DEBUG_PRINTLN();

    CS_DEBUG_PRINTLN("HTTP HEADER:");
    while (_http.headerAvailable())
    {
        String headerName = _http.readHeaderName();
        String headerValue = _http.readHeaderValue();
        CS_DEBUG_PRINTLN(headerName + ": " + headerValue);
    }
    CS_DEBUG_PRINTLN();

    length = _http.contentLength();
    body = _http.responseBody();

    CS_DEBUG_PRINTLN("HTTP RESPONSE:");
    CS_DEBUG_PRINTLN(body);
    CS_DEBUG_PRINTLN();

    _http.stop();

    if (status == CS_STATUS_OK)
    {
        return CONN_SVC_OK;
    }
    else
    {
        return CONN_SVC_REQUEST_SRV_ERROR;
    }
}




/*!
 * \brief Posts Binary Data to Server (POST request)
 * \detailed
 * \param[in] resource - Pointer to the resource (string)
 * \param[in] data - pointer to binary data to be posted
 * \param[in] length - data length in bytes
 * \param[out] body - Response body (string)
 * \retval CONN_SVC_OK - API call is OK
 * \retval CONN_SVC_PARAM_ERROR - API error - invalid parameters
 * \retval CONN_SVC_SERIALIZATION_FAILED - Serialization has failed
 * \retval CONN_SVC_REQUEST_FAILED - Server request failed - server responded but with error
 * \retval CONN_SVC_NO_CONNECTION - No connection
 */
ConnSvcReturn_t ConnService::httpPostBinary(const char *resource, uint8_t *data, size_t length, String &body)
{
    if (_modemStatus != CONN_SVC_MODEM_STATUS_CONNECTED)
    {
        CS_DEBUG_PRINTLN("HTTP request cannot be done. Modem is not connected!");
        return CONN_SVC_NO_CONNECTION;
    }

    CS_DEBUG_PRINTLN();
    CS_DEBUG_PRINT("Requesting resource ");
    CS_DEBUG_PRINT(resource);
    CS_DEBUG_PRINT("... ");

    int err = _http.post(resource, CS_HTTP_CONTENT_TYPE, length, (const byte *) data);

    if (err != 0)
    {
        CS_DEBUG_PRINTLN("FAILED");
        _modemStatus = CONN_SVC_MDDEM_STATUS_NO_NW;
        return CONN_SVC_REQUEST_FAILED;
    }

    CS_DEBUG_PRINTLN("OK");

    int status = _http.responseStatusCode();

    CS_DEBUG_PRINT("Status: ");
    CS_DEBUG_PRINT(status);
    CS_DEBUG_PRINT(" (");

    if (status == CS_STATUS_OK)
    {
        CS_DEBUG_PRINT("SUCCESS");
    }
    else
    {
        CS_DEBUG_PRINT("ERROR");
    }
    CS_DEBUG_PRINTLN(")");
    CS_DEBUG_PRINTLN();

    CS_DEBUG_PRINTLN("HTTP HEADER:");
    while (_http.headerAvailable())
    {
        String headerName = _http.readHeaderName();
        String headerValue = _http.readHeaderValue();
        CS_DEBUG_PRINTLN(headerName + ": " + headerValue);
    }
    CS_DEBUG_PRINTLN();

    body = _http.responseBody();

    CS_DEBUG_PRINTLN("HTTP RESPONSE:");
    CS_DEBUG_PRINTLN(body);
    CS_DEBUG_PRINTLN();

    _http.stop();

    if (status == CS_STATUS_OK)
    {
        return CONN_SVC_OK;
    }
    else
    {
        return CONN_SVC_REQUEST_SRV_ERROR;
    }
}



/*!
 * \brief Turns ON the modem's power supply
 * \detailed
 * \retval none
 */
void ConnService::modemTurnOn()
{
    if (_modemStatus != CONN_SVC_MDDEM_STATUS_OFF)
    {
        return;
    }

    // enable the GSM board power
    board.gsmPower(true);

    _modemStatus = CONN_SVC_MODEM_STATUS_ON;
}


/*!
 * \brief Turns OFF the modem's power supply
 * \detailed
 * \retval none
 */
void ConnService::modemTurnOff()
{
    if (_modemStatus == CONN_SVC_MDDEM_STATUS_OFF)
    {
        return;
    }

#if (CONNECTION_CLIENT_STUB == 0)
    modem.poweroff();
#endif

    // Power OFF sequence
    board.gsmPower(false);

    _modemStatus = CONN_SVC_MDDEM_STATUS_OFF;
}


/*!
 * \brief Modem Hardware Restart - performs Power cycle
 * \detailed
 * \retval none
 */
void ConnService::modemHwRestart()
{
    modemTurnOff();
    modemTurnOn();
}


/*!
 * \brief Modem Software Restart
 * \detailed
 * \retval none
 */
void ConnService::modemSwRestart()
{
#if (CONNECTION_CLIENT_STUB == 0)
    if (_modemStatus != CONN_SVC_MDDEM_STATUS_OFF)
    {
        modem.restart();
    }
#endif
}


/*!
 * \brief Initializes Modem's Serial Interface
 * \detailed
 * \retval none
 */
void ConnService::modemSerialStart()
{
    CS_WIRELESS_SERIAL.begin(CS_WIRELESS_SERIAL_BAUD_RATE); // start the serial
    CS_WIRELESS_SERIAL.flush();
    // clear the UART Rx buffer if there is something
    while (CS_WIRELESS_SERIAL.available() > 0)
    {
        CS_WIRELESS_SERIAL.read();
    }
    delay(100);
}


/*!
 * \brief Deinitializes Modem's Serial Interface
 * \detailed
 * \retval none
 */
void ConnService::modemSerialStop()
{
    CS_WIRELESS_SERIAL.flush();

    while (CS_WIRELESS_SERIAL.available())
    {
        CS_WIRELESS_SERIAL.read();
    }

    CS_WIRELESS_SERIAL.end();

    pinMode(CS_WIRELESS_RX, INPUT);
    pinMode(CS_WIRELESS_TX, INPUT);
}


/*!
 * \brief Returns modem status
 * \detailed
 * \retval CONN_SVC_MDDEM_STATUS_NO_SIM - No SIM card
 * \retval CONN_SVC_MDDEM_STATUS_NO_NW - No Network
 * \retval CONN_SVC_MDDEM_STATUS_GPRS_FAILED - GPRS connection failed
 * \retval CONN_SVC_MDDEM_STATUS_OFF - Modem is powered off
 * \retval CONN_SVC_MODEM_STATUS_ON - Modem is powered on, but not connected
 * \retval CONN_SVC_MODEM_STATUS_CONNECTED - Modem is powered on and connected
 */
ConnSvcModemStatus_t ConnService::getModemStatus() const
{
    return _modemStatus;
}


/*!
 * \brief Returns connection "ready" state
 * \detailed
 * \retval true: Modem is connected
 * \retval false: Modem is NOT connected
 */
bool ConnService::ready()
{
    keepAlive();

    return (_modemStatus == CONN_SVC_MODEM_STATUS_CONNECTED);
}



/*!
 * \brief get modem signal quality in RSSI units (Received signal strength indication)
 * \retval  signal quality in RSSI units
 */
int16_t ConnService::getModemSignalQualityRSSI()
{
    return(modem.getSignalQuality());
}



/*!
 * \brief get modem signal quality in decibel's
 * \retval  signal quality in dB
 */
int16_t ConnService::getModemSignalQualityDb()
{
    return (-115 + (getModemSignalQualityRSSI() * 2) );
}
