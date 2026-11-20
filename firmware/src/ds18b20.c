
#include "ds18b20.h"
#include "onewire.h"
#define CMD_SKIP_ROM        0xCC    // Ack all device
#define CMD_CONVERT_T       0X44    // Measuremen temperature
#define CMD_READ_SCRATCHPAD 0XBE    // Request device memory

uint8_t ds18b20_start_conversion(void){         // Order for measure of temperature
    if(! ow_reset()){
        return 0;
    }
    ow_write_byte(CMD_SKIP_ROM);
    ow_write_byte(CMD_CONVERT_T);
    return 1;
}

int16_t ds18b20_read_temp(void){
    uint8_t msb, lsb;
    if(! ow_reset()){
        return DS18B20_ERROR;
    }
    ow_write_byte(CMD_SKIP_ROM);
    ow_write_byte(CMD_READ_SCRATCHPAD);
    lsb = ow_read_byte();
    msb = ow_read_byte();
    int16_t raw = ((int16_t)msb << 8) | lsb;
    return (raw * 5) / 8;
}