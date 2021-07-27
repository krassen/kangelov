#ifndef __COURSE_PROJECT__
#define __COURSE_PROJECT__

#define NUMBER_OF_LEDS 8
#define NUMBER_CCP_BUTTON 5 // Number of consecutive checks for pressed button
                            // ���� �������������� ��������, �� ���� ���� ������ � ��������
#define ONE_SECOND 1000
#define QUARTER_SECOND 250


bool button_pushed;
unsigned char activated_leds;
unsigned char inactivated_leds;
unsigned char activated_leds_sum;
unsigned char first_bit_value;
unsigned char button_counter; // ������ ��, �� �� ����� ���� ������ � �������� � ����������� �� 50ms
unsigned int select_counter; // ������ ��, �� �� �������� ��������� �� ���� ������� � ������� �� �������� �� ���������
unsigned int running_counter; // ������ ��, �� �� �������� ��������� �� ������� ������� � ������� �� "��������" �� ������������
bool reset_aleds; // ������ ��, �� �� �������� ������������ � ������������ ��������� �� ������ ����������, ��� ������ ���� �������� ������, ���� ���� ���� ��������� �� ��������� running_aleds();

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

 * ��������� �� �������� �� ��������� ����������.

 */
void select_aleds();

/*

 * ��������� �� ������ �� ������������.

 */
void running_aleds();

#endif

