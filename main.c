#include <reg52.h>
#include "motor.h"

int flag = 0;

char Rec[];
//���ڳ�ʼ������
void UART_Init(void)
{
	SCON  = 0x40;//���ڷ�ʽһ
	PCON  = 0;//SOMD = 0
	REN  = 1;//�������
	TMOD = 0x20;//��ʱ��1��ʽ2
	TH1 = 0xfd;					//������9600������λ8��ֹͣλ1
  TL1 = 0xfd;
	TR1  = 1;//������ʱ��1
	ES  = 1;//��UART�ж�
	EA  = 1;//�����ж�
}

void main(void)
{
	UART_Init();
	P0 = 0;//���θ���
	while(1)
	{
		if(RI)
		{
			switch(Rec[])
		{
			case "00"://ǰ��
				Left_moto_go;
				Right_moto_go;
			break;
			case "01"://����
				Left_moto_back;
				Right_moto_back;
			break;
			case ""://��ת
				Left_moto_go;
				Right_moto_back;
			break;
			case ""://��ת
				Left_moto_back;
				Right_moto_go;
			break;
			default:
				break;
			
		}
		}
		
	}
}

//���ڷ����ж��ӳ����
void Uart_Timer1(void) interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
		if(flag < 2)
		{
			Rec[flag] = SBUF;
			flag++;
		}
		else
		{
			flag = 0;
		}
	}
}