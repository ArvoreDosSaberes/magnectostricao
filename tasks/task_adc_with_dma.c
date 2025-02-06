#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "hardware/adc.h"
#include "hardware/dma.h"

#include "inc/neopixel.h"

#include "stdio.h"
#include <math.h>
#include <string.h>

#include "inc/magnectostriccao.h"
#include "task_adc_with_dma.h"

// buffer de texto para o display oled
extern char text_line_oled[max_text_lines][max_text_columns];

// buffer de amostragem do ADC, microfone que coleta o audio
// os samples devem ser no comprimento equivalente aos segundos
// necessários para uma amostragem adequada
uint16_t adc_buffer[SAMPLES];
QueueHandle_t adc_Buffer_Semaphore;

static uint dma_channel;
static dma_channel_config dma_cfg;

void task_adc_with_dma(void *pvParameters)
{

  (void)pvParameters;
  // O código abaixo deve ser transportado para a TASK (FreeRTOS) que
  // faz o processamento da amostragem via DMA
  adc_gpio_init(MIC_PIN);
  adc_init();
  adc_select_input(MIC_CHANNEL);

  adc_fifo_setup(
      true,  // Habilitar FIFO
      true,  // Habilitar request de dados do DMA
      1,     // Threshold para ativar request DMA é 1 leitura do ADC
      false, // Não usar bit de erro
      false  // Não fazer downscale das amostras para 8-bits, manter 12-bits.
  );

  adc_set_clkdiv(ADC_CLOCK_DIV);
  // Tomando posse de canal do DMA.
  dma_channel = dma_claim_unused_channel(true);

  // Configurações do DMA.
  dma_cfg = dma_channel_get_default_config(dma_channel);

  channel_config_set_transfer_data_size(&dma_cfg, DMA_SIZE_16); // Tamanho da transferência é 16-bits (usamos uint16_t para armazenar valores do ADC)
  channel_config_set_read_increment(&dma_cfg, false);           // Desabilita incremento do ponteiro de leitura (lemos de um único registrador)
  channel_config_set_write_increment(&dma_cfg, true);           // Habilita incremento do ponteiro de escrita (escrevemos em um array/buffer)

  channel_config_set_dreq(&dma_cfg, DREQ_ADC); // Usamos a requisição de dados do ADC

  adc_Buffer_Semaphore = xSemaphoreCreateBinary();

  while (1)
  {
    // Realiza uma amostragem do microfone. deve ser transportado para a TASK de amostragem ADC

    if (xSemaphoreTake(adc_Buffer_Semaphore, portMAX_DELAY) == pdTRUE)
    {
      // se o semaforo foi obtido, realiza a leitura do microfone
      sample_mic();
      xSemaphoreGive(adc_Buffer_Semaphore);
    }

    // realiza a exibição do status da coleta de ruidos
    // Pega a potência média da amostragem do microfone.
    float avg = mic_power();
    float db = 20.f * log10(avg / ADC_MAX);
    avg = 2.f * abs(ADC_ADJUST(avg)); // Ajusta para intervalo de 0 a 3.3V. (apenas magnitude, sem sinal)

    uint intensity = get_intensity(avg); // Calcula intensidade a ser mostrada na matriz de LEDs.

    // Limpa a matriz de LEDs.
    npClear();

    // A depender da intensidade do som, acende LEDs específicos.
    switch (intensity)
    {
    case 0:
      strcpy(text_line_oled[3], "   Sem Som    ");
      break; // Se o som for muito baixo, não acende nada.
    case 1:
      strcpy(text_line_oled[3], "   Pouco Som  ");
      npSetLED(12, 0, 0, 80); // Acende apenas o centro.
      break;
    case 2:
      strcpy(text_line_oled[3], " Nivel ideal ");
      npSetLED(12, 0, 0, 120); // Acente o centro.

      // Primeiro anel.
      npSetLED(7, 0, 0, 80);
      npSetLED(11, 0, 0, 80);
      npSetLED(13, 0, 0, 80);
      npSetLED(17, 0, 0, 80);
      break;
    case 3:
      strcpy(text_line_oled[3], "   Alto Som   ");
      // Centro.
      npSetLED(12, 60, 60, 0);

      // Primeiro anel.
      npSetLED(7, 0, 0, 120);
      npSetLED(11, 0, 0, 120);
      npSetLED(13, 0, 0, 120);
      npSetLED(17, 0, 0, 120);

      // Segundo anel.
      npSetLED(2, 0, 0, 80);
      npSetLED(6, 0, 0, 80);
      npSetLED(8, 0, 0, 80);
      npSetLED(10, 0, 0, 80);
      npSetLED(14, 0, 0, 80);
      npSetLED(16, 0, 0, 80);
      npSetLED(18, 0, 0, 80);
      npSetLED(22, 0, 0, 80);
      break;
    case 4:
      strcpy(text_line_oled[3], "Muito Alto Som");
      // Centro.
      npSetLED(12, 80, 0, 0);

      // Primeiro anel.
      npSetLED(7, 60, 60, 0);
      npSetLED(11, 60, 60, 0);
      npSetLED(13, 60, 60, 0);
      npSetLED(17, 60, 60, 0);

      // Segundo anel.
      npSetLED(2, 0, 0, 120);
      npSetLED(6, 0, 0, 120);
      npSetLED(8, 0, 0, 120);
      npSetLED(10, 0, 0, 120);
      npSetLED(14, 0, 0, 120);
      npSetLED(16, 0, 0, 120);
      npSetLED(18, 0, 0, 120);
      npSetLED(22, 0, 0, 120);

      // Terceiro anel.
      npSetLED(1, 0, 0, 80);
      npSetLED(3, 0, 0, 80);
      npSetLED(5, 0, 0, 80);
      npSetLED(9, 0, 0, 80);
      npSetLED(15, 0, 0, 80);
      npSetLED(19, 0, 0, 80);
      npSetLED(21, 0, 0, 80);
      npSetLED(23, 0, 0, 80);
      break;
    }
    // Atualiza a matriz.
    npWrite();

    sprintf(text_line_oled[5], "   %02.2f dB     ", db);
  }
}

/**
 * Realiza as leituras do ADC e armazena os valores no buffer.
 */
void sample_mic()
{
  adc_fifo_drain(); // Limpa o FIFO do ADC.
  adc_run(false);   // Desliga o ADC (se estiver ligado) para configurar o DMA.

  dma_channel_configure(dma_channel, &dma_cfg,
                        adc_buffer,      // Escreve no buffer.
                        &(adc_hw->fifo), // Lê do ADC.
                        SAMPLES,         // Faz SAMPLES amostras.
                        true             // Liga o DMA.
  );

  // Liga o ADC e espera acabar a leitura.
  adc_run(true);
  dma_channel_wait_for_finish_blocking(dma_channel);

  // Acabou a leitura, desliga o ADC de novo.
  adc_run(false);
}

/**
 * Calcula a potência média das leituras do ADC. (Valor RMS)
 */
float mic_power()
{
  float avg = 0.f;

  for (uint i = 0; i < SAMPLES; ++i)
    avg += adc_buffer[i] * adc_buffer[i];

  avg /= SAMPLES;
  return sqrt(avg);
}

/**
 * Calcula a intensidade do volume registrado no microfone, de 0 a 4, usando a tensão.
 */
uint8_t get_intensity(float v)
{
  uint count = 0;

  while ((v -= ADC_STEP / 20) > 0.f)
    ++count;

  return count;
}
