#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>

typedef enum{
    BTN_EVENT_NONE = 0,
    BTN_EVENT_START,
    BTN_EVENT_DOWN,
    BTN_EVENT_UP,
    BTN_EVENT_PROFILE
}ButtonEvent;

void buttons_init(void);

ButtonEvent buttons_poll(void);

#endif