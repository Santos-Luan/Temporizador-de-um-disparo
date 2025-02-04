#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Declarações
#define LED_PIN_B 11
#define LED_PIN_R 12
#define LED_PIN_G 13
#define btn 5

#define DEBOUNCE_TIME_MS 20 // Tempo de debounce
#define DELAY_LED_MS 3000   // Atraso entre LEDs

bool leds_ativos = false; // Flag para controlar se os LEDs estão ativos

// Funções
void Inicializacoes();

// Funções de callback para desligar os LEDs em sequência
int64_t turn_off_blue(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_B, false);
    return 0; // Não repetir o alarme
}

int64_t turn_off_red(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_R, false);
    return 0;
}

int64_t turn_off_green(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_G, false);
    leds_ativos = false; // Libera o botão após todos os LEDs serem desligados
    return 0;
}

// Função de debounce usando controle por tempo sem bloqueio
bool botao_pressionado_com_debounce() {
    static absolute_time_t ultimo_tempo = {0};
    if (!gpio_get(btn)) { // Botão pressionado (ativo em LOW)
        absolute_time_t agora = get_absolute_time();
        if (absolute_time_diff_us(ultimo_tempo, agora) > DEBOUNCE_TIME_MS * 1000) {
            ultimo_tempo = agora;
            return true;
        }
    }
    return false;
}

int main() {
    Inicializacoes();

    while (true) {
        // Verifica se o botão foi pressionado, com debounce, e se os LEDs estão inativos
        if (botao_pressionado_com_debounce() && !leds_ativos) {
            leds_ativos = true; // Impede novas ativações até o ciclo completo

            gpio_put(LED_PIN_B, true);
            gpio_put(LED_PIN_R, true);
            gpio_put(LED_PIN_G, true);

            // Agendar o desligamento dos LEDs em sequência com 3 segundos de intervalo
            add_alarm_in_ms(DELAY_LED_MS, turn_off_blue, NULL, false);             // Azul apaga após 3 segundos
            add_alarm_in_ms(DELAY_LED_MS * 2, turn_off_red, NULL, false);          // Vermelho apaga após 6 segundos
            add_alarm_in_ms(DELAY_LED_MS * 3, turn_off_green, NULL, false);        // Verde apaga após 9 segundos

            printf("Botão pressionado!\n");
        }
    }
}

void Inicializacoes() {
    // Inicializa a comunicação serial, permitindo o uso de funções como printf.
    stdio_init_all();

    // Inicializar os pinos 11, 12 e 13 e definir como saída
    gpio_init(LED_PIN_B);
    gpio_set_dir(LED_PIN_B, GPIO_OUT);
    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);
    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G, GPIO_OUT);

    // Inicializa o botão como pino 5
    gpio_init(btn);
    gpio_set_dir(btn, GPIO_IN);
    gpio_pull_up(btn);
}
