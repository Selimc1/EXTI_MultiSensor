#include "stm32f4xx.h"

void EXTI_Init(void);

int main(void)
{
    EXTI_Init();

    while (1)
    {
        // Interrupt-driven system, no polling required
    }
}
// PA1: Threshold, PA2: LDR, PA3: NTC
// PD12-14: Output LEDs / Relay

void EXTI_Init(void)
{
    // 1. CLOCK ENABLE
    RCC->AHB1ENR |= (1 << 0); // GPIOA
    RCC->AHB1ENR |= (1 << 3); // GPIOD
    RCC->APB2ENR |= (1 << 14); // SYSCFG

    // 2. GPIO CONFIGURATION

    // PA1, PA2, PA3 → INPUT
    GPIOA->MODER &= ~((3 << 2) | (3 << 4) | (3 << 6));

    // Pull-up (stability için)
    GPIOA->PUPDR &= ~((3 << 2) | (3 << 4) | (3 << 6));
    GPIOA->PUPDR |=  ((1 << 2) | (1 << 4) | (1 << 6));

    // PD12, PD13, PD14 → OUTPUT
    GPIOD->MODER &= ~((3 << 24) | (3 << 26) | (3 << 28));
    GPIOD->MODER |=  ((1 << 24) | (1 << 26) | (1 << 28));

    // 3. EXTI CONFIGURATION

    // PA1 → EXTI1, PA2 → EXTI2, PA3 → EXTI3
    SYSCFG->EXTICR[0] &= ~((0xF << 4) | (0xF << 8) | (0xF << 12));

    // Interrupt mask
    EXTI->IMR |= (1 << 1) | (1 << 2) | (1 << 3);

    // Rising edge trigger
    EXTI->RTSR |= (1 << 1) | (1 << 2) | (1 << 3);

    // Falling edge disable (clean config)
    EXTI->FTSR &= ~((1 << 1) | (1 << 2) | (1 << 3));

    // 4. NVIC CONFIGURATION

    NVIC_SetPriority(EXTI1_IRQn, 1);
    NVIC_SetPriority(EXTI2_IRQn, 1);
    NVIC_SetPriority(EXTI3_IRQn, 1);

    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI2_IRQn);
    NVIC_EnableIRQ(EXTI3_IRQn);
}

// PA1 (Threshold)
void EXTI1_IRQHandler(void)
{
    if (EXTI->PR & (1 << 1))
    {

        // Signal verification
        if (GPIOA->IDR & (1 << 1))
        {
            GPIOD->ODR ^= (1 << 12);
        }

        // Clear interrupt flag
        EXTI->PR = (1 << 1);
    }
}

// PA2 (LDR)
void EXTI2_IRQHandler(void)
{
    if (EXTI->PR & (1 << 2))
    {

        if (GPIOA->IDR & (1 << 2))
        {
            GPIOD->ODR ^= (1 << 13);
        }

        EXTI->PR = (1 << 2);
    }
}

// PA3 (NTC)
void EXTI3_IRQHandler(void)
{
    if (EXTI->PR & (1 << 3))
    {

        if (GPIOA->IDR & (1 << 3))
        {
            GPIOD->ODR ^= (1 << 14);
        }

        EXTI->PR = (1 << 3);
    }
}
