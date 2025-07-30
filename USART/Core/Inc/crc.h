/*
 * crc.h
 *
 *  Created on: Jul 21, 2025
 *      Author: praje
 */

#ifndef INC_CRC_H_
#define INC_CRC_H_

#include <stdint.h>

uint8_t calculate_crc(const uint8_t *data, uint8_t len);

#endif /* INC_CRC_H_ */
