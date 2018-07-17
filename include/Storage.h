
#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>

uint8_t EEPROMInitialize (void);
uint8_t EEPROMWrite (uint16_t addr, uint8_t data);
uint8_t EEPROMRead (uint16_t addr, uint8_t *data);

#endif
