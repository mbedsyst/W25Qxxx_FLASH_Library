#include <stdint.h>
#include "LED.h"
#include "UART.h"
#include "W25Qxx.h"

int main()
{
	uint8_t buf[76] ="WELL, IT JUST SO HAPPENS THAT WE ARE EXPERTS AT EXTERMINATING SHITBAG SUPES.";
	W25Q_Init();
	LED_Init();
	UART2_Init();

	LED_On();
	for(int i = 0; i < 16; i++)
	{
		W25Q_WritePage(i, 0, 76, buf);
	}
	LED_Off();



	while(1)
	{

	}
}
