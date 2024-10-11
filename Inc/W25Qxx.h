#ifndef W25QXX_H_
#define W25QXX_H_

#include "SPI.h"
#include "SYSTICK.h"

// Flash Memory Parameter macros
#define W25Q_Bytes			8388608
#define W25Q_PageSize		256
#define W25Q_PageCount		32768
#define W25Q_SectorSize		4096
#define	W25Q_SectorCount	2048
#define W25Q_BlockSize		65536
#define W25Q_BlockCount		128

// Flash Memory Command macros
#define ENABLE_RESET	0x66
#define EXECUTE_RESET	0x99
#define READ_ID			0x9F
#define NORMAL_READ		0x03
#define FAST_READ		0x0B
#define ENABLE_WRITE	0x06
#define DISABLE_WRITE	0x04
#define PAGE_WRITE		0x02
#define ERASE_SECTOR	0x20
#define ERASE_32kBLOCK	0x52
#define ERASE_64kBLOCK	0xD8
#define ERASE_CHIP		0x60


// Control Functions
void W25Q_Init(void);
uint32_t W25Q_ReadID(void);

// Read Functions
void W25Q_ReadData(uint32_t startPage, uint8_t offset, uint8_t *buffer, uint16_t length);
void W25Q_FastReadData(uint32_t startPage, uint8_t offset, uint8_t *buffer, uint16_t length);

// Write Functions
void W25Q_WritePage(uint32_t startPage, uint16_t offset, uint32_t size, uint8_t *data);

// Erase Functions
void W25Q_EraseSector(uint8_t block, uint8_t sector);
void W25Q_Erase32kBlock(uint8_t block, uint8_t half);
void W25Q_Erase64kBlock(uint8_t block);
void W25Q_EraseChip(void);


#endif
