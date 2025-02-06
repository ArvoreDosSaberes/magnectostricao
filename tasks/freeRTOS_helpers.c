#include "FreeRTOS.h"
#include "task.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "hardware/i2c.h"

#include "inc/ssd1306.h"

// Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
static struct render_area frame_area = {
  start_column : 0,
  end_column : ssd1306_width - 1,
  start_page : 0,
  end_page : ssd1306_n_pages - 1
};

// zera o display inteiro
static uint8_t ssd[ssd1306_buffer_length];


// buffer de texto para o display oled
static char text_line_oled[max_text_lines][max_text_columns];

void vApplicationMallocFailedHook( void ){
      strcpy(text_line_oled[0], "***************");
      strcpy(text_line_oled[1], "               ");
      strcpy(text_line_oled[2], "    Erro na    ");
      strcpy(text_line_oled[3], "   alocacao    ");
      strcpy(text_line_oled[4], "  de memoria   ");
      strcpy(text_line_oled[5], "               ");
      strcpy(text_line_oled[6], "               ");
      strcpy(text_line_oled[7], "***************");
      uint8_t y = 0;
      for (uint i = 0; i < count_of(text_line_oled); i++)
      {
        ssd1306_draw_string(ssd, 5, y, text_line_oled[i]);
        y += ssd1306_line_height;
      }
      render_on_display(ssd, &frame_area);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
      strcpy(text_line_oled[0], "***************");
      strcpy(text_line_oled[1], "               ");
      strcpy(text_line_oled[2], " stack overflow");
      strcpy(text_line_oled[3], "               ");
      strcpy(text_line_oled[4], pcTaskName);
      strcpy(text_line_oled[5], "               ");
      strcpy(text_line_oled[6], "               ");
      strcpy(text_line_oled[7], "***************");
      uint8_t y = 0;
      for (uint i = 0; i < count_of(text_line_oled); i++)
      {
        ssd1306_draw_string(ssd, 5, y, text_line_oled[i]);
        y += ssd1306_line_height;
      }
      render_on_display(ssd, &frame_area);
    while (1);
}