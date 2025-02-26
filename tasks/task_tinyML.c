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

#include "inc/magnectostriccao.h"
#include "task_adc_with_dma.h"
#include "tasks_paramiters.h"

static uint16_t adc_buffer[ADC_SAMPLES];

extern QueueHandle_t xTinyML_Buffer_Queue;

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
        printf("Inicio Loop Task TinyML %d\n", xPreviousWakeTime);
        
        if(xQueueReceive(xTinyML_Buffer_Queue, adc_buffer, ADC_TO_FFT_QUEUE_TIMEOUT) == pdPASS){
            printf("TinyML: sucesso ao receber dado de xTinyML_Buffer_Queue\n");

            // implementa código que classifica as amostras captadas pelo microfone

            // Uma vez classificadas cada bloco de amostras deve ser enviada para o computador de borda
            // implementa código que envia o resultado para o computador de borda
            // me parece que o ideal é coletar um bloco de amostras algo como 1 a 2 minutos para 
            // fazer uma classificação adequada
        }        
        
        printf("antes da pausa Loop Task TinyML %d\n", xPreviousWakeTime);
        xTaskDelayUntil(&xPreviousWakeTime, TASK_TINYML_DELAY); /* delay 100 ticks */
        printf("Fim Loop Task TinyML %d\n", xPreviousWakeTime);
    }
}