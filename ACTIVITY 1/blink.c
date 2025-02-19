#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2  // Most ESP32 boards have the built-in LED on GPIO2

void vBlinkTask(void *pvParameters)
{
    // Configure the LED pin as an output
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(LED_PIN, 1); // Turn LED ON
        printf("LED ON\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1-second delay

        gpio_set_level(LED_PIN, 0); // Turn LED OFF
        printf("LED OFF\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1-second delay
    }
}


void vPrintString(const char *pcString)
{
    printf("%s", pcString); // Prints the string to the standard output
}

void vTask1(void *pvParameters)
{
    const char *pcTaskName = "Task 1 is running\r\n";

    for( ;; )
    {
        vPrintString(pcTaskName);
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1-second delay
    }
}

void vTask2(void *pvParameters)
{
    const char *pcTaskName = "Task 2 is running\r\n";

    for( ;; )
    {
        vPrintString(pcTaskName);
        vTaskDelay(pdMS_TO_TICKS(1500)); // 1.5-second delay
    }
}

void app_main(void) {
    xTaskCreate(vTask1, "Task 1", 2048, NULL, 3, NULL);
    xTaskCreate(vTask2, "Task 2", 2048, NULL, 2, NULL);
    xTaskCreate(vBlinkTask, "BlinkTask", 2048, NULL, 1, NULL);
}
