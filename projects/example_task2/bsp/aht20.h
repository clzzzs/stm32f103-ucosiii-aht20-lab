#ifndef AHT20_H
#define AHT20_H

#include "main.h"

/* 软件 I2C 引脚：SCL=PB6，SDA=PB7，模块需带上拉电阻 */
void AHT20_Init(void);
void AHT20_Read(int32_t *temp_x10, int32_t *humi_x10);

#endif
