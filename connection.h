#pragma once

#include <stdint.h>
#include <iostream>
#include "dynamixel_sdk.h"
#include "defines.h"


extern uint8_t dxl_error;
extern uint16_t dxl_now_pos;

int setComm(dynamixel::PortHandler *porth, dynamixel::PacketHandler *packh, const char* port, float version, int baudrate);
void closeComm(dynamixel::PortHandler* porth);