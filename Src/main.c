#include <stdint.h>
#include "LED.h"
#include "UART.h"
#include "W25Qxx.h"

int main()
{
	W25Q_Init();
	LED_Init();
	UART2_Init();

	LED_Toggle();

	while(1)
	{

	}
}
