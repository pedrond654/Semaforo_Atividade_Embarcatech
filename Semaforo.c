#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define LED_RED 13
#define LED_BLUE  12
#define LED_GREEN 11

//Define a cor do semáforo
uint estado = 0;

// Callback do temporizador periódico
bool semaforo_callback(struct repeating_timer *t) {

    // Desliga todos os LEDs antes de ligar o próximo
    gpio_put(LED_RED, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_GREEN, 0);

    switch (estado)
    {
    case 0:
        gpio_put(LED_RED, 1);
        printf("Sinal Vermelho\n");
        break;
    
   case 1:
        gpio_put(LED_RED,"1");
        gpio_put(LED_GREEN,"1");
        printf("Sinal Amarelo\n");
        break;
    case 2:
        gpio_put(LED_GREEN,"1");
        printf("Sinal Verde\n");

    }

    estado = (estado + 1) % 3;

    return true; // Mantém o temporizador rodando
}

int main() {

    stdio_init_all();

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Declaração do temporizador
    struct repeating_timer timer;

    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);
    
    while (true) {
        printf("Semáforo em funcionamento\n");
        sleep_ms(1000);
    }

    return 0;
}
