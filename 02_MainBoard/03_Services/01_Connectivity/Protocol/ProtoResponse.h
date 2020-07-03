/**
 * \file   ProtoResponse.h
 * \brief  Protocol Responses
 * \author Emil Kirilov
 * \date   20 Sep 2019
 */
#ifndef __PROTO_RESPONSE_H__
#define __PROTO_RESPONSE_H__

/*!
 * enum Protocol Responses
 */
typedef enum
{
    NO_UPDATE = 0,      /**< No Update is available */
    UPDATE_AVAILABLE,   /**< Update Available response */
    UPDATE_CHUNK        /**< Update Chunk in response */
} ProtoResponseID_t;

#endif // __PROTO_RESPONSE_H__
