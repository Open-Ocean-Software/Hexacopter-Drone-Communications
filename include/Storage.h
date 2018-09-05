
#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>

/**
 * Initializes the EEPROM.
 * @return  Success code
 */
uint8_t EEPROMInitialize (void);
/**
 * Writes data to the EEPROM.
 * @param  addr The address
 * @param  data The payload
 * @return      Success code
 */
uint8_t EEPROMWrite (uint16_t addr, uint8_t data);
/**
 * Reads data from the EEPROM.
 * @param  addr The address
 * @param  data The payload
 * @return      Success code
 */
uint8_t EEPROMRead (uint16_t addr, uint8_t *data);

#endif
