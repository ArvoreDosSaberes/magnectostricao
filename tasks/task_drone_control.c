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
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "hardware/adc.h"

#include "task_adc_with_dma.h"
#include "tasks_paramiters.h"

/**
 * Envia aceleração para o drone através da porta I2C.
 */
static void send_drone_direction(int x, int y);

// flag definido no main, controlado por interrupção do botão B
extern bool modo_local;
// as acelerações abaixo são obtidos atráves do servidor restful
extern int aceleration_x;
extern int aceleration_y;
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
        if(modo_local){

            adc_select_input(0);
            uint adc_y_raw = adc_read();
            adc_select_input(1);
            uint adc_x_raw = adc_read();

            // Display the joystick position something like this:
            // X: [            o             ]  Y: [              o         ]
            const uint bar_width = 10;  // aceleração máxima
            const uint adc_max = (1 << 12) - 1; // amostragem máxima do ADC
            aceleration_x = (adc_x_raw * bar_width / adc_max) - (adc_max / 2);
            aceleration_y = (adc_y_raw * bar_width / adc_max) - (adc_max / 2);
            send_drone_direction(aceleration_x, aceleration_y);
        }else{
            send_drone_direction(aceleration_x, aceleration_y);
        }

        printf("Inicio Loop Task Drone Control, modo: %d aceleration_x: %d aceleration_y: %d, waketime: %d\n", 
                                                    modo_local, aceleration_x, aceleration_y, xLastWakeTime);

        printf("Fim Loop Task Drone Control %d\n", xLastWakeTime);
        UBaseType_t stackLeft = uxTaskGetStackHighWaterMark(NULL);
        printf("Drone Control Espaço de pilha livre: %u bytes\n", stackLeft);
        xTaskDelayUntil(&xLastWakeTime, TASK_DRONE_CONTROL_DELAY); /* delay 100 ticks */

    }
}

static void send_drone_direction(int x, int y){
    // implementar
    //este código envia via i2c a direção do drone
}