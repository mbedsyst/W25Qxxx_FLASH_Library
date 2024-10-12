#include <stdint.h>
#include "LED.h"
#include "UART.h"
#include "W25Qxx.h"

int main()
{
	uint8_t buf[256] ="The W25Q64FV (64M-bit) Serial Flash memory provides a storage solution for systems with limited space, pins and power. The 25Q series offers flexibility and performance well beyond ordinary Serial Flash devices. They are ideal for code shadowing to RAM .!!";
	W25Q_Init();
	LED_Init();
	UART2_Init();

	LED_Toggle();
	W25Q_EraseSector(0, 0);
	for(int i = 0; i < 32768; i++)
	{
		W25Q_WritePage(i, 0, 256, buf);
	}
	LED_Toggle();;



	while(1)
	{

	}
}
