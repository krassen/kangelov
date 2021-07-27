#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "CourseProject.h"


void Init(void) {
    button_pushed = false;
    activated_leds = 0;
    inactivated_leds = NUMBER_OF_LEDS;
    activated_leds_sum = 0;
    button_counter = 0;
    select_counter = ONE_SECOND-50;
    running_counter = QUARTER_SECOND;
    reset_aleds = false;
    return;
}

void Task_Update(void) {
    if(button_pushed == true) {
        select_counter -= 10;
        if(select_counter == 0) {
            select_aleds();
            button_pushed = false;
            select_counter = ONE_SECOND-50;
            running_counter = QUARTER_SECOND;
        }
    } else {
        if((ReadPortB() & 0x01) == 1) {
            button_counter++;
            if(button_counter == NUMBER_CCP_BUTTON) {
                if(reset_aleds == true)
                    Init();
                button_pushed = true;
                button_counter = 0;
            }
        } else {
            button_pushed = false;
            button_counter = 0;
        }
        if(button_pushed != true) {
            running_counter -= 10;
            if(running_counter == 0) {
                running_aleds();
                reset_aleds = true;
                running_counter = QUARTER_SECOND-50;
            }
        }
    }
}

void select_aleds(void) {
    if(activated_leds == NUMBER_OF_LEDS) {
        activated_leds_sum = 0;
        inactivated_leds = NUMBER_OF_LEDS;
        activated_leds = 0;
    }
    activated_leds++;
    inactivated_leds--;
    activated_leds_sum += pow(2, inactivated_leds);
    WritePortD(activated_leds_sum);
    return;
}

void running_aleds(void) {
    first_bit_value = activated_leds_sum & 0x01;
    if(first_bit_value == 0)
        activated_leds_sum /= 2;
    else {
        activated_leds_sum >>= 1;
        activated_leds_sum += pow(2,NUMBER_OF_LEDS-1);
    }
    WritePortD(activated_leds_sum);
    return;
}

int main() {
    Init();

    // Task_Update сама се извиква на 10 милисекунди

    return 0;
}
