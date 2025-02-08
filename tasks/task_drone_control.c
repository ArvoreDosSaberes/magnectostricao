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

#include "task_adc_with_dma.h"
#include "tasks_paramiters.h"

/**
 * @brief Controls the drone operations.
 *
 * @details This task is responsible for managing drone-related activities.
 * It runs indefinitely, executing control logic at a regular interval.
 *
 * @param pvParameters Pointer to the parameters passed during task creation (unused).
 *
 * @note The task includes a delay of 100 ticks between iterations.
 */
void task_drone_control(void *pvParameters){
    /* Unused parameters. */
    ( void ) pvParameters;

    printf("Task Drone Control\n");
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)    
    {
        // Implementar código que recebe os comandos do computador de borda via
        // servidor web.
        // Estes comandos serão enviados pela GPIO para os motores e sensores do drone
        // awqui se usa o 

        //printf("Loop Task Drone Control %d\n", xLastWakeTime);
        xTaskDelayUntil(&xLastWakeTime, TASK_DRONE_CONTROL_DELAY); /* delay 100 ticks */
    }
}