#ifndef DS18B20_H
#define DS18B20_H

#include <stdint.h>

#define DS18B20_ERROR -9999

uint8_t ds18b20_start_conversion(void);

int16_t ds18b20_read_temp(void);

#endif
