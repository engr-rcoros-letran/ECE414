#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BUTTON_PIN GPIO_NUM_23

void app_main(void) {
    // Configure the button pin as input with internal pull-up enabled
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_DISABLE  // No interrupts used here
    };
    gpio_config(&io_conf);


    // Poll the button state in a loop for debugging purposes
    int last_state = 1;  // Initially, button is not pressed (pulled up)
    while (1) {
        int current_state = gpio_get_level(BUTTON_PIN);
        // Check for a falling edge (transition from high to low)
        if (last_state == 1 && current_state == 0) {
            printf("Button pressed!\n");
        }
        last_state = current_state;
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Short delay to debounce and reduce CPU usage
    }
}
