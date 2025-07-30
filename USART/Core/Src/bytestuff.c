/*
 * bytestuff.c
 *
 *  Created on: Jul 21, 2025
 *      Author: praje
 */

#include "bytestuff.h"
#include "crc.h"

void send_stuffed_byte(uint8_t byte, void (*send_func)(uint8_t)) {
    if (byte == START_BYTE || byte == END_BYTE || byte == ESC_BYTE) {
        send_func(ESC_BYTE);
        send_func(byte ^ 0x20);
    } else {
        send_func(byte);
    }
}

void send_packet(int16_t value, void (*send_func)(uint8_t)) {
    uint8_t data[2] = { (value >> 8) & 0xFF, value & 0xFF };
    uint8_t crc = calculate_crc(data, 2);

    send_func(START_BYTE);
    send_stuffed_byte(data[0], send_func);
    send_stuffed_byte(data[1], send_func);
    send_stuffed_byte(crc, send_func);
    send_func(END_BYTE);
}

