#include "cartridge.h"

Header getHeader(const uint8_t *rom){ 
  Header header;

  memcpy(header.entry_point, rom+0x0100, 4);
  memcpy(header.nintendo_logo, rom+0x0104, 48);
  memcpy(header.title, rom+0x0134, 16);
  memcpy(header.manufacturer_code, rom+0x013F, 4);
  header.cgb_flag = rom[0x0143];
  memcpy(header.new_licensee_code, rom+0x0144, 4);

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
