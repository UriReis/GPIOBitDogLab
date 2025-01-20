#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 21 //Porta associada ao Buzzer
#define linhas 4  // Definindo Linhas da Matriz
#define colunas 4 // Definindo colunas da Matriz

// Criação de matriz para ler linha e coluna do programa.
const uint8_t PINOS_DA_LINHA[linhas] = {8, 7, 6, 5};
const uint8_t PINOS_DA_COLUNA[colunas] = {4, 3, 2, 1};

//Definição dos Pinos dos LEDs
const uint LED_G = 11;
const uint LED_B = 12;
const uint LED_R = 13;

const char key_map[linhas][colunas] = { // criação da função para fazer o mapeamento de teclas nas linhas e colunas
    {'1', '2', '3', 'A'},

    {'4', '5', '6', 'B'},

    {'7', '8', '9', 'C'},

    {'*', '0', '#', 'D'}};

    

void keypad_init()
{
    // Implementacao dos LEDS

    for (int i = 0; i < linhas; i++)
    { // percorre as linhas
        gpio_init(PINOS_DA_LINHA[i]);
        gpio_set_dir(PINOS_DA_LINHA[i], GPIO_OUT);
        gpio_put(PINOS_DA_LINHA[i], 0);
    }
    for (int j = 0; j < colunas; j++)
    { // percorre as colunas
        gpio_init(PINOS_DA_COLUNA[j]);
        gpio_set_dir(PINOS_DA_COLUNA[j], GPIO_OUT);
        gpio_put(PINOS_DA_COLUNA[j], 0);
    }
    //Inicialização dos Pino dos LEDs
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
}
char read_keypad()
{
    for (int linha = 0; linha < linhas; linha++)
    {
        gpio_put(PINOS_DA_LINHA[linha], 1);
        for (int coluna = 0; coluna < colunas; coluna++)
        {
            if (gpio_get(PINOS_DA_COLUNA[coluna]))
            {
                gpio_put(PINOS_DA_LINHA[linha], 0);
                return key_map[linha][coluna];
            }
        }
        gpio_put(PINOS_DA_LINHA[linha], 0);
    }
    return '\0';
}

void buzz(uint freq, uint tempo) {

    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint channel = pwm_gpio_to_channel(BUZZER_PIN);

    // Configurando a frequência
    uint32_t clock_freq = 125000000; 
    uint32_t divider = clock_freq / freq / 65536 + 1; 
    uint32_t top = clock_freq / (divider * freq);

    // Configurando as repetições
    pwm_set_clkdiv(slice_num, divider); 
    pwm_set_wrap(slice_num, top - 1);
    pwm_set_chan_level(slice_num, channel, top / 2);
    pwm_set_enabled(slice_num, true);

    sleep_ms(tempo);

    pwm_set_enabled(slice_num, false);
}

int main()
{
    stdio_init_all();
    keypad_init();

    while (true)
    {
        char key = read_keypad();
        if (key != '\0')
        {
            printf("Tecla pressionada: %c\n", key);

            switch (key)
            {
            case '1':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case '2':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case '3':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case 'A':
                // LED VERMELHO ON
                gpio_put(LED_R, 1);
                sleep_ms(1000);
                gpio_put(LED_R, 0);

                break;

            case '4':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case '5':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case '6':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case 'B':
                // LED AZUL ON
                gpio_put(LED_B, 1);
                sleep_ms(1000);
                gpio_put(LED_B, 0);
                break;
            case '7':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
            case '8':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case '9':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case 'C':
                // LED VERDE ON
                gpio_put(LED_G, 1);
                sleep_ms(1000);
                gpio_put(LED_G, 0);
                break;
            case '*':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case '0':
                // LED OFF
                gpio_put(LED_R, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_G, 0);
                break;
            case '#':
                 gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
                 buzz(550, 500); //Frequência de 550Hz por um tempo de 500ms
                 sleep_ms(500);

                // Buzzers
                
                break;

            case 'D':

                // LED ON VERMELHO,VERDE E AZUL
                gpio_put(LED_G, 1);
                gpio_put(LED_B, 1);
                gpio_put(LED_R, 1);
                sleep_ms(1000);
                gpio_put(LED_G, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_R, 0);
                break;
            default:
                // LED OFF
                gpio_put(LED_G, 0);
                gpio_put(LED_B, 0);
                gpio_put(LED_R, 0);
               
                break;
            }
        }
        sleep_ms(100); 
    }
    return 0;
}
