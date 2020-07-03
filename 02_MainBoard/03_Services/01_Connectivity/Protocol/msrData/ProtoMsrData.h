/**
 * \file   ProtoMsrData.h
 * \brief  Send Measured Data Protocol Definition
 * \author Emil Kirilov
 * \date   20 Sep 2019
 */
#ifndef __PROTO_MSR_DATA_H__
#define __PROTO_MSR_DATA_H__

#define PROTO_DATA_FRACT_VALUE_MULTIPLIER   (100.0)
#define PROTO_DATA_GPS_VALUE_MULTIPLIER     (10000000.0)
#define PROTO_DATA_INVALID_VALUE            (-1000)


/*!
 * Data Structure
 */
typedef struct
{
    uint32_t timestamp;
    int32_t temperature;
    int32_t humidity;
    int32_t pressure;
    int32_t ozone;
    int32_t carbonMonoxide;
    int32_t sulfurDioxide;
    int32_t nitrogenDioxide;
    int32_t pm1_0;
    int32_t pm2_5;
    int32_t pm4_0;
    int32_t pm10;
    int32_t airq;
    int32_t vbatt;
    int32_t cbatt;
    uint32_t fixQuality;
    int32_t latitude;
    int32_t longitude;
    int32_t altitude;
} ProtoMsrData_t;

#endif // __PROTO_MSR_DATA_H__
