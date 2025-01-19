#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 21 //Porta associada ao Buzzer

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

int main() {
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);

    //Para integrar ao teclado matricial, ajustar essa parte chamando a função buzz e configurando a frequência e duração
    while (true) {
        buzz(550, 500); //Frequência de 550Hz por um tempo de 500ms
        sleep_ms(500);
    }

    return 0;
}
