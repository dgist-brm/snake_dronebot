#include "snake_state.h"

uint8_t dxl_error;
uint16_t dxl_now_pos;

void enable_motor()
{
	packh->write1ByteTxOnly(porth, 0xFE, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE);
	packh->write2ByteTxOnly(porth, 0xFE, ADDR_TOQUE_LIMIT, 0x2BC);
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
	int amp_ver_s = (92 * robot->throtle) / 100;
	int amp_hor_s = 25;
	int delaytime = 7;

	if (robot->modes != V_MODE)
	{
		robot->modes = V_MODE;
		robot->count = 0;
		robot->modetime = time(0);

		enable_motor();
		packh->write2ByteTxOnly(porth, 0xFE, ADDR_MX_GOAL_POSITION, 512);
	}

	set_speed_motor(robot->throtle);

	if (robot->throtle >= 0)
	{
		if (robot->heading < 0)
		{
			if (robot->preheading != 1)
			{
				robot->preheading = 1;
				int verdel = 3;

				packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 + (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 + (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 + (amp_hor_s));
				Sleep(verdel);
			}
		}
		else if (robot->heading == 0)
		{
			if (robot->preheading != 0)
			{
				robot->preheading = 0;
				int verdel = 2;

				packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512);
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512);
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512);
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512);
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512);
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512);
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512);
				Sleep(verdel);
			}
		}
		else if (robot->heading > 0)
		{
			if (robot->preheading != -1)
			{
				robot->preheading = -1;
				int verdel = 2;

				packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 - (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 - (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 - (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 - (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 - (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 - (amp_hor_s));
				Sleep(verdel);
				packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 - (amp_hor_s));
				Sleep(verdel);
			}
		}

		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 1));
		Sleep(delaytime);

		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 3));
		Sleep(delaytime);

		packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 5));
		Sleep(delaytime);

		packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 7));
		Sleep(delaytime);

		packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 9));
		Sleep(delaytime);

		packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 11));
		Sleep(delaytime);

		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 13));
		Sleep(delaytime);

		/*packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 15));
		Sleep(delaytime);*/
	}
	else
	{
		/*packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 1 + M_PI_2));
		Sleep(delaytime);*/
		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 3 + M_PI_2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 5 + M_PI_2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 7 + M_PI_2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 9 + M_PI_2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 11 + M_PI_2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 13 + M_PI_2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2 * 15 + M_PI_2));
		Sleep(delaytime);
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
	int delaytime = 8;

	if (robot->modes != SIDEWIND_MODE)
	{
		robot->modes = SIDEWIND_MODE;
		robot->modetime = time(0);
		robot->count = 0;

		enable_motor();
	}

	set_speed_motor(robot->throtle);

	if (robot->heading >= 0)
	{
		x = robot->count + lag_ver / 2;

		packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 3;

		packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 5;

		packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 7;

		packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 3));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 9;

		packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 4));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 11;

		packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 5));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 13;

		packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 6));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 15;

		/*packh->write2ByteTxOnly(porth, DXL_ID16, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 7));
		Sleep(delaytime);*/
		packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);
	}
	else
	{
		x = robot->count + lag_ver / 2 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 3 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 5 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 7 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 3));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 9 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 4));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 11 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 5));
		packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 13 + M_PI;

		packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 6));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		x = robot->count + lag_ver / 2 * 15 + M_PI;

		//packh->write2ByteTxOnly(porth, DXL_ID16, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 7));
		//Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);
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
		robot->modetime = time(0);

		enable_motor();
		set_speed_motor(150);

	}
	int amp_x = -1 * robot->throtle;
	int amp_y = -1 * robot->heading;

	uint16_t x = amp_x * 2 + 512;
	uint16_t y = amp_y + 512;

	

	packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 - 135); //512 is a middle position value of a AX-12
	packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 - 135); //512 is a middle position value of a AX-12
	packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 - 135); //512 is a middle position value of a AX-12
	packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 - 135); //512 is a middle position value of a AX-12
	packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 - 135); //512 is a middle position value of a AX-12

	Sleep(10);

	//packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 - 185); //512 is a middle position value of a AX-12
	packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 - 185); //512 is a middle position value of a AX-12

	packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, y);
	packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, x);

}

void turning(robot_state* robot)
{
	int delaytime = 8;
	int amp_ver_s = 50;

	if (robot->modes != TURN_MODE)
	{
		robot->modes = TURN_MODE;
		robot->count = 0;
		robot->modetime = time(0);

		enable_motor();
		packh->write2ByteTxOnly(porth, 0xFE, ADDR_MX_GOAL_POSITION, 512);
	}
	if(robot->count < 31)
	{
		//Front Side
		double x = robot->count * M_PI_4;
		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		x += M_PI_4;
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		x += M_PI_4;
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		x += M_PI_4;
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		x += M_PI_4;

		if (robot->count % 3 == 0)
		{
			packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + (int)(robot->count / 3) * 20);
			Sleep(delaytime);
			packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + (int)(robot->count / 3) * 20);
			Sleep(delaytime);
			packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + (int)(robot->count / 3) * 20);
			Sleep(delaytime);

			packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + (int)(robot->count / 3) * 15);
			Sleep(delaytime);
		}

		//Back side
		packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		x += M_PI_4;
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		x += M_PI_4;
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		x += M_PI_4;
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
		Sleep(delaytime);

		if (robot->count % 3 == 0)
		{
			packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 - (int)(robot->count / 3) * 20);
			Sleep(delaytime);
			packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 - (int)(robot->count / 3) * 20);
			Sleep(delaytime);
			packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 - (int)(robot->count / 3) * 20);
			Sleep(delaytime);
		}
	}
	

	if (robot->count == 40)
	{
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + 20);
		packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + 20);
		packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + 20);
		packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + 20);
		packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + 20);
		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + 20);
		Sleep(10);
		packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512);
		packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512);
		packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512);
		packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512);
		packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512);
		packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512);
		Sleep(10);

	}

	if (robot->count > 60)
	{
		robot->count = 0;
	}
	robot->count++;
	
}



void turning2(robot_state* robot)
{
	int delaytime = 8;

	if (robot->modes != TURN_MODE)
	{
		robot->modes = TURN_MODE;
		robot->count = 0;
		robot->modetime = time(0);

		enable_motor();
		packh->write2ByteTxOnly(porth, 0xFE, ADDR_MX_GOAL_POSITION, 512);
	}

	set_speed_motor(robot->throtle);

	int amp_hor_s = (120 * robot->heading) / 100;
	int amp_ver_s = (150 * robot->heading) / 100;
	if (robot->heading > 0)
	{
		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * sin(robot->count + lag_ver / 2 + M_PI_2));//방향전환 기여 (정밀)
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * sin(robot->count + lag_ver / 2 + M_PI_2));//방향전환 기여 (정밀)

		packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * sin(robot->count + lag_hor * 2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 3));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 4));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 5));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 6));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * sin(robot->count + lag_hor * 2));

		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2));//방향전환 기여 (정밀)
		packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2));//방향전환 기여 (정밀)
	}
	else
	{
		packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * sin(robot->count + lag_ver / 2 + M_PI_2));//방향전환 기여 (정밀)
		packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * sin(robot->count + lag_ver / 2 + M_PI_2));//방향전환 기여 (정밀)

		packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * sin(robot->count + lag_hor * 2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 2));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 3));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 4));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 5));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * cos(robot->count + lag_hor * 6));
		Sleep(delaytime);
		packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 + amp_hor_s * sin(robot->count + lag_hor * 2));

		packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2));//방향전환 기여 (정밀)
		packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(robot->count + lag_ver / 2));//방향전환 기여 (정밀)

	}

	robot->count++;
}

void sinuslift(robot_state* robot)
{
	if (robot->modes != SINUSLIFT_MODE)
	{
		robot->modes = SINUSLIFT_MODE;
		robot->modetime = time(0);
		robot->count = 0;

		enable_motor();
		packh->write2ByteTxOnly(porth, 0xFE, ADDR_MX_GOAL_POSITION, 512);
		
	}

	int amp_hor_s = (200 * robot->throtle) / 100;
	int amp_ver_s = (150 * robot->throtle) / 100;
	int delaytime = 5;
	int bias = 0;
	double x = 0;

	set_speed_motor(robot->throtle);

	if (robot->heading == 0)
	{
		bias = 0;
	}
	else
	{
		bias = -0.55 * robot->heading;
	}


	x = robot->count;
	packh->write2ByteTxOnly(porth, DXL_ID1, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(delaytime);
	packh->write2ByteTxOnly(porth, DXL_ID2, ADDR_MX_GOAL_POSITION, 512 + bias + amp_hor_s * cos(0.5 * robot->count + lag_hor * 1.5));
	Sleep(delaytime);


	x = robot->count + lag_ver * 2;
	packh->write2ByteTxOnly(porth, DXL_ID3, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(delaytime);
	packh->write2ByteTxOnly(porth, DXL_ID4, ADDR_MX_GOAL_POSITION, 512 + bias + amp_hor_s * cos(0.5 * robot->count + lag_hor * 2.5));
	Sleep(delaytime);

	x = robot->count + lag_ver * 4;
	packh->write2ByteTxOnly(porth, DXL_ID5, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(delaytime);
	packh->write2ByteTxOnly(porth, DXL_ID6, ADDR_MX_GOAL_POSITION, 512 + bias + amp_hor_s * cos(0.5 * robot->count + lag_hor * 3.5));
	Sleep(delaytime);

	x = robot->count + lag_ver * 6;
	packh->write2ByteTxOnly(porth, DXL_ID7, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(delaytime);
	packh->write2ByteTxOnly(porth, DXL_ID8, ADDR_MX_GOAL_POSITION, 512 + bias + amp_hor_s * cos(0.5 * robot->count + lag_hor * 4.5));
	Sleep(delaytime);

	x = robot->count + lag_ver * 8;
	packh->write2ByteTxOnly(porth, DXL_ID9, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(delaytime);
	packh->write2ByteTxOnly(porth, DXL_ID10, ADDR_MX_GOAL_POSITION, 512 + bias + amp_hor_s * cos(0.5 * robot->count + lag_hor * 5.5));
	Sleep(delaytime);

	x = robot->count + lag_ver * 10;
	packh->write2ByteTxOnly(porth, DXL_ID11, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(delaytime);
	packh->write2ByteTxOnly(porth, DXL_ID12, ADDR_MX_GOAL_POSITION, 512 + bias + amp_hor_s * cos(0.5 * robot->count + lag_hor * 6.5));
	Sleep(delaytime);

	x = robot->count + lag_ver * 12;
	packh->write2ByteTxOnly(porth, DXL_ID13, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(delaytime);
	packh->write2ByteTxOnly(porth, DXL_ID14, ADDR_MX_GOAL_POSITION, 512 + bias + amp_hor_s * cos(0.5 * robot->count + lag_hor * 7.5));
	Sleep(delaytime);

	x = robot->count + lag_ver * 14;
	packh->write2ByteTxOnly(porth, DXL_ID15, ADDR_MX_GOAL_POSITION, 512 + amp_ver_s * cos(x));
	Sleep(delaytime);

	robot->count++;
}

void stopmode(robot_state* robot)
{
	if (robot->modes != STOP_MODE)
	{
		robot->modes = STOP_MODE;
		robot->modetime = time(0);
		robot->count = 0;

		packh->write1ByteTxOnly(porth, 0xFE, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE);
	}
}
