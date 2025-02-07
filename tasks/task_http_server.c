/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

#include "task_http_server.h"

void task_http_server(void *pvParameters) {

   while (1)
   {
      cyw43_arch_poll(); // Necessário para manter o Wi-Fi ativo
      vTaskDelay( 500 );
   }
      
}
