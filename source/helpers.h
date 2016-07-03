#ifndef HELPERS_H
#define HELPERS_H

#include "global.h"

#define WRITEU8(addr, data) *(vu8*)(addr) = data
#define WRITEU16(addr, data) *(vu16*)(addr) = data
#define WRITEU32(addr, data) *(vu32*)(addr) = data

#define Write8(addr, data) *(volatile unsigned char*)(addr) = data
#define Write16(addr, data) *(volatile unsigned short*)(addr) = data
#define Write32(addr, data) *(volatile unsigned int*)(addr) = data

#define Read8(addr) *(volatile unsigned char*)(addr)
#define Read16(addr) *(volatile unsigned short*)(addr)
#define Read32(addr) *(volatile unsigned int*)(addr)

#define IO_BASE_PAD		1
#define IO_BASE_LCD		2
#define IO_BASE_PDC		3
#define IO_BASE_GSPHEAP		4

u32 plgGetIoBase(u32 IoType);

extern u32 IoBasePad;

u32 getKey();
void waitKeyUp();

#endif
