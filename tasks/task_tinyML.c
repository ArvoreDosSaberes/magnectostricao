/**
 * @file tasks.c
 * @author Carlos Delfino
 * @brief Tarefas para uso no Captador Acustico inteligente
 */

/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

#include "task_adc_with_dma.h"

extern uint16_t adc_buffer[SAMPLES];

extern QueueHandle_t  adc_Buffer_Semaphore;

/**
 * @brief Tarefa para uso do TinyML
 * 
 * @details 
 *  Classifica o audio captado pelo microfone usando o TinyML.
 * 
 * @see task_adc_with_dma
 */
void task_tinyML(void *pvParameters){
    /* Unused parameters. */
    ( void ) pvParameters;

    while (1)    
    {
        printf("Task TinyML\n");
        // implementa código que classifica as amostras captadas pelo microfone
        // esta task está atrelada a task_adc_with_dma, que deverá emitir 
        // um evento ou depositar num queue a leitura feita
        vTaskDelay(100 / portTICK_PERIOD_MS); /* delay 100 ticks */
    }
}