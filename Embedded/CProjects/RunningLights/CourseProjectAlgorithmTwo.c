#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "CourseProjectAlgorithmTwo.h"


void Init(void) {
    button_pushed = false;
    activated_leds = 0;
    inactivated_leds = NUMBER_OF_LEDS;
    activated_leds_sum = 0;
    half_current_leds_sum = 0;
    activated_leds_old_sum = 0;
    carrying_leds = NUMBER_OF_LEDS-1;
    return;
}

void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
    return;
}

void select_number_aleds(void) {
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
    activated_leds_old_sum = activated_leds_sum;
    while(button_pushed != true) {
        printf("running LEDs\n");
        printf("Activated LEDs sum: %d\n", activated_leds_sum);
        first_bit_value = activated_leds_sum & 0x01;
        printf("First bit value: %d\n", first_bit_value);
        printf("---------------------------------------\n");
        delay(2000); // сложени са 2 секунди за да се види, как се променя сумата на светодиодите
        if(first_bit_value == 0) {
            activated_leds_sum /= 2;
            carrying_leds = NUMBER_OF_LEDS-1;
            activated_leds_old_sum = activated_leds_sum;
        } else {
            if(half_current_leds_sum == 0) {
                carrying_leds = NUMBER_OF_LEDS-1;
                activated_leds_old_sum = activated_leds_sum;
            }
            half_current_leds_sum = activated_leds_old_sum/2;
            activated_leds_sum += pow(2,carrying_leds) - (activated_leds_old_sum-half_current_leds_sum);
            carrying_leds--;
            activated_leds_old_sum = half_current_leds_sum;
            printf("Half current LEDs sum: %d\n", half_current_leds_sum);
        }
    }
    return;
}

int main() {

    Init();

    button_pushed = true;

    while(true) {
        select_number_aleds();
        running_aleds();
    }

    return 0;
}
