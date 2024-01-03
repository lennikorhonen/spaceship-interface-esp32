#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define RED_LED_1 27
#define RED_LED_2 26
#define GREEN_LED 25
#define BUTTON 13

/*
 * handle_button_press()
 * Checks if button is pressed and turns leds on and off according to that
*/
void handle_button_press(void)
{
    // Get button level
    int button_level = gpio_get_level(BUTTON);

    if (button_level == 0) {
        gpio_set_level(GREEN_LED, 1);

        gpio_set_level(RED_LED_1, 0);
        gpio_set_level(RED_LED_2, 0);
    }
    else {
        gpio_set_level(GREEN_LED, 0);
        gpio_set_level(RED_LED_2, 0);

        gpio_set_level(RED_LED_1, 1);

        vTaskDelay(250 / portTICK_PERIOD_MS);
        gpio_set_level(RED_LED_2, 1);
        gpio_set_level(RED_LED_1, 0);
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    // Reset pins
    gpio_reset_pin(BUTTON);
    gpio_reset_pin(RED_LED_1);
    gpio_reset_pin(RED_LED_2);
    gpio_reset_pin(GREEN_LED);

    // Set pin direction to input and output
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_direction(RED_LED_1, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(RED_LED_2, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(GREEN_LED, GPIO_MODE_INPUT_OUTPUT);

    while(1) {
        handle_button_press();
    }
}
