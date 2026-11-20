#include "onewire.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#define OW_L OW_DDR |= (1 << OW_BIT)//; OW_PORT &= ~(1 << OW_BIT)
#define OW_H OW_DDR &= ~(1 << OW_BIT)//; OW_PORT &= ~(1 << OW_BIT))

uint8_t ow_reset(void){
    uint8_t availability = 0;
    uint8_t sreg = SREG;
    cli();

    OW_L;
    _delay_us(480);
    OW_H;
    _delay_us(70);

    if(!(OW_PIN & (1 << OW_BIT))){
        availability = 1;
    }

    _delay_us (410);
    SREG =sreg;
    return availability;
}

static void ow_write_bit(uint8_t bit){
    uint8_t sreg = SREG;
    cli();
    
    OW_L;
    if(bit){
        _delay_us(6);
        OW_H;
        _delay_us(64);
    }
    else{
        _delay_us(60);
        OW_H;
        _delay_us(10);
    }
    SREG = sreg;
}

static uint8_t ow_read_bit(void){
    uint8_t bit = 0;
    uint8_t sreg = SREG;
    cli();

    OW_L;
    _delay_us(3);
    OW_H;
    _delay_us(10);

    if(OW_PIN & (1 << OW_BIT)){
        bit = 1;
    }
    _delay_us(53);
    SREG = sreg;
    return bit;
}

void ow_write_byte(uint8_t byte){
    for(uint8_t i = 0; i < 8; i++){
        if((byte &(1 << i)) == 1 << i)
        ow_write_bit(1);
        else
        ow_write_bit(0);
    }
}

uint8_t ow_read_byte(void){
    uint8_t byte = 0;
    for(uint8_t i = 0; i < 8; i++){
        byte |= (ow_read_bit() << i);
    }
    return byte;
}

