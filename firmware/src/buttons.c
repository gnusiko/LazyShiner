#include "buttons.h"
#include "config.h"
void buttons_init(void){
    BTN_DDR &= ((1 << BTN_START) | (1 << BTN_DOWN) | (1 << BTN_UP));
    BTN_PORT |= (1 << BTN_START) | (1 << BTN_DOWN) | (1 << BTN_UP);
}

ButtonEvent buttons_poll(void){
    static uint8_t pref_state = 0xFF;
    uint8_t curr_state = BTN_PIN;

    ButtonEvent event = BTN_EVENT_NONE;

    uint8_t both_mask = (1 << BTN_UP) | (1 << BTN_DOWN);
    if(((curr_state & both_mask) == 0) && ((pref_state & both_mask) != 0)){
        event = BTN_EVENT_PROFILE;
    }
    else if (!(curr_state & (1 << BTN_START)) && (pref_state & (1 << BTN_START))){
        event = BTN_EVENT_START;
    }
    else if (!(curr_state & (1 << BTN_UP)) && (pref_state & (1 << BTN_UP))){
        event = BTN_EVENT_UP;
    }
    else if (!(curr_state & (1 << BTN_DOWN)) && (pref_state & (1 << BTN_DOWN))){
        event = BTN_EVENT_DOWN;
    }
    pref_state = curr_state;
    return event;
}
