#include "control.h"



void lcd_send_nibble(uint8_t nibble);

void lcd_send_byte(uint8_t byte, uint8_t is_data);

void lcd_init(void);

void lcd_set_cursor(uint8_t row, uint8_t col);

void lcd_print(const char *str);

void lcd_clear(void);

void lcd_render_status(const SystemStatus *st);

//static void lcd_print_temp(int16_t demp_deci);

//static void lcd_print_pct(uint8_t pct);