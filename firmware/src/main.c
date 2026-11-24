#include <avr/io.h>
#include <util/delay.h>
#include "ds18b20.h"
#include "config.h"
#include "lcd1602.h"
#include " control.h"

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
    control_init();

    while(1){
    
    }
}