#include <stdint.h>

// RCC and GPIO base
#define RCC_AHBENR     (*(volatile uint32_t*)0x40021014)
#define RCC_APB1ENR    (*(volatile uint32_t*)0x4002101C)

// GPIOA (USART2) and GPIOC (LED)
#define GPIOA_MODER    (*(volatile uint32_t*)0x48000000)
#define GPIOA_AFRL     (*(volatile uint32_t*)0x48000020)
#define GPIOC_MODER    (*(volatile uint32_t*)0x48000800)
#define GPIOC_ODR      (*(volatile uint32_t*)0x48000814)

// USART2 registers
#define USART2_BASE    0x40004400
#define USART2_CR1     (*(volatile uint32_t*)(USART2_BASE + 0x0C))
#define USART2_BRR     (*(volatile uint32_t*)(USART2_BASE + 0x08))
#define USART2_ISR     (*(volatile uint32_t*)(USART2_BASE + 0x1C))
#define USART2_RDR     (*(volatile uint32_t*)(USART2_BASE + 0x24))

#define PC8_PIN        8



// ========== LED Setup ==========
void PC8_Init(void) {
    RCC_AHBENR |= (1 << 19);  // Enable GPIOC clock
    GPIOC_MODER &= ~(3 << (2 * PC8_PIN));  // Clear mode
    GPIOC_MODER |=  (1 << (2 * PC8_PIN));  // Output mode
}

void PC8_On(void) {
    GPIOC_ODR |= (1 << PC8_PIN);
}

void PC8_Off(void) {
    GPIOC_ODR &= ~(1 << PC8_PIN);
}

// ========== USART2 Setup ==========
void USART2_Init(void) {
    RCC_AHBENR  |= (1 << 17);  // Enable GPIOA clock
    RCC_APB1ENR |= (1 << 17);  // Enable USART2 clock

    // PA2 (TX), PA3 (RX) alternate function mode (AF1)
    GPIOA_MODER &= ~((3 << (2 * 2)) | (3 << (2 * 3)));
    GPIOA_MODER |=  ((2 << (2 * 2)) | (2 << (2 * 3)));

    GPIOA_AFRL &= ~((0xF << (4 * 2)) | (0xF << (4 * 3)));
    GPIOA_AFRL |=  ((1 << (4 * 2)) | (1 << (4 * 3)));  // AF1

    USART2_BRR = 48000000 / 9600;  // Baud = 9600 @ 48 MHz
    USART2_CR1 |= (1 << 5);        // Enable RXNE interrupt
    USART2_CR1 |= (1 << 2) | (1 << 3) | (1 << 0);  // RE | TE | UE

    // Enable USART2 IRQ in NVIC
    *((volatile uint32_t*)0xE000E100) |= (1 << 29);  // NVIC_ISER0 for USART2
}

// ========== Main ==========
int main(void) {
    PC8_Init();
    USART2_Init();

    while (1) {
        // Main loop does nothing; USART2 IRQ handles everything
    }
}

// ========== USART2 IRQ Handler ==========
void USART2_IRQHandler(void) {
    if (USART2_ISR & (1 << 5)) {  // RXNE flag set
        char byte = USART2_RDR;

        if (byte == 'O') {
            PC8_On();
        } else if (byte == 'F') {
            PC8_Off();
        }
    }
}
