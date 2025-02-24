#ifndef task_adc_with_dma_h
#define task_adc_with_dma_h

#include "stdint.h"

// Parâmetros e macros do ADC.
#define MIC_CHANNEL 2
#define MIC_PIN (26 + MIC_CHANNEL)

#define SAMPLE_RATE 8000  // Taxa de amostragem em Hz
#define ADC_CLOCK_DIV 48000000 / SAMPLE_RATE
#define SAMPLES 256 // Número de amostras que serão feitas do ADC. deve ser potência de 2
#define ADC_ADJUST(x) (x * 3.3f / (1 << 12u) - 1.65f) // Ajuste do valor do ADC para Volts.
#define ADC_MAX 3.3f
#define ADC_STEP (3.3f / 5.f) // Intervalos de volume do microfone.


void task_adc_with_dma(void *pvParameters);

#endif