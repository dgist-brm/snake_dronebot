#include "connection.h"

int setComm(int port, int version, int baudrate)
{

	return 0;
}

int setComm(dynamixel::PortHandler *porth, dynamixel::PacketHandler *packh, const char* port, float version, int baudrate)
{
	porth = dynamixel::PortHandler::getPortHandler(port);
	porth->setBaudRate(BAUDRATE);
	packh = dynamixel::PacketHandler::getPacketHandler(1.0);

	if (porth->openPort())
	{
		std::cout << "Port open done! \n";
	}
	else
	{
		std::cout << "Port open fail! \n";
		return 0;
	}

	if (porth->setBaudRate(baudrate))
	{
		std::cout << "Set baudrate done! \n";
	}
	else
	{
		std::cout << "Set baudrate fail! \n";
		return 0;
	}
	return 1;
}

void closeComm(dynamixel::PortHandler* porth)
{
	porth->closePort();
}
