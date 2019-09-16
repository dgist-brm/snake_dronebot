#pragma once
#include "defines.h"
#include "connection.h"
#include "dynamixel_sdk.h"
#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>



struct robot_state
{
	int modes = 0;
	int count = 0;
	//0 no action
	//
	//
	int throtle = 0;
	int heading = 0;

	int preheading = 0;
};

const double lag_ver = 2 * M_PI / 6;
const double lag_hor = 2 * M_PI / 6;

extern dynamixel::PortHandler* porth;
extern dynamixel::PacketHandler* packh;

void enable_motor();
void disable_motor();
void set_speed_motor(int throttle);
void ver_wave(robot_state *robot);
void sidewind(robot_state* robot);
void finding(robot_state* robot);