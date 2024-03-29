#pragma once
#pragma warning(disable:4996)

#include "defines.h"
#include "connection.h"
#include "dynamixel_sdk.h"
#include <Windows.h>
#include <ctime>

#define _USE_MATH_DEFINES
#include <math.h>



struct robot_state
{
	time_t boottime = 0;
	time_t modetime = 0;

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
void turning(robot_state* robot);
void turning2(robot_state* robot);
void sinuslift(robot_state* robot);
void stopmode(robot_state* robot);