#include "snake_state.h"

uint8_t dxl_error;
uint16_t dxl_now_pos;

void enable_motor()
{
	packh->write1ByteTxOnly(porth, 0xFE, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE);
	packh->write2ByteTxOnly(porth, 0xFE, ADDR_TOQUE_LIMIT, 0x3FF);
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

	if (robot->throtle >= 0)
	{
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
	}
	else
	{
		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 1 + M_PI));
		Sleep(10);
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 3 + M_PI));
		Sleep(10);
		packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 5 + M_PI));
		Sleep(10);
		packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 7 + M_PI));
		Sleep(10);
		packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 9 + M_PI));
		Sleep(10);
		packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 11 + M_PI));
		Sleep(10);
		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 13 + M_PI));
		Sleep(10);
		packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 15 + M_PI));
		Sleep(10);
	}


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

	set_speed_motor(robot->throtle);

	if (robot->heading >= 0)
	{
		x = robot->count + lag_ver / 2;

		packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 3;

		packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 5;

		packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 2));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 7;

		packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 3));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 9;

		packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 4));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 11;

		packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 5));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 13;

		packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 6));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 15;

		packh->write2ByteTxOnly(porth, DXL_ID16, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 7));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);
	}
	else
	{
		x = robot->count + lag_ver / 2 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 3 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 5 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 2));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 7 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 3));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 9 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 4));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 11 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 5));
		packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 13 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 6));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);

		x = robot->count + lag_ver / 2 * 15 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID16, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 7));
		Sleep(15);
		packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(15);
	}
	robot->count++;

	//std::cout << "AMP :\t" << amp_ver_s << std::endl;
	//std::cout << "AMP :\t" << amp_hor_s << std::endl;
	//std::cout << "COUNT :\t" << robot->count << std::endl;
}

void finding(robot_state* robot)
{
	if (robot->modes != FIND_MODE)
	{
		robot->modes = FIND_MODE;
		robot->count = 0;
	}
	int amp_x = -1 * robot->throtle;
	int amp_y = -1 * robot->heading;

	uint16_t x = amp_x * 2 + 512;
	uint16_t y = amp_y * 2 + 512;

	set_speed_motor(270);

	packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, x); //512 is a middle position value of a AX-12
	packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 300); //512 is a middle position value of a AX-12
	packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 300); //512 is a middle position value of a AX-12
	packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 300); //512 is a middle position value of a AX-12

	packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, y);

	std::cout << amp_x << std::endl;
	std::cout << amp_y << std::endl;
	std::cout << x << std::endl;
	std::cout << y << std::endl;

}
