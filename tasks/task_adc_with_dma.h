#ifndef task_adc_with_dma_h
#define task_adc_with_dma_h

#include "stdint.h"

// Parâmetros e macros do ADC.
#define MIC_CHANNEL 2
#define MIC_PIN (26 + MIC_CHANNEL)

#define ADC_CLOCK_DIV 96.f
#define SAMPLES 200                                   // Número de amostras que serão feitas do ADC.
#define ADC_ADJUST(x) (x * 3.3f / (1 << 12u) - 1.65f) // Ajuste do valor do ADC para Volts.
#define ADC_MAX 3.3f
#define ADC_STEP (3.3f / 5.f) // Intervalos de volume do microfone.


void task_adc_with_dma(void *pvParameters);

void sample_mic();
float mic_power();
uint8_t get_intensity(float v);

#endif