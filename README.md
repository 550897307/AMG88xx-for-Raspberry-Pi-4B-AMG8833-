# AMG88xxforRaspberryPi4B
## ���
����Ŀ��ֲ�ڿ�Դ��ĿAdafruit_AMG88xx��ԭ��Ŀ�ǻ���Arduino���ֿ���Raspberry Pi 4B�����С�

��Ŀʹ��VS2017����������ΪC++��ͨ��[WiringPi]([WiringPi](http://wiringpi.com/)) ��������I2C��ʵ����ģ���ͨ�š�

## Ӳ������

### AMG88XX

AMG88XX��8*8�����ȳ��񴫸�����I2C�ӿڡ���ϵ�з�ΪAMG8833��AMG8831��

����ʹ�õ���AMG8833ģ�飨���ʱ����180��������ֻҪ120����������������������ĿҲ�ǻ��ڴ˽��в��Եġ�

��ԭ��Ŀ֧��AMG88XXϵ�У�������ֲ�汾�Ƿ�����֧��ȫϵ��ֻ����������֪�������û���ԣ������ҡ�������������

### AMG8833������ ��������

**ע��1���˲���Ϊ���²��Ĵ�������Ϣ��**

**ע��2������ʹ�õ���ģ�飬�򲿷ֲ������в��죬���ܵ�Դ��Χ������**

| �����б�      | ��ֵ       |
| :------------ | ---------- |
| Ʒ��          | PANASONIC  |
| ��Դ��ѹ      | 3.00V(min) |
| �������(Max) | 10 mA      |
| �����¶�(Max) | 80 ��       |
| �����¶�(Min) | 0 ��        |
| ����          | �� 2.5 ��    |
| ��Դ��ѹ(Max) | 3.6 V      |
| ��Դ��ѹ(Min) | 3.0 V      |

[AMG8833�����ֲ����ӣ���о����](https://www.findic.com/jiage/amg8833-JLb7qp78e.html)

### Raspberry Pi 4B

- ��ݮ��û��ģ��ӿ�
- **GPIO�ߵ�ƽΪ3.3V������**
- **ʹ��I2C�ӿ�ǰ��Ҫ����Raspberry Pi I2C����**
- ��ʹ�õ�wiring Pi�汾Ϊ2.60 ��**ʹ��2.50��������⣡����**�Ƽ���github��װ���°�wiring Pi��

GPIO����ͼ��

<img src="md_pictures/image-20210721161225042.png" alt="image-20210721161225042" style="zoom:80%;" />

## ��Ŀ��ʹ��

### ���ӵ�·

�ܹ��ĸ��ߣ��ܺ�Ū������׸����

### ���I2C�豸�Ƿ��ѹ���

��ݮ�ɿ���I2C���ܣ������������⣺

`i2cdetect -y 1`

<img src="md_pictures/image-20210721162449342.png" alt="image-20210721162449342" style="zoom:67%;" />

������Կ��������ǵ��豸�Ѿ��ɹ����أ�69����AMG8833��Ĭ��I2C��ַ��`0x69`��

### �������

����Ŀ���Ĳ���ΪAMG88xx.h��AMG88xx.cpp����ʹ��ǰ��Ҫ���������ļ��������������浽�Լ�����Ŀ�ļ����С���

�������Ƽ�ʹ��VS������VS�����������һIDE������ݮ�ɿ�����֧�ֿ���������

��������Ŀ�󣬵���ͷ�ļ���cpp�ļ���������Ҫ�ļ���

<img src="md_pictures/image-20210721164106590.png" alt="image-20210721164106590" style="zoom:80%;" />



main.cpp�������£�

```cpp
/**************************************************************************/
/*!
	����Ŀ��ֲ�ڿ�Դ��ĿAdafruit_AMG88xx��ԭ��Ŀ�ǻ���Arduino����ʵ����
	    Raspberry Pi 4B�����С�
    ��Ŀʹ��VS2017����������ΪC++��ͨ��wiring Pi ��������I2C��ʵ����ģ���ͨ�š�
*/
/**************************************************************************/
#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "AMG88xx/AMG88xx.h"

// ��������AMG8833�Ķ���
Adafruit_AMG88xx amg;

// �����ȳ������ݵ�һά����
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

/*��ʼ��*/
void setup() {
	// ��ʼ��wiringPi
	if (-1 == wiringPiSetup())
	{
		std::cerr << "setup error\n";
		exit(-1);
	}

	// ��ʼ��amg
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
		amg.readPixels(pixels); // ��ȡ���ݵ�����

		// 8*8����ѭ����ӡ���
		for (int i = 1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++) {
			std::cout << pixels[i - 1];
			std::cout << ", ";
			if (i % 8 == 0) std::cout << std::endl;
		}
		std::cout << "--------------------" << std::endl;

		//AMG8833���֡��10Hz
		delay(1000);
	}
	return 0;
}
```

�������£�

<img src="md_pictures/image-20210721163239655.png" alt="image-20210721163239655" style="zoom:80%;" />



## ���

����Ŀ��ֲ��Ϊ���ɣ�û�������е���ô���ѣ���ԭ�ļ�����VS��Ŀ�У��ѱ�촦ȫ���������ɡ�

���˼����רҵ��Ӳ��ֻ�ǰ��ã��Ժ�Ҳ���ٸ�����ˡ���������

���С�������Լ�����ְ֮ǰ����������ã����һ�ȱ�ٺܶಿ�֣�������ӻ����Ժ������л����ٲ��ɡ�����

