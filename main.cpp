/**************************************************************************/
/*!
	此项目移植于开源项目Adafruit_AMG88xx，原项目是基于Arduino，可实现在
	    Raspberry Pi 4B上运行。
    项目使用VS2017开发，语言为C++，通过wiring Pi 这个库调用I2C，实现与模块的通信。
*/
/**************************************************************************/
#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "AMG88xx/AMG88xx.h"

// 创建控制AMG8833的对象
Adafruit_AMG88xx amg;

// 保存热成像数据的一维数组
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

/*初始化*/
void setup() {
	// 初始化wiringPi
	if (-1 == wiringPiSetup())
	{
		std::cerr << "setup error\n";
		exit(-1);
	}

	// 初始化amg
	bool status = amg.begin();
	if (!status) {
		std::cout << "Could not find a valid AMG88xx sensor, check wiring!" << std::endl;
		exit(-1);
	}

	std::cout << "-- Pixels Test --" << std::endl;
}

int main() {
	setup();

	while (true)
	{
		amg.readPixels(pixels); // 读取数据到矩阵

		// 8*8矩阵，循环打印输出
		for (int i = 1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++) {
			std::cout << pixels[i - 1];
			std::cout << ", ";
			if (i % 8 == 0) std::cout << std::endl;
		}
		std::cout << "--------------------" << std::endl;

		//AMG8833最大帧率10Hz
		delay(1000);
	}
	return 0;
}