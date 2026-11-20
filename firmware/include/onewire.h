#ifndef ONEWIRE_H
#define ONEWIRE_H

#include <avr/io.h>
#include <stdint.h>

#define OW_PORT     PORTB
#define OW_DDR      DDRB
#define OW_PIN      PINB
#define OW_BIT      PB0

uint8_t ow_reset(void);

void ow_write_byte(uint8_t byte);

uint8_t ow_read_byte(void);

#endif