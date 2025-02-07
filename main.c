#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

void vBlinkTask(void *pvParameters) {
    while (1) {
        printf("Blink Task Running!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main() {
    stdio_init_all();
    
    xTaskCreate(vBlinkTask, "Blink", 256, NULL, 1, NULL);
    
    vTaskStartScheduler();

    while (1);
}