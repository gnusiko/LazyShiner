#include "config.h"


#ifndef LCD_DDR
#define LCD_DDR         DDRD
#define LCD_PORT        PORTD
#define RS              PD0
#define E               PD1


#endif

void lcd_send_nibble(uint8_t nibble);

void lcd_send_byte(uint8_t byte, uint8_t is_data);

void lcd_init(void);

void lcd_set_cursor(uint8_t row, uint8_t col);

void lcd_print(const char *str);

