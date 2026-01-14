#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint8_t entry_point[4]; 
  uint8_t nintendo_logo[48];
  unsigned char title[16];
  unsigned char manufacturer_code[4];
  uint8_t cgb_flag;
  unsigned char new_licensee_code[2];
  uint8_t sgb_flag;
  uint8_t cartridge_type;
  uint8_t rom_size;
  uint8_t ram_size;
  uint8_t destination_code;
  uint8_t old_licensee_code;
  uint8_t mask_rom_version_num;
  uint8_t header_checksum;
  uint16_t global_checksum; 
} Header;

typedef struct{
  Header header;
} Cartridge;

Header getHeader(const uint8_t *rom);
void printInfo(Header *header);

#endif  
