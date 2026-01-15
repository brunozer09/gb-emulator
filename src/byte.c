#include "byte.h"
#include <stdint.h>

uint16_t make_16(uint8_t lowByte, uint8_t highByte){
  return (highByte << 8) | lowByte;
}
