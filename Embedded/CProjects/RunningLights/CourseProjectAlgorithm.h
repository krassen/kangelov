#ifndef __COURSE_PROJECT_ALGORITHM__
#define __COURSE_PROJECT_ALGORITHM__

#define NUMBER_OF_LEDS 8

bool button_pushed;
unsigned char activated_leds;
unsigned char inactivated_leds;
unsigned char activated_leds_sum;
unsigned char first_bit_value;

/*

 * Установява изходите на PORTD. Да не се имплементира.

*/
extern void WritePortD(unsigned char value);

/*

 * Връша стойността на PORTB. Aко съответния бит е 0 на входа

 * нивото е ниско, ако е 1 е високо ниво. Да не се имплементира.

 */
extern unsigned char ReadPortB(void);

/*

 * Инициализира вътрешното състояние на модула.

 */
void Init(void);

/*

 * 10 милисекунден таск на вашия модул

 */
void Task_Update(void);

/*

 * Функцията за изчакване на период от време.

 */
void delay(unsigned int);

/*

 * Функцията за избиране на активните светодиоди(като бройка).

 */
void select_aleds();

/*

 * Функцията за бягане на светодиодите.

 */
void running_aleds();

#endif

