#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "CourseProjectAlgorithm.h"


void Init(void) {
    button_pushed = false;
    activated_leds = 0;
    inactivated_leds = NUMBER_OF_LEDS;
    activated_leds_sum = 0;
    return;
}

void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
    return;
}

void select_aleds(void) {
    unsigned char input_number;
    while(button_pushed == true) {
            delay(1000);
            if(activated_leds == NUMBER_OF_LEDS) {
                activated_leds_sum = 0;
                inactivated_leds = NUMBER_OF_LEDS;
                activated_leds = 0;
            }
            activated_leds++;
            inactivated_leds--;
            activated_leds_sum += pow(2, inactivated_leds);
            printf("Activated LEDs: %d\n", activated_leds);
            printf("Activated LEDs sum: %d\n", activated_leds_sum);
            printf("Button condition: %d\n", button_pushed);
            printf("Enter -> 1 or 0\n");
            scanf("%d", &input_number);
            button_pushed = input_number;
            printf("---------------------------------------\n");
    }
    return;
}

void running_aleds(void) {
    while(button_pushed != true) {
        printf("running LEDs\n");
        printf("Activated LEDs sum: %d\n", activated_leds_sum);
        first_bit_value = activated_leds_sum & 0x01;
        printf("First bit value: %d\n", first_bit_value);
        printf("---------------------------------------\n");
        delay(2000); // сложени са 2 секунди за да се види, как се променя сумата на светодиодите
        if(first_bit_value == 0)
            activated_leds_sum /= 2;
        else {
            activated_leds_sum >>= 1;
            activated_leds_sum += pow(2,NUMBER_OF_LEDS-1);
        }
    }
    return;
}

int main() {

    Init();

    button_pushed = true;

    while(true) {
        select_aleds();
        running_aleds();
    }

    return 0;
}
