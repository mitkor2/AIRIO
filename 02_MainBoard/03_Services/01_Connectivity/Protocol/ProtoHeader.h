/**
 * \file   ProtoHeaders.h
 * \brief  Contains protocol message common header definition
 * \author Emil Kirilov
 * \date   20 Sep 2019
 */
#ifndef __PROTO_HEADER_H__
#define __PROTO_HEADER_H__

/*!
 * Proto Header structure
 */
typedef struct
{
    uint8_t uid[CONFIG_PARAM_GENERAL_UID_SIZE];
    uint32_t dataSize;
} ProtoHeader_t;

#endif // __PROTO_HEADER_H__
