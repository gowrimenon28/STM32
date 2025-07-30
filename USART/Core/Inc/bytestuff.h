/*
 * bytestuff.h
 *
 *  Created on: Jul 21, 2025
 *      Author: praje
 */

#ifndef INC_BYTESTUFF_H_
#define INC_BYTESTUFF_H_



#include <stdint.h>

#define START_BYTE 0x7E
#define END_BYTE   0x7F
#define ESC_BYTE   0x7D

void send_stuffed_byte(uint8_t byte, void (*send_func)(uint8_t));
void send_packet(int16_t value, void (*send_func)(uint8_t));




#endif /* INC_BYTESTUFF_H_ */
