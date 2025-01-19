#include <stdio.h>
#include "pico/stdlib.h"

#define linhas 4  // Definindo Linhas da Matriz
#define colunas 4 // Definindo colunas da Matriz

// Criação de matriz para ler linha e coluna do programa.

const uint8_t PINOS_DA_LINHA[linhas] = {8, 7, 6, 5};
const uint8_t PINOS_DA_COLUNA[colunas] = {4, 3, 2, 1};

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
        gpio_put(PINOS_DA_LINHA, 0);
    }
    for (int j = 0; j < colunas; j++)
    { // percorre as colunas
        gpio_init(PINOS_DA_COLUNA[j]);
        gpio_set_dir(PINOS_DA_COLUNA[j], GPIO_OUT);
        gpio_put(PINOS_DA_COLUNA[j], 0);
    }
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
                break;
            case '2':
                // LED OFF
                break;
            case '3':
                // LED OFF
                break;
            case 'A':
                // LED VERMELHO ON
                break;

            case '4':
                // LED OFF
                break;
            case '5':
                // LED OFF
                break;
            case '6':
                // LED OFF
                break;
            case 'B':
                // LED AZUL ON
                break;
            case '7':
                // LED OFF
            case '8':
                // LED OFF
                break;
            case '9':
                // LED OFF
                break;
            case 'C':
                // LED VERDE ON
                break;
            case '*':
                // LED OFF
                break;
            case '0':
                // LED OFF
                break;
            case '#':
                // LED OFF
                break;

            case 'D':

                // LED ON VERMELHO,VERDE E AZUL

                break;
            default:
                // LED OFF
                break;
            }
        }
        sleep_ms(100);
    }
    return 0;
}
