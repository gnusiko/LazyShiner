#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602.h"
#include "config.h"
#include "ds18b20.h"

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

void lcd_clear(void){
    lcd_send_byte(0x01, 0);
}

static void lcd_print_temp(int16_t temp_deci){
    if(temp_deci == DS18B20_ERROR){
        lcd_print("ERR");
        return;
    }
    if(temp_deci < 0){
        lcd_send_byte('-', 1);
        temp_deci = -temp_deci;
    }
    uint8_t tens = (temp_deci / 100) % 10;
    uint8_t ones = (temp_deci / 10) % 10;
    uint8_t deci = temp_deci % 10;

    lcd_send_byte(tens ? ('0' + tens) : ' ', 1);
    lcd_send_byte('0' + ones, 1);
    lcd_send_byte('.', 1);
    lcd_send_byte('0' + deci, 1);
}

static void lcd_print_pct(uint8_t pct){
    uint8_t hund = (pct / 100) % 10;
    uint8_t deci = (pct / 10) % 10;
    uint8_t onec = pct % 10;
    lcd_send_byte(hund ? ('0' + hund) : ' ', 1);
    lcd_send_byte(deci ? ('0' + deci) : ' ', 1);
    lcd_send_byte('0' + onec, 1);
}

void lcd_render_status(const SystemStatus *st){
    lcd_set_cursor(0,0);
    lcd_print("T:");
    lcd_print_temp(st->current_temp);
    lcd_print("C S:");
    lcd_print_temp(st->target_temp);
    lcd_print("C");

    lcd_set_cursor(1, 0);
    lcd_print((st->profile == PROFILE_6L) ? " 6L" : "20L");

    switch(st->state){
        case STATE_IDLE:    lcd_print("IDLE "); break;
        case STATE_HEATUP:  lcd_print("HEAT "); break;
        case STATE_WORK:    lcd_print("WORK "); break;
        case STATE_ALARM:
            if(st->error == ERR_SENSOR_LOST)    lcd_print("ERR:SENS");
            else lcd_print("ERR:OVER");
            return;
    }
    lcd_print("P:");
    lcd_print_pct(st->power_pct);
    lcd_print("%");
}
















































