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

#include "task_display_oled.h"
#include "tasks_paramiters.h"

#include "inc/ssd1306.h"

char text_line_oled[max_text_lines][max_text_columns];
/**
 * @brief Tarefa para uso do Display OLED
 *
 * @details
 *
 */
void task_display_oled(void *pvParameters)
{
    printf("Task Display OLED\n");
    /* Unused parameters. */
    (void)pvParameters;

    vTaskSuspendAll();
    memcpy(text_line_oled[0], "               ", max_text_columns);
    memcpy(text_line_oled[1], " Nivel do Sinal", max_text_columns);
    memcpy(text_line_oled[2], "               ", max_text_columns);
    memcpy(text_line_oled[3], "               ", max_text_columns);
    memcpy(text_line_oled[4], "               ", max_text_columns);
    memcpy(text_line_oled[5], "               ", max_text_columns);
    memcpy(text_line_oled[6], "               ", max_text_columns);
    memcpy(text_line_oled[7], "               ", max_text_columns);
    xTaskResumeAll();
        
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    // zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];

    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        // ssd1306_write_array(ssd, &frame_area, &text);
        printf("Task Display OLED %d\n", xLastWakeTime);
        
        vTaskSuspendAll();
        printf(text_line_oled[0]);
        printf("\n");
        printf(text_line_oled[1]);
        printf("\n");
        printf(text_line_oled[2]);
        printf("\n");
        printf(text_line_oled[3]);
        printf("\n");
        printf(text_line_oled[4]);
        printf("\n");
        printf(text_line_oled[5]);
        printf("\n");
        printf(text_line_oled[6]);
        printf("\n");
        printf(text_line_oled[7]);
        printf("\n");
        printf("\n");

        uint8_t y = 0;
        for (uint i = 0; i < count_of(text_line_oled); i++)
        {
            ssd1306_draw_string(ssd, 5, y, text_line_oled[i]);
            y += ssd1306_line_height;
        }
        render_on_display(ssd, &frame_area);
        xTaskResumeAll();
        
        xTaskDelayUntil(&xLastWakeTime, TASK_DISPLAY_OLED_DELAY); 
        
        //printf("fim loop taskdisplayoled %d\n", xLastWakeTime);
    }
}