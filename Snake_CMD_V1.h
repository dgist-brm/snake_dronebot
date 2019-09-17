#pragma once

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <Xinput.h>
#include <ctime>
#include <fstream>
#include <string>

#include "connection.h"
#include "defines.h"
#include "snake_state.h"
#include "dynamixel_sdk.h"

dynamixel::PortHandler* porth;
dynamixel::PacketHandler* packh;

XINPUT_STATE Xstate;
int inputMode;
int boot_time = 0;
int mode_time = 0;
bool isLogged;

static robot_state robot;

int analogToSpeed(short analog);
int buttonToMode(WORD Buttons);
