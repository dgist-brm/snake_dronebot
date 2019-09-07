#pragma once
#include "defines.h"
#include "connection.h"
#include "dynamixel_sdk.h"


struct robot_state
{
	int modes;
	//0 no action
	//
	//
	float throtle;
	float heading;
};

extern dynamixel::PortHandler* porth;
extern dynamixel::PacketHandler* packh;

void enable_motor();
void disable_motor(dynamixel::PacketHandler *packh);