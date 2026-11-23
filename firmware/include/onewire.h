#ifndef ONEWIRE_H
#define ONEWIRE_H

#include <avr/io.h>
#include <stdint.h>
#include "config.h"



uint8_t ow_reset(void);

void ow_write_byte(uint8_t byte);

uint8_t ow_read_byte(void);

#endif