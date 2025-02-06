#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

// Buffer estático para a Idle Task
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

// Buffer estático para a Timer Task
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

/**
 * @brief Fornece memória estática para a Tarefa Idle do FreeRTOS.
 *
 * Essa função é chamada automaticamente pelo FreeRTOS ao iniciar.
 * Se `configUSE_STATIC_ALLOCATION` for `1`, esta função **deve** ser implementada.
 *
 * @param[out] ppxIdleTaskTCBBuffer       Ponteiro para armazenar o bloco de controle da tarefa Idle.
 * @param[out] ppxIdleTaskStackBuffer     Ponteiro para armazenar o buffer da pilha da tarefa Idle.
 * @param[out] pulIdleTaskStackSize       Tamanho da pilha em palavras (32 bits).
 */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;     // Define o TCB da Idle Task
    *ppxIdleTaskStackBuffer = uxIdleTaskStack; // Define a pilha da Idle Task
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE; // Define o tamanho da pilha
}

/**
 * @brief Fornece memória estática para a Tarefa do Timer do FreeRTOS.
 *
 * Essa função é chamada automaticamente se `configUSE_STATIC_ALLOCATION` for `1`
 * e `configUSE_TIMERS` também for `1`.
 *
 * @param[out] ppxTimerTaskTCBBuffer      Ponteiro para armazenar o bloco de controle da Timer Task.
 * @param[out] ppxTimerTaskStackBuffer    Ponteiro para armazenar o buffer da pilha da Timer Task.
 * @param[out] pulTimerTaskStackSize      Tamanho da pilha em palavras (32 bits).
 */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize) {
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;     // Define o TCB da Timer Task
    *ppxTimerTaskStackBuffer = uxTimerTaskStack; // Define a pilha da Timer Task
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH; // Define o tamanho da pilha
}

/**
 * @brief Manipula estouro de pilha (Stack Overflow).
 *
 * Se `configCHECK_FOR_STACK_OVERFLOW` estiver ativado (`1` ou `2`),
 * essa função será chamada sempre que uma tarefa estourar a pilha.
 *
 * @param[in] xTask     Handle da tarefa que sofreu overflow.
 * @param[in] pcTaskName Nome da tarefa que sofreu overflow.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    (void)xTask;  // Evita warnings de variável não usada
    (void)pcTaskName;

    // Aqui você pode tratar o erro, como reiniciar o sistema ou logar a falha
    while (1);  // Loop infinito para depuração (pode ser substituído por um reset)
}
