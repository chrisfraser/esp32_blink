/*
 * Created by: Chris Fraser (@thegwa)
 * Email: hello<at>chrisfraser<dot>co<dot>za
 * License: MIT
 *
 * Blink
 * Step 1: Flash an LED
 * Step 2: ...
 * Step 3: Profit
 */

#include <espressif/esp_common.h>
#include <freertos/task.h>
#include <freertos/FreeRTOS.h>

// Drivers
#include <gpio.h>

// LED pin
// Connect led+ to pin below
// Ensure that the resistor keeps current below 6mA
int pin = 17;

// blinkTask for LED
void blinkTask(void *p) {
	while (1) {
		printf("PIN:%i ON\n", pin);
		// Set the pin to high
		GPIO_OUTPUT_SET(pin, 1);

		// For some reason FreeRTOS has a tick rate of 100Hz
		// Dividing by portTICK_RATE_MS fixes ms values
		vTaskDelay(1000 / portTICK_RATE_MS);

		printf("PIN:%i OFF\n", pin);

		// Set the pin to low
		GPIO_OUTPUT_SET(pin, 0);
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

// "main" method
void user_init(void) {
	// Print out some interesting things
	printf("SDK version:%s\n", system_get_sdk_version());
	printf("CPU running at %dMHz\n", system_get_cpu_freq());
	printf("Free Heap size: %d\n", system_get_free_heap_size());
	system_print_meminfo();

	printf("Starting blinkTask");
	printf("==================================================================");
	// Create the blink task
	xTaskCreate(blinkTask, (signed char * )"blinkTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}
