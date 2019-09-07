#include "snake_state.h"

uint8_t dxl_error;
uint16_t dxl_now_pos;

void enable_motor()
{
	packh->write1ByteTxRx(porth, DXL_ID1, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID2, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID3, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID4, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID5, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID6, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID7, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID8, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID9, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID10, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID11, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID12, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID13, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID14, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID15, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID16, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);

	std::cout << packh->getProtocolVersion() << std::endl;
	std::cout << porth->getBaudRate() << std::endl;

	if (dxl_error != 0)
	{
		std::cout << "ERROR!" << std::endl;
	}
}

void disable_motor(dynamixel::PacketHandler* packh)
{
	packh->write1ByteTxRx(porth, DXL_ID1, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID2, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID3, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID4, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID5, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID6, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID7, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID8, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID9, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID10, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID11, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID12, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID13, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID14, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID15, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	packh->write1ByteTxRx(porth, DXL_ID16, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);

	if (dxl_error != 0)
	{
		std::cout << "ERROR!" << std::endl;
	}
}
