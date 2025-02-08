/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

#include "pico/cyw43_arch.h"

#include "task_http_server.h"

void task_http_server(void *pvParameters) {

   TickType_t xLastWakeTime = xTaskGetTickCount();
   while (1)
   {
      cyw43_arch_poll(); // Necessário para manter o Wi-Fi ativo
      printf("Task HTTP Server\ %d\n", xLastWakeTime);
      xTaskDelayUntil(xLastWakeTime, 500 / portTICK_PERIOD_MS);
   }
      
}
