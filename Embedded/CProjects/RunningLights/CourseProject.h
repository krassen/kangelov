#ifndef __COURSE_PROJECT__
#define __COURSE_PROJECT__

#define NUMBER_OF_LEDS 8
#define NUMBER_CCP_BUTTON 5 // Number of consecutive checks for pressed button
                            // Брой последователни проверки, за това дали бутона е натиснат
#define ONE_SECOND 1000
#define QUARTER_SECOND 250


bool button_pushed;
unsigned char activated_leds;
unsigned char inactivated_leds;
unsigned char activated_leds_sum;
unsigned char first_bit_value;
unsigned char button_counter; // Трябва ни, за да знаем дали бутона е натиснат в продължение на 50ms
unsigned int select_counter; // Трябва ни, за да направим изчакване от една секунда в процеса на избиране на светодиод
unsigned int running_counter; // Трябва ни, за да направим изчакване от четвърт секунда в процеса на "бягането" на светодиодите
bool reset_aleds; // Трябва ни, за да направим установяване в първоначално състояние на всички променливи, ако бутона бъде натиснат отново, след поне едно извикване на функцията running_aleds();

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

 * Функцията за избиране на активните светодиоди.

 */
void select_aleds();

/*

 * Функцията за бягане на светодиодите.

 */
void running_aleds();

#endif

