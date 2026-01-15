#include "cpu.h"
#include <stdint.h>

uint8_t getFlagRegister(Flags *flag){
  return 
    (flag->z << 7)|
    (flag->n << 6)|
    (flag->h << 5)|
    (flag->c << 4)|0;
}

void updateFlagRegister(Flags *flag, uint8_t value){
  flag->c = (value & 0b00010000)>>4;
  flag->h = (value & 0b00100000)>>5;
  flag->n = (value & 0b01000000)>>4;
  flag->z = (value & 0b10000000)>>4;
}
