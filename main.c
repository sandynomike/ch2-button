//  Challenge 2, Button
//  Mike Shegedin, 03/2023
//
//  Object: Turn ON the LED built into the Blue Pill when a button is pressed, and turn
//          the LED OFF when the button is released.
//
//  Hardware Setup:
//  ===============
//  Install a button (tactile switch) between pin A12 and ground.

//  Software Setup:
//  ===============
//  1. Set up GPIO PORT A, Pin A12 as input with internal pullup resistor.
//     Enable IO Port A in the RCC APB2ENR register.
//     Set the configuration and mode of pin A4 as input with internal pullup resistor.
//  2. Set up GPIO PORT C, Pin C13 (LED built-into Blue Pill) as an output, push-pull, 2 Mhz.
//     Enable IO Port C in the RCC APB2ENR register.
//     Set the configuration and mode of pin C13 as output, push-pull, 2 MHz.

#include "stm32f103xb.h"

int
main( void )
{
    // Enable GPIO Ports A and C
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;

    // Set up pin A4 as input with internal pullup resistor
    // CNF4[1:0] = 0b10 (Input with pullup/pulldown)
    GPIOA->CRH &= ~GPIO_CRH_CNF12_Msk;        // Clear CNF bits
    GPIOA->CRH |= GPIO_CRH_CNF12_1;           // Set 1-bit

    // MODE4[1:0] = 0b00 (Input Mode -- This is the default state, so no settings needed)

    // Set pullup by setting ODR4 to 1
    GPIOA->ODR |= GPIO_ODR_ODR12;

    // Set up pin C13 as an output with push-pull, 2 MHz max speed.
    // CNF13[1:0] = 0b00 (General purpose output, push-pull)
    // Clear CNF13[1:0]
    // Note that the default state of CNFxx[1:0] = 0b01, so the 0-bit must be cleared.
    GPIOC->CRH &= ~GPIO_CRH_CNF13_Msk;  // This clears both bits of CNF13

    // Set MODE13[1:0] to 0b10 (Output mode, 2 MHz)
    GPIOC->CRH |= GPIO_CRH_MODE13_1;          // This sets bit 1 of MODE13

    while( 1 )                                // Endless loop to flash LED
    {
        // Test Pin A12 for a 1. Will be zero if the button is pressed and the pullup resistor
        // is grounded.
        // Note that on the Blue Pill, setting pin C13 to a 0 will turn the built-in LED ON and
        // setting pin C13 to a 1 will turn it OFF (for some reason!)
        if( !(GPIOA->IDR & GPIO_IDR_IDR12) )   // If button pressed,
          GPIOC->ODR &= ~GPIO_ODR_ODR13;      // then turn ON LED by making pin low,
        else                                  // otherwise
          GPIOC->ODR |= GPIO_ODR_ODR13;       // turn OFF LED by making pin high.
    }
} // End main.c
