
#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>

typedef enum{
    STATE_IDLE = 0,
    STATE_HEATUP,
    STATE_WORK,
    STATE_ALARM
}SystemState;

typedef enum{
    PROFILE_6L = 0,
    PROFILE_20L
}ProfileType;

typedef enum{
    ERR_NONE = 0,
    ERR_SENSOR_LOST,
    ERR_OVERHEAT
}ErrorCode;

typedef struct{
    SystemState     state;
    ProfileType     profile;
    ErrorCode       error;
    int16_t         current_temp;
    int16_t         target_temp;
    uint8_t         power_pct;
}SystemStatus;

void control_init(void);

void control_tick(void);

void control_update_temp(int16_t temp_deci);
void control_set_target_temp(int16_t temp_deci);
void control_set_profile(ProfileType profile);
void control_start_stop(void);

const SystemStatus* control_get_status(void);

#endif // CONTROL_H