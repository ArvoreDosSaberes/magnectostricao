
#include "lwip/tcp.h"

#define I2C_SDA  14
#define I2C_SCL  15

#define MIC_CHANNEL 2
#define MIC_PIN (26 + MIC_CHANNEL)

// Parâmetros e macros do ADC.
#define ADC_CLOCK_DIV 96.f
#define SAMPLES 200                                   // Número de amostras que serão feitas do ADC.
#define ADC_ADJUST(x) (x * 3.3f / (1 << 12u) - 1.65f) // Ajuste do valor do ADC para Volts.
#define ADC_MAX 3.3f
#define ADC_STEP (3.3f / 5.f) // Intervalos de volume do microfone.

// Pino e número de LEDs da matriz de LEDs.
#define LED_PIN 7
#define LED_COUNT 25

#define BUTTON_A_PIN 5      // Pino do botão A
#define BUTTON_B_PIN 6      // Pino do botão B

#define WIFI_SSID "ArvoreDosSaberes"
#define WIFI_PASSWORD "Arduino2022"

#define abs(x) ((x < 0) ? (-x) : (x))

// Buffer para respostas HTTP
#define HTTP_RESPONSE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" \
                      "<!DOCTYPE html><html><body>" \
                      "<h1>Controle do LED</h1>" \
                      "<p><a href=\"/led/on\">Ligar LED</a></p>" \
                      "<p><a href=\"/led/off\">Desligar LED</a></p>" \
                      "</body></html>\r\n"

void sample_mic();
float mic_power();
uint8_t get_intensity(float v);

static void start_http_server(void);
void create_http_response();
static err_t http_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static err_t connection_callback(void *arg, struct tcp_pcb *newpcb, err_t err);
static void monitor_buttons_callback(unsigned int gpio, long unsigned int events);