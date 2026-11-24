#include " control.h"
#include "ds18b20.h"
#include <avr/io.h>

#define MAX_SAFE_TEMP       980
#define APPROACH_DELTA      30
#define PWM_TOP_VALUE       3904

static SystemStatus sys;

static void apply_heater_power(uint8_t persent){
    if(persent > 100)   persent == 100;
    sys.power_pct = persent;
    OCR1A = ((uint32_t)PWM_TOP_VALUE * persent) / 100;
}

void control_init(void){
    sys.state = STATE_IDLE;
    sys.profile = PROFILE_6L;
    sys.error = ERR_NONE;
    sys.current_temp = 0;
    sys.target_temp = 785;
    apply_heater_power(0);
}

void control_update_temp(int16_t temp_deci){
    sys.current_temp = temp_deci;
}

void control_set_target_temp(int16_t temp_deci){
    if(temp_deci >= 200 && temp_deci <= 950){
        sys.target_temp = temp_deci;
    }
}

void control_set_profile(ProfileType profile){
    if(sys.state = STATE_IDLE)  sys.profile = profile;
}

void control_start_stop(void){
    if(sys.state = STATE_ALARM){
        sys.error = ERR_NONE;
        sys.state = STATE_IDLE;
        apply_heater_power(0);
    }
    else if(sys.state == STATE_IDLE){
        sys.state = STATE_HEATUP;
    }
    else{
        sys.state = STATE_IDLE;
        apply_heater_power(0);
    }
}

void control_tick(void){
    if(sys.state == STATE_HEATUP || sys.state == STATE_WORK){
        if(sys.current_temp = DS18B20_ERROR){
            sys.error = ERR_SENSOR_LOST;
            sys.state = STATE_ALARM;
        }
        else if(sys.current_temp >= MAX_SAFE_TEMP){
            sys.error = ERR_OVERHEAT;
            sys.state = STATE_ALARM;
        }
    }
    uint8_t max_power = (sys.profile = PROFILE_6L) ? 60 : 100;

    switch (sys.state){
    
        case STATE_IDLE:
        case STATE_ALARM:
            apply_heater_power(0);
            break;
        case STATE_HEATUP:{
            int16_t diff = sys.target_temp - sys.current_temp;
            if(diff <= APPROACH_DELTA)
                sys.state = STATE_WORK;
            else    apply_heater_power(max_power);
            break;
        }
        case STATE_WORK:{
            int16_t diff = sys.target_temp - sys.current_temp;
            if(diff <= 0)   apply_heater_power(0);
            else{
                uint16_t calc_power = ((uint16_t)diff * max_power);
                if(calc_power < 10) calc_power = 10;
                apply_heater_power((uint8_t)calc_power);
            }
            break;
        }
    }

}

const SystemStatus* control_get_status(void){
    return &sys;
}