#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602.h"

void lcd_send_nibble(uint8_t nibble){
    LCD_PORT = (LCD_PORT & 0x0F) | (nibble & 0xF0);
    LCD_PORT |= (1 << E);
    _delay_us(1);
    LCD_PORT &= ~(1 << E);
    _delay_us(50);
}

void lcd_send_byte(uint8_t byte, uint8_t is_data){
    if(is_data)     LCD_PORT |= (1 << RS);
    else            LCD_PORT &= ~(1 << RS);
    lcd_send_nibble(byte);
    lcd_send_nibble(byte << 4);
}

void lcd_init(void){
    LCD_DDR |= (1 << RS) | (1 << E) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
    LCD_PORT &= ~(1 << RS);
    lcd_send_nibble(0x30);
    _delay_us(5);
    lcd_send_nibble(0x30);
    _delay_us(150);
    lcd_send_nibble(0x30);
    lcd_send_nibble(0x20);

    lcd_send_byte(0x28, 0);
    lcd_send_byte(0x0C, 0);
    lcd_send_byte(0x01, 0);
    _delay_us(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col){
    uint8_t addr = (row == 0) ? 0x80 : 0xC0;
    lcd_send_byte(addr + col, 0);
}

void lcd_print(const char *str){
    while(*str){
        lcd_send_byte(*str++, 1);
    }
}

