/**
 * @brief Tarefa para manter o display OLED atualziado
 * 
 * 
 * @details 
 *  Obtem no array text_line_oled o texto a ser exibido no display OLED.
 * 
 * @see task_adc_with_dma
 */

#ifndef  __TASK_DISPLAY_OLED_H__
#define  __TASK_DISPLAY_OLED_H__

void task_display_oled(void *pvParameters);

#endif // TASK_TINY_ML_H