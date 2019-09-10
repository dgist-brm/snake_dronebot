// Snake_CMD_V1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "Snake_CMD_V1.h"

int main()
{
	porth = dynamixel::PortHandler::getPortHandler(DEVICENAME);
	porth->setBaudRate(BAUDRATE);
	packh = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

	robot.modes = 0;
	robot.count = 0;
	robot.heading = 0;
	robot.throtle = 0;

	ZeroMemory(&Xstate, sizeof(XINPUT_STATE));

    std::cout << "Snake CMD commander V1\n";
	std::cout << "Initiating Port\n";

	if (1)
	{
		std::cout << "Setting communication line done! \n";
		Sleep(500);
	}
	else
	{
		std::cout << "Fail to set communication line! Close the program now.\n";
		try 
		{
			if(porth != NULL)
				closeComm(porth);
		}
		catch (std::exception e)
		{ 
			std::cout << "exception!" << e.what() << std::endl;
		}
		return 0;
	}

	system("cls");
	std::cout << "Snake CMD commander V1\n";
	std::cout << "Initiating state\n";
	enable_motor();
	//disable_motor(porth);

	std::cout << "Motor Initiating done!" << std::endl;
	Sleep(500);

	

	while (1)
	{
		system("cls");
		std::cout << "Snake CMD commander V1\n";
		std::cout << "Command Now \n";

		DWORD Xresult;
		Xresult = XInputGetState(0, &Xstate);

		inputMode = buttonToMode(Xstate.Gamepad.wButtons);

		robot.throtle = analogToSpeed(Xstate.Gamepad.sThumbLY);
		robot.heading = analogToSpeed(Xstate.Gamepad.sThumbLX);

		switch (inputMode)
		{
		default: //STOP 모드
			std::cout << "mode 0" << std::endl;
			robot.modes = 0;
			break;

		case STOP_MODE: //STOP 모드
			std::cout << "mode 0" << std::endl;
			robot.modes = 0;
			break;

		case V_MODE: //자벌레 모드
			std::cout << "VERTICAL WAVE MODE" << std::endl;
			ver_wave(&robot);
			break;

		case 2:
			std::cout << "mode 2" << std::endl;
			break;

		case SIDEWIND_MODE:
			std::cout << "SIDE WINDING MODE" << std::endl;
			sidewind(&robot);
			break;

		case 4:
			std::cout << "ENABLE MOTOR" << std::endl;
			enable_motor();
			break;

		case 5:
			std::cout << "DISABLE MOTOR" << std::endl;
			disable_motor();
			break;

		}

		std::cout << analogToSpeed(Xstate.Gamepad.sThumbLX) << (Xstate.Gamepad.sThumbLY) << std::endl;

		unsigned int tempa = Xstate.Gamepad.bLeftTrigger;
		unsigned int tempb = Xstate.Gamepad.bRightTrigger;

		std::cout << tempa << std::endl;
		std::cout << tempb << std::endl;
		std::cout << Xstate.Gamepad.wButtons << std::endl;

		Sleep(100);
	}

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

int analogToSpeed(short analog)
{
	if (analog < 5000 && analog > -5000)
		return 0;
	else if (analog > 0)
		return (analog - 5000) * 0.0036;
	else if (analog <= 0)
		return (analog + 5000) * 0.0036;
	else
		return 0;
}

int buttonToMode(WORD Buttons)
{
	if (Buttons & XINPUT_GAMEPAD_DPAD_UP)
		return 0;
	else if (Buttons & XINPUT_GAMEPAD_DPAD_DOWN)
		return 1;
	else if (Buttons & XINPUT_GAMEPAD_DPAD_LEFT)
		return 2;
	else if (Buttons & XINPUT_GAMEPAD_DPAD_RIGHT)
		return 3;
	else if (Buttons & XINPUT_GAMEPAD_START)
		return 4;
	else if (Buttons & XINPUT_GAMEPAD_BACK)
		return 5;
}
