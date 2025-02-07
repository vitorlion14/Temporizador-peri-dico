
JOÃO VITOR S. AMORIM

# Código de Semáforo em C

Este projeto implementa um semáforo simples utilizando uma placa baseada em RP2040 (por exemplo, Raspberry Pi Pico). O código controla três LEDs (vermelho, amarelo e verde) representando os estados de um semáforo de trânsito.

## Funcionalidades

- Controla três LEDs correspondentes aos estados do semáforo: Vermelho, Amarelo e Verde.
- Os LEDs mudam de estado a cada 3 segundos.
- Imprime uma mensagem no console a cada segundo indicando que o semáforo está em funcionamento.

## Configuração do Hardware

- LED Vermelho conectado ao pino GPIO 11.
- LED Amarelo conectado ao pino GPIO 12.
- LED Verde conectado ao pino GPIO 13.

## Detalhes do Código

O código está dividido em algumas partes principais:

1. **Definições dos pinos dos LEDs:**
    ```c
    #define LED_R_PIN 11    
    #define LED_Y_PIN 12
    #define LED_G_PIN 13
    ```

2. **Definição dos estados dos LEDs:**
    ```c
    typedef enum { RED, YELLOW, GREEN } traffic_light_state_t;
    traffic_light_state_t current_state = RED;
    ```

3. **Função de callback do temporizador repetitivo:**
    Esta função é chamada a cada 3 segundos e alterna os estados dos LEDs.
    ```c
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
    ```

4. **Função principal:**
    Inicializa os pinos dos LEDs, configura o temporizador repetitivo e imprime uma mensagem no console a cada segundo.
    ```c
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
    ```

## Como Compilar e Executar

1. Configure seu ambiente de desenvolvimento para a placa RP2040.
2. Compile o código utilizando um compilador compatível, como o GCC.
3. Carregue o binário na placa RP2040.
4. Conecte os LEDs aos pinos especificados.
5. Execute o código na placa e observe o funcionamento do semáforo.




