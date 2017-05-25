#include <reg52.h>

sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit IN3 = P1^2;
sbit IN4 = P1^3;
sbit INA = P1^4;//��ʹ�ܶ�
sbit INB = P1^5;

//ǰ������
void go(void)
{
	INA = 1;
	INB = 1;
	
	IN1 = 1;
	IN2 = 0;
	IN3 = 1;
	IN4 = 0;
}

//���˺���
void back(void)
{
	INA = 1;
	INB = 1;
	
	IN1 = 0;
	IN2 = 1;
	IN3 = 0;
	IN4 = 1;
	
}

//��ת
void left(void)
{
	INA = 1;
	INB = 1;
	
	IN1 = 0;
	IN2 = 1;
	IN3 = 1;
	IN4 = 0;
}
//��ת
void right(void)
{
	INA = 1;
	INB = 1;
	
	IN1 = 1;
	IN2 = 0;
	IN3 = 0;
	IN4 = 1;
}