#ifndef __SPI_H
#define __SPI_H

#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>

void Init_SPI0(void);
void SPI0_Write(uint8_t data);

#endif