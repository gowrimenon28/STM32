#include "stm32f0xx.h"
#include "bytestuff.h"

void USART2_Init(void) {
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIOA->MODER &= ~((3 << (2 * 2)) | (3 << (2 * 3)));  // PA2/PA3
    GPIOA->MODER |=  ((2 << (2 * 2)) | (2 << (2 * 3)));
    GPIOA->AFR[0] |= (1 << (4 * 2)) | (1 << (4 * 3));

    USART2->BRR = 48000000 / 115200;
    USART2->CR1 |= USART_CR1_TE | USART_CR1_UE;
}

void usart_send(uint8_t byte) {
    while (!(USART2->ISR & USART_ISR_TXE));
    USART2->TDR = byte;
}

int main(void) {
    USART2_Init();
    while (1) {
        int16_t value = 1234;
        send_packet(value, usart_send);
        for (volatile int i = 0; i < 800000; i++);  // ~1 sec delay
    }
}
