#pragma once

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <Xinput.h>

#include "connection.h"
#include "defines.h"
#include "snake_state.h"
#include "dynamixel_sdk.h"

dynamixel::PortHandler* porth;
dynamixel::PacketHandler* packh;

XINPUT_STATE Xstate;
robot_state robot;

int count = 0;