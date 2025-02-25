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

#include "tasks_paramiters.h"
#include "task_fft_filter.h"

/**
 * @brief Tarefa para uso do Fast Fourier Transform
 * 
 * @details 
 *  Filtra ruidos que não são interessantes.
 * 
 * @see task_adc_with_dma
 */
void task_fft_filter(void *pvParameters){
    /* Unused parameters. */
    ( void ) pvParameters;

    printf("Task FFT Filter\n");
        
    TickType_t xPreviousWakeTime = xTaskGetTickCount();
    while (1)    
    {
        printf("Inicio Loop Task FFT Filter %d\n", xPreviousWakeTime);
        
        // implementa código que filtra o audio captado pelo microfone
        // esta task está atrelada a task_adc_with_dma, que deverá emitir 
        // um evento ou depositar num queue a leitura feita
        
        printf("antes da pausa Loop Task FFT Filter %d\n", xPreviousWakeTime);
        xTaskDelayUntil(&xPreviousWakeTime, TASK_TINYML_DELAY); /* delay 100 ticks */
        printf("Fim Loop Task FFT Filter %d\n", xPreviousWakeTime);
    }
}