#include "snake_state.h"

uint8_t dxl_error;
uint16_t dxl_now_pos;

void enable_motor()
{
	packh->write1ByteTxOnly(porth, 0xFE, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE);
}

void disable_motor()
{
	packh->write1ByteTxOnly(porth, 0xFE, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE);
}

void set_speed_motor(int throttle)
{
	uint16_t S_DATA;

	if (throttle > 0)
	{
		S_DATA = throttle * 5;
	}
	else
	{
		S_DATA = 0;
	}
	packh->write2ByteTxOnly(porth, 0xFE, ADDR_MX_GOAL_SPEED, S_DATA);
}

void ver_wave(robot_state *robot)
{
	int speed_s = 500;
	int amp_ver_s = (80 * robot->throtle) / 100;

	if (robot->modes != V_MODE)
	{
		robot->modes = V_MODE;
		robot->count = 0;

		packh->write2ByteTxOnly(porth, 0xFE, ADDR_MX_GOAL_POSITION, 512);
	}

	set_speed_motor(robot->throtle);

	packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 1));
	Sleep(10);
	packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 3));
	Sleep(10);
	packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 5));
	Sleep(10);
	packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 7));
	Sleep(10);
	packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 9));
	Sleep(10);
	packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 11));
	Sleep(10);
	packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 13));
	Sleep(10);
	packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 15));
	Sleep(10);

	robot->count++;

	//std::cout << "AMP :\t" << amp_ver_s << std::endl;
	//std::cout << "COUNT :\t" << robot->count << std::endl;
}

void sidewind(robot_state* robot)
{
	double x;
	/*int amp_hor_s = 200;
	int amp_ver_s = 120;*/

	int amp_hor_s = (200 * robot->heading) / 100;
	int amp_ver_s = (120 * robot->heading) / 100;

	if (robot->modes != SIDEWIND_MODE)
	{
		robot->modes = SIDEWIND_MODE;
		robot->count = 0;
	}

	x = robot->count + lag_ver / 2;

	packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count));
	Sleep(20);
	packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(20);

	x = robot->count + lag_ver / 2 * 3;

	packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor));
	Sleep(20);
	packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(20);

	x = robot->count + lag_ver / 2 * 5;

	packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 2));
	Sleep(20);
	packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(20);

	x = robot->count + lag_ver / 2 * 7;

	packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 3));
	Sleep(20);
	packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(20);

	x = robot->count + lag_ver / 2 * 9;

	packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 4));
	Sleep(20);
	packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(20);

	x = robot->count + lag_ver / 2 * 11;

	packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 5));
	Sleep(20);
	packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(20);

	x = robot->count + lag_ver / 2 * 13;

	packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 6));
	Sleep(20);
	packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(20);

	x = robot->count + lag_ver / 2 * 15;

	packh->write2ByteTxOnly(porth, DXL_ID16, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 7));
	Sleep(20);
	packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(20);

	robot->count++;

	//std::cout << "AMP :\t" << amp_ver_s << std::endl;
	//std::cout << "AMP :\t" << amp_hor_s << std::endl;
	//std::cout << "COUNT :\t" << robot->count << std::endl;
}
