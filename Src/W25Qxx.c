#include "W25Qxx.h"

static void W25Q_WriteEnable(void)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(ENABLE_WRITE);
	SPI2_DeselectSlave();
	delay_ms(10);
}

static void W25Q_WriteDisable(void)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(DISABLE_WRITE);
	SPI2_DeselectSlave();
	delay_ms(10);
}

static void W25Q_Reset(void)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(ENABLE_RESET);
	SPI2_TransmitReceiveByte(EXECUTE_RESET);
	SPI2_DeselectSlave();
	delay_ms(100);
}

void W25Q_Init(void)
{
	SPI2_Init();
	W25Q_Reset();
}

uint32_t W25Q_ReadID(void)
{
    	uint8_t dummyByte = 0xFF;
    	uint8_t id[3];
    	SPI2_SelectSlave();
    	SPI2_TransmitReceiveByte(READ_ID);
    	SPI2_TransmitReceive_MultiByte(&dummyByte, id, 3);
    	SPI2_DeselectSlave();
    	return ((id[0] << 16) | (id[1] << 8) | (id[2]));
}

void W25Q_ReadData(uint32_t startPage, uint8_t offset, uint8_t *buffer, uint16_t length)
{
	uint32_t memAddress = (startPage * 256) + offset;

	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(NORMAL_READ);
	SPI2_TransmitReceiveByte((memAddress >> 16) & 0xFF);
	SPI2_TransmitReceiveByte((memAddress >> 8) & 0xFF);
	SPI2_TransmitReceiveByte(memAddress & 0xFF);
	for (uint16_t i = 0; i < length; i++)
	{
		// Send dummy byte and receive data
		buffer[i] = SPI2_TransmitReceiveByte(0xFF);
	}
	SPI2_DeselectSlave();
}

void W25Q_FastReadData(uint32_t startPage, uint8_t offset, uint8_t *buffer, uint16_t length)
{
	uint32_t memAddress = (startPage * 256) + offset;

	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(FAST_READ);
	SPI2_TransmitReceiveByte((memAddress >> 16) & 0xFF);
	SPI2_TransmitReceiveByte((memAddress >> 8) & 0xFF);
	SPI2_TransmitReceiveByte(memAddress & 0xFF);
	SPI2_TransmitReceiveByte(0x00);
	for (uint16_t i = 0; i < length; i++)
	{
		// Send dummy byte and receive data
		buffer[i] = SPI2_TransmitReceiveByte(0xFF);
	}
	SPI2_DeselectSlave();
}

void W25Q_WritePage(uint32_t startPage, uint16_t offset, uint32_t size, uint8_t *data)
{
	uint32_t memAddress = (startPage * 256) + offset;
	W25Q_WriteEnable();
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(PAGE_WRITE);
	SPI2_TransmitReceiveByte((memAddress >> 16) & 0xFF);
	SPI2_TransmitReceiveByte((memAddress >> 8) & 0xFF);
	SPI2_TransmitReceiveByte((memAddress) & 0xFF);
	SPI2_TransmitReceive_MultiByte(data, NULL, size);
	SPI2_DeselectSlave();
	W25Q_WriteDisable();
	delay_ms(5);
}

void W25Q_EraseSector(uint8_t block, uint8_t sector)
{
	uint32_t memAddress = (block * 65536) + (sector * 4096);
	W25Q_WriteEnable();
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(ERASE_SECTOR);
	SPI2_TransmitReceiveByte((memAddress >> 16) & 0xFF);
	SPI2_TransmitReceiveByte((memAddress >> 8) & 0xFF);
	SPI2_TransmitReceiveByte(memAddress & 0xFF);
	SPI2_DeselectSlave();
	delay_ms(500);
}

void W25Q_Erase32kBlock(uint8_t block, uint8_t half)
{
	uint32_t memAddress = (block * 65536) + (half * 32768);
	W25Q_WriteEnable();
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(ERASE_32kBLOCK);
	SPI2_TransmitReceiveByte((memAddress >> 16) & 0xFF);
	SPI2_TransmitReceiveByte((memAddress >> 8) & 0xFF);
	SPI2_TransmitReceiveByte(memAddress & 0xFF);
	SPI2_DeselectSlave();
	delay_ms(1700);
}

void W25Q_Erase64kBlock(uint8_t block)
{
	uint32_t memAddress = (block * 65536);
	W25Q_WriteEnable();
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(ERASE_64kBLOCK);
	SPI2_TransmitReceiveByte((memAddress >> 16) & 0xFF);
	SPI2_TransmitReceiveByte((memAddress >> 8) & 0xFF);
	SPI2_TransmitReceiveByte(memAddress & 0xFF);
	SPI2_DeselectSlave();
	delay_ms(2100);
}

void W25Q_EraseChip(void)
{
	W25Q_WriteEnable();
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(ERASE_CHIP);
	SPI2_DeselectSlave();
	delay_ms(100100);
}
