/*
 * ApplicationCode.c
 *
 *  Created on: Aug 27, 2024
 *      Author: seank
 */

#include <stdint.h>

#define GPIOG_RCC_ENABLE_ADDRESS 0x40023830
#define GPIOG_AHB1ENR_BIT_OFFSET 6
#define GPIOG_MODER_ADDRESS 0x40021800
#define GPIOG_ODR_ADDRESS 0x40021814
#define LED_MODER_OFFSET 28
#define LED_ODR_BIT_OFFSET 14
#define LENGTH_OF_FIRST_NAME 4

void AppDelay(uint32_t time) {

	// Create two arrays to store the name
	char sean[LENGTH_OF_FIRST_NAME] = {'S', 'E', 'A', 'N'};
	[[maybe_unused]] char destinationArray[LENGTH_OF_FIRST_NAME];

	// Iterate through the array to create a crude delay function
	for (int i = 0; i < time; i++) {

		for (int j = 0; j < LENGTH_OF_FIRST_NAME; j++) {

			destinationArray[j] = sean[j];
		}
	}
}

void EnablePeripheralsAndClocks() {

	// Create pointers to access the RCC and MODER registers
	uint32_t * clkPtr = (uint32_t *) GPIOG_RCC_ENABLE_ADDRESS;
	uint32_t * moderPtr = (uint32_t *) GPIOG_MODER_ADDRESS;

	// Emable the peripheral clock
	*clkPtr |= (0x1 << GPIOG_AHB1ENR_BIT_OFFSET);

	// Configure GPIO Pin to properly drive the LED
	*moderPtr &= ~(0x3 << LED_MODER_OFFSET);
	*moderPtr |= (0x1 << LED_MODER_OFFSET);

}

void TurnOnRedLED() {

	// Create a pointer to access the ODR control register
	uint32_t * gpiogODRPtr = (uint32_t*) GPIOG_ODR_ADDRESS;

	// Set the LED GPIO pin to high
	*gpiogODRPtr |= (0x1 << LED_ODR_BIT_OFFSET);

}

void TurnOffRedLED() {

	// Create a pointer to access the ODR control register
	uint32_t * gpiogODRPtr = (uint32_t*) GPIOG_ODR_ADDRESS;

	// Set the LED GPIO pin to LOW
	*gpiogODRPtr &= ~(0x1 << LED_ODR_BIT_OFFSET);

}

void ToggleRedLED() {

	// Create a pointer to access the ODR control register
	uint32_t * gpiogODRPtr = (uint32_t*) GPIOG_ODR_ADDRESS;

	// If the pin is high, turn it low, if the pin is low, turn it high
	if (*gpiogODRPtr) {

		*gpiogODRPtr &= ~(0x1 << LED_ODR_BIT_OFFSET);

	}
	else {

		*gpiogODRPtr |= (0x1 << LED_ODR_BIT_OFFSET);

	}
}















