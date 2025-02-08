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

#include "stdio.h"
#include "string.h"
#include "pico/stdlib.h"

#include "task_adc_with_dma.h"
#include "tasks_paramiters.h"

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

    printf("Task TinyML\n");
        
    TickType_t xPreviousWakeTime = xTaskGetTickCount();
    while (1)    
    {
        //printf("Loop Task TinyML %d\n", xPreviousWakeTime);
        
        // implementa código que classifica as amostras captadas pelo microfone
        // esta task está atrelada a task_adc_with_dma, que deverá emitir 
        // um evento ou depositar num queue a leitura feita
        
        xTaskDelayUntil(&xPreviousWakeTime, TASK_TINYML_DELAY); /* delay 100 ticks */
    }
}