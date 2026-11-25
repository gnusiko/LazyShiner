#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include "buttons.h"
#include "lcd1602.h"
#include "ds18b20.h"
#include "control.h"

void timer_init(void){
    HEATER_DDR = (1 << HEATER_BIT);
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS12);
    ICR1 = 3904;
    OCR1A = 3600;
}

int main(){
    timer_init();
    lcd_init();
    control_init();
    buttons_init();

    ds18b20_start_conversion();
    uint16_t tick_ms = 0;

    while(1){
        ButtonEvent btn = buttons_poll();
        const SystemStatus *st = control_get_status();

        if(btn == BTN_EVENT_START){
            control_start_stop();
        }
        else if(btn == BTN_EVENT_UP){
            control_set_target_temp(st->target_temp + 5);
        }
        else if(btn == BTN_EVENT_DOWN){
            control_set_target_temp(st->target_temp - 5);
        }
        else if(btn == BTN_EVENT_PROFILE){
            ProfileType next = (st->profile == PROFILE_6L) ? PROFILE_20L : PROFILE_6L;
            control_set_profile(next);
        }
        
        if(tick_ms >= 1000){
            tick_ms = 0;
            int16_t temp = ds18b20_read_temp();
            control_update_temp(temp);
            control_tick();

            ds18b20_start_conversion();
        }
        if((tick_ms % 200) == 0){
            lcd_render_status(control_get_status());
        }
        _delay_ms(20);
        tick_ms += 20;
    }
}









































