#ifndef CONFIG_H
#define CONFIG_H

#include <avr/io.h>

#define OW_PORT     PORTB
#define OW_DDR      DDRB
#define OW_PIN      PINB
#define OW_BIT      PB0

#define HEATER_PORT     PORTB
#define HEATER_DDR      DDRB
#define HEATER_BIT      PB1



#endif  // CONFIG_H