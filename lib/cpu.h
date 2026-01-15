#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>

typedef struct{
  bool c; //Carry flag
  bool h; //Half carry flag
  bool n; //Subtraction flag
  bool z; //Zero flag;
} Flags;

uint8_t getFlagRegister(Flags *flag);
void updateFlagRegister(Flags *flag, uint8_t value);

typedef struct{
  uint8_t a; //Accumulator register
  uint8_t b;
  uint8_t c;
  uint8_t d;
  uint8_t e;
  uint8_t f;
  uint8_t h;
  uint8_t l;
  
  Flags flag;
  
  uint16_t sp;  //Stack Pointer 
  uint16_t pc;  //Program Counter
}

#endif
