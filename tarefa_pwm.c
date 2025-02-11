#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definições de constantes
#define PINO_SERVO 22                           // Pino PWM para o servomotor
#define PINO_LED 12                             // Pino PWM para o LED RGB
#define FREQUENCIA_PWM 50                       // Frequência de 50Hz (comum para servomotores)
#define PERIODO_PWM (1000000 / FREQUENCIA_PWM)  // Período em microssegundos (20ms para 50Hz)
#define PASSO_PWM 5                             // Incremento de 5µs para movimentação suave do servo
#define ATRASO_MOVIMENTO 10                     // Atraso de 10ms para suavizar o movimento do servo

// Protótipos das funções
void configurar_pwm_no_pino(uint pino);
void mover_servo_gradualmente(uint pino_servo, uint pino_led, uint inicio, uint fim, int passo);
void posicionar_servo(uint pino, uint largura_pulso);
void mover_servo_e_ajustar_led(uint pino_servo, uint pino_led, uint posicao_servo, uint brilho_led, uint tempo_inicio);
void ajustar_brilho_do_led(uint pino, uint brilho);

// Função para configurar o PWM no pino especificado
void configurar_pwm_no_pino(uint pino) {
    gpio_set_function(pino, GPIO_FUNC_PWM);         // Configura o pino para função PWM
    uint canal = pwm_gpio_to_slice_num(pino);       // Obtém o canal PWM associado ao pino
    pwm_config config = pwm_get_default_config();   // Obtém a configuração padrão do PWM
    pwm_config_set_wrap(&config, PERIODO_PWM);      // Define o período do PWM
    pwm_config_set_clkdiv(&config, 125.0f);         // Define o divisor de clock para 125 (ajusta a frequência)
    pwm_init(canal, &config, true);                 // Inicializa o PWM no canal especificado
    pwm_set_enabled(canal, true);                   // Habilita o PWM no canal
}

// Função para mover o servo suavemente entre dois pontos
void mover_servo_gradualmente(uint pino_servo, uint pino_led, uint inicio, uint fim, int passo) {
    // Verifica a direção do movimento
    if (inicio < fim) {
        // Movimento crescente (0° a 180°)
        for (uint pulso = inicio; pulso <= fim; pulso += passo) {
            posicionar_servo(pino_servo, pulso); // Move o servo
            ajustar_brilho_do_led(pino_led, pulso); // Ajusta o brilho do LED
            sleep_ms(ATRASO_MOVIMENTO);
        }
    } else {
        // Movimento decrescente (180° a 0°)
        for (uint pulso = inicio; pulso >= fim; pulso -= passo) {
            posicionar_servo(pino_servo, pulso); // Move o servo
            ajustar_brilho_do_led(pino_led, pulso); // Ajusta o brilho do LED
            sleep_ms(ATRASO_MOVIMENTO);
        }
    }
}

// Função para posicionar o servo em um ângulo específico
void posicionar_servo(uint pino, uint largura_pulso) {
    pwm_set_gpio_level(pino, largura_pulso); // Define o nível do PWM no pino (largura do pulso em µs)
}

// Função para mover o servo e ajustar o LED em uma posição específica
void mover_servo_e_ajustar_led(uint pino_servo, uint pino_led, uint posicao_servo, uint brilho_led, uint tempo_inicio) {
    posicionar_servo(pino_servo, posicao_servo); // Posiciona o servo
    ajustar_brilho_do_led(pino_led, brilho_led); // Ajusta o brilho do LED
    uint angulo = 0;

    switch (posicao_servo)
    {
    case 500:
        angulo = 0;
        break;
    case 1470:
        angulo = 90;
        break;
    case 2400:
        angulo = 180;
        break;
    default:
        break;
    }

    printf("Servo movido para %d°. Tempo decorrido: %d ms\n", angulo, to_ms_since_boot(get_absolute_time()) - tempo_inicio);

    sleep_ms(5000); // Aguarda 5 segundos antes de prosseguir
}

// Função para ajustar o brilho do LED
void ajustar_brilho_do_led(uint pino, uint brilho) {
    pwm_set_gpio_level(pino, brilho); // Define o nível do PWM no pino do LED (ajusta o brilho)
}

// Função principal
int main() {
    stdio_init_all(); // Inicializa todas as funcionalidades de I/O
    configurar_pwm_no_pino(PINO_SERVO); // Configura o PWM para o pino do servo
    configurar_pwm_no_pino(PINO_LED); // Configura o PWM para o pino do LED

    uint tempo_inicio = to_ms_since_boot(get_absolute_time()); // Obtém o tempo inicial em milissegundos

    // Movimentos pré-definidos do servo e ajustes do LED
    mover_servo_e_ajustar_led(PINO_SERVO, PINO_LED, 2400, 2400, tempo_inicio); // Move o servo para 180° 
    mover_servo_e_ajustar_led(PINO_SERVO, PINO_LED, 1470, 1470, tempo_inicio); // Move o servo para 90° 
    mover_servo_e_ajustar_led(PINO_SERVO, PINO_LED, 500, 500, tempo_inicio);   // Move o servo para 0° 

    // Movimento suave entre 0° e 180° com incremento de 5µs a cada 10ms
    while (true) {
        mover_servo_gradualmente(PINO_SERVO, PINO_LED, 500, 2400, PASSO_PWM); // Move o servo de 0° a 180°
        printf("Servo movido para 180°. Tempo decorrido: %d ms\n", to_ms_since_boot(get_absolute_time()) - tempo_inicio);

        mover_servo_gradualmente(PINO_SERVO, PINO_LED, 2400, 500, PASSO_PWM); // Move o servo de 180° a 0°
        printf("Servo movido para 0°. Tempo decorrido: %d ms\n", to_ms_since_boot(get_absolute_time()) - tempo_inicio);
    }

    return 0; 
}