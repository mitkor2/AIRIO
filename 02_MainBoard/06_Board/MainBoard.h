/**
 * \file MainBoard.h
 * \brief This file implements handling of the main board -
 *  pin definitions, power supply switching, etc
 * \author Emil Kirilov
 * \date 20 Sep 2019
 */
#ifndef __MS_BOARD_H__
#define __MS_BOARD_H__

#include "config.h"
#include "MSGPIOs.h"


/*!
 * MainBoard class
 */
class MainBoard
{
public:
    virtual void init();
    virtual void power(bool on);
    virtual void gsmPower(bool on);
    virtual void sensorPower(bool on);

    virtual bool getGSMStatus();

private:

};


/*!
 * Global variable declaration
 */
extern MainBoard board;


#endif // __MS_BOARD_H__
