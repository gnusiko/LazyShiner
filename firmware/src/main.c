#include <avr/io.h>
#include <util/delay.h>
#include "ds18b20.h"
#include "config.h"
#include "lcd1602.h"

void timer_init(void){
    DDRB = (1 << PB1);
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS12);
    TCCR1B |= (1 << CS10) | (1 << CS12);
    ICR1 = 3904;
    OCR1A = 3600;
}

int main(){
    timer_init();
    lcd_init();
    lcd_set_cursor(0, 0);
    lcd_print("Hello, Attmega8");
    lcd_set_cursor(1, 0);
    lcd_print("Line 2 works");
    DDRD = 255;
    uint16_t T = 0;
    while(1){
    
    ds18b20_start_conversion();
    _delay_us(750);
    {
        /* code */
    }
    
    T = ds18b20_read_temp();
    PORTD = T;
    }
}