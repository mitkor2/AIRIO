/**
 * \file   Utils.h
 * \brief  Implements utility functions
 * \author Emil Kirilov
 * \date   20 Sep 2019
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <Arduino.h>
#include <time.h>
extern "C" {
#include <driverlib.h>
}

#define ASCII_BACKSPACE         (0x08)
#define ASCII_DELETE            (0x7f)
#define ASCII_ESC               (0x1B)


void utilsOnReset();
void utilsGetRandnum(uint8_t *dest, size_t len);
void utilsPrintUID();
String utilsGetUID();
void utilsGetUID(uint8_t *uid);
void utilsPrintArray(const uint8_t *array, size_t len, bool ln = true);

uint8_t utilsHexChar2Uint(char hex);
uint32_t utilsHexString2Uint(const String str);
void utilsParseDateTime(const char * str, time_t & dateTime);
void utilsPrintBootloaderData();


void utilsWaitButton1();
void utilsWaitButton2();

bool utilsCheckButton1();
bool utilsCheckButton2();

bool utilsCheckBothButtons();

void utilsCRC32setSeed(uint32_t seed, uint_fast8_t crcType);
void utilsCRC32set32BitData(uint32_t dataIn);
uint32_t utilsCRC32getResult(uint_fast8_t crcType);

bool utilsReadLine(char * buff, const size_t size, const uint32_t timeout = 0);
void utilsPrintLine();

char utilsReadKey(bool waitForInput);

uint32_t utilsStr2Long(const char* str);

void utilsSystemSwReset();

/*!
 * Returns the smaller of 2 values
 */
#define MIN(a, b)   ((a < b) ? a : b)

#endif //__UTILS_H__
