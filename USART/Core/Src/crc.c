/*
 * crc.c
 *
 *  Created on: Jul 21, 2025
 *      Author: praje
 */

#include "crc.h"

uint8_t calculate_crc(const uint8_t *data, uint8_t len) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
    }
    return crc;
}

