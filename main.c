#include "cartridge.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ROM_MAX_SIZE 0xFFFF

int main(int argc, char **argv){
  if(argc < 2){
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *fl = fopen(argv[1], "rb");

  if (fl == NULL){
    printf("Error opening the file");
    return 1;
  }
  
  uint8_t rom[ROM_MAX_SIZE];
  size_t read_bytes = fread(rom, sizeof(uint8_t), ROM_MAX_SIZE, fl);

  if(read_bytes == 0 || ferror(fl)){
    printf("Error reading the file");
    fclose(fl);
    return 1;
  }

  Header rom_header = getHeader(rom);
  printInfo(&rom_header);

  fclose(fl);
  return 0;
}
