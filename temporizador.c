#include "pico/stdlib.h"

#define LED_R_PIN 11    
#define LED_Y_PIN 12
#define LED_G_PIN 13

// Estados dos LEDs
typedef enum { RED, YELLOW, GREEN } traffic_light_state_t;
traffic_light_state_t current_state = RED;

bool repeating_timer_callback(struct repeating_timer *t) {
    switch (current_state) {
        case RED:
            gpio_put(LED_R_PIN, 1);
            gpio_put(LED_Y_PIN, 0);
            gpio_put(LED_G_PIN, 0);
            current_state = YELLOW;
            break;
        case YELLOW:
            gpio_put(LED_R_PIN, 0);
            gpio_put(LED_Y_PIN, 1);
            gpio_put(LED_G_PIN, 0);
            current_state = GREEN;
            break;
        case GREEN:
            gpio_put(LED_R_PIN, 0);
            gpio_put(LED_Y_PIN, 0);
            gpio_put(LED_G_PIN, 1);
            current_state = RED;
            break;
    }
    return true; // continuar repetindo
}

int main() {
    // Inicializa os pinos dos LEDs
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_Y_PIN);
    gpio_set_dir(LED_Y_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);

    // Configura o temporizador repetitivo
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {
        // Imprime uma mensagem a cada segundo
        printf("Semáforo está em funcionamento.\n");
        sleep_ms(1000);
    }

    return 0;
}
