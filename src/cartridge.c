#include "cartridge.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

Header getHeader(const uint8_t *rom){ 
  Header header;

  memcpy(header.entry_point, rom+0x0100, 4);
  memcpy(header.nintendo_logo, rom+0x0104, 48);
  memcpy(header.title, rom+0x0134, 16);
  memcpy(header.manufacturer_code, rom+0x013F, 4);
  header.cgb_flag = rom[0x0143];
  memcpy(header.new_licensee_code, rom+0x0144, 2);

  header.sgb_flag = rom[0x0146];
  header.cartridge_type = rom[0x0147];
  header.rom_size = rom[0x0148];
  header.ram_size = rom[0x0149];
  header.destination_code = rom[0x014A];
  header.old_licensee_code = rom[0x014B];
  header.mask_rom_version_num = rom[0x014C];
  header.header_checksum = rom[0x014D];
  header.global_checksum = (rom[0x014F] << 8) | (rom[0x014E]); 

  return header;
} 

bool validateHeader(const Header *header){
  bool valid = true;
  uint8_t n_LOGO[48] = {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88,0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};
  
  if(memcmp(n_LOGO, header->nintendo_logo, 48) != 0)
    valid = false;

  return valid;
}

Cartridge getRomInfo(const uint8_t *rom){
  Cartridge cartridge;
  cartridge.header = getHeader(rom);

  cartridge.isValid = validateHeader(&cartridge.header);

  return cartridge;
}

void printCartridgeType(uint8_t cartridge_type)
{
  for (size_t i = 0; i < sizeof(cartridge_types)/sizeof(cartridge_types[0]); i++) {
    if (cartridge_types[i].type == cartridge_type) {
      printf("%s", cartridge_types[i].name);
      return;
    }
  }

  printf("Unknown");
}

void printNewLicenseeCode(const char *new_licensee_code)
{
  for (size_t i = 0; i < sizeof(licensees)/sizeof(licensees[0]); i++) {
    if (strncmp(new_licensee_code, licensees[i].code, 2) == 0) {
      printf("%s", licensees[i].name);
      return;
    }
  }
  printf("Unknown");
}

void printOldLicenseeCode(uint8_t old_licensee_code)
{
  for (size_t i = 0; i < sizeof(old_licensees)/sizeof(old_licensees[0]); i++) {
    if (old_licensees[i].code == old_licensee_code) {
      printf("%s", old_licensees[i].name);
      return;
    }
  }

  printf("???");
}

void printInfo(const Cartridge *cartridge){
  printf("TITLE: %s\n", cartridge->header.title);
  printf("ROM SIZE: %d\n", cartridge->header.rom_size);
  printf("MANUFACTURER CODE: %s\n", cartridge->header.manufacturer_code);
  
  if(cartridge->isValid){
    printf("VALID: YES\n");
  }
  else{
    printf("VALID:NO\n");
  }

  if(cartridge->header.old_licensee_code != 0x33){
    printf("OLD LICENSEE CODE: "); printOldLicenseeCode(cartridge->header.old_licensee_code);
    printf("\n");
  }
  else{
    printf("NEW LICENSEE CODE: "); printNewLicenseeCode(cartridge->header.new_licensee_code);
    printf("\n");
  }
}
