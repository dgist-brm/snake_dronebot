#pragma once

//IDs of dynamixels
#define DXL_ID1    48//head
#define DXL_ID2    43//head
#define DXL_ID3    49
#define DXL_ID4    44
#define DXL_ID5    50
#define DXL_ID6    45
#define DXL_ID7    36
#define DXL_ID8    31
#define DXL_ID9    37
#define DXL_ID10   32
#define DXL_ID11    28
#define DXL_ID12    23
#define DXL_ID13    29
#define DXL_ID14    24
#define DXL_ID15    46//tail
#define DXL_ID16    25//tail


#define ADDR_MX_TORQUE_ENABLE           24                  // Control table address is different in Dynamixel model
#define ADDR_MX_GOAL_POSITION           30                 // Control table address is different in Dynamixel model
#define ADDR_MX_GOAL_SPEED              32                 // Control table address is different in Dynamixel model
#define ADDR_MX_PRESENT_POSITION        36                 // Control table address is different in Dynamixel model

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque
#define DXL_MOVING_STATUS_THRESHOLD     5                  // Dynamixel moving status threshold


//ASCI CODE for control keys
#define ESC_ASCII_VALUE      0x1b  //esc
#define WAVE_ASCII_VALUE     0x77  //w
#define WAVE2_ASCII_VALUE    0x65  //e
#define SINUS_LIFTING_VALUE  0x73  //s
#define SIDE_WINDING_VALUE    0x64  //d
#define SIDE_WINDING_2_VALUE  0x66  //f
#define CMU_MOTION_VALUE     0x63   //c
#define ROLLING_VALUE     0x72   //r

// Protocol version
#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel
#define BAUDRATE                        115200//1000000     // this should be same with baudrate of dynamixels
#define DEVICENAME                      "COM4"      // Check which port is being used on your controller

// State Mode Define
#define STOP_MODE 0
#define V_MODE 1
#define H_MODE 2
#define SIDEWIND_MODE 3
