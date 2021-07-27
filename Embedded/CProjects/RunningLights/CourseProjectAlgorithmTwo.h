#ifndef __COURSE_PROJECT_ALGORITHM_TWO__
#define __COURSE_PROJECT_ALGORITHM_TWO__

#define NUMBER_OF_LEDS 8

bool button_pushed;
unsigned char activated_leds;
unsigned char inactivated_leds;
unsigned char activated_leds_sum;
unsigned char first_bit_value;
unsigned char half_current_leds_sum;
unsigned char activated_leds_old_sum;
unsigned char carrying_leds;

/*

 * ���������� �������� �� PORTD. �� �� �� ������������.

*/
extern void WritePortD(unsigned char value);

/*

 * ����� ���������� �� PORTB. A�� ���������� ��� � 0 �� �����

 * ������ � �����, ��� � 1 � ������ ����. �� �� �� ������������.

 */
extern unsigned char ReadPortB(void);

/*

 * ������������ ���������� ��������� �� ������.

 */
void Init(void);

/*

 * 10 ������������ ���� �� ����� �����

 */
void Task_Update(void);

/*

 * ��������� �� ��������� �� ������ �� �����.

 */
void delay(unsigned int);

/*

 * ��������� �� �������� �� ��������� ����������(���� ������).

 */
void select_number_aleds();

/*

 * ��������� �� ������ �� ������������.

 */
void running_aleds();

#endif

