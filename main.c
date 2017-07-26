/*
*�������ö�ʱ��2��Ϊ�����ʷ���������ģ��������ݴ�����Ƭ����ͬʱ�ɻش����ݵ�����������ʵ��С���Ŀ��ƹ���
*ͨ��Э�飺1	ǰ�� 1
					 2	���� 2
					 3	��ת 3
					 4	��ת 4
					 ���� ֹͣ stop
*ƽ̨��STC89C52RC
*���ߣ�W_Honor
*���ڣ�2017/7/24
*/
#include <stc89xx.h>
#include "motor.h"

#define FOSC 12000000L      //System frequency
#define BAUD 9600   //���ò�����

bit flag = 0;

bit rec_flag = 0;//���ݽ��ܱ�־λ

unsigned char RecData = 0;

char code str[] = "stop"; 


//���ڳ�ʼ������	`
void UART_Init(void)
{
 //PCON = 0x80;//�����ʼӱ���SOMD = 1
 SCON = 0x50; //SM0 SM1 SM2 REN TB8 RB8 TI RI ���пڹ�����ʽ1��10λ�첽�շ�
 RCAP2H = (65536-(FOSC/32/BAUD)) >> 8;
 RCAP2L = (65536-(FOSC/32/BAUD));
 TH2 = RCAP2H;
 TL2 = RCAP2L;
 T2CON = 0x34; //TF2 EXF2 RCLK TCLK EXEN2 TR2 C/T2 CP/RL2//��ʱ��2���������ʷ�����
 T2MOD = 0;
 ES = 1;
 EA = 1;
	
/*	PCON = 0x80;
    SCON = 0x50;   // 
    TMOD = 0x20;   //T1
    TH1 = 0xF3;    //[
    TL1 = 0xF3;  
    TR1 = 1;                 	
    ES  = 1;       //
    EA  = 1;
	*/
}

//����λ������һ���ֽ�����Ϣ
void senddata(char dat)
{
		if(rec_flag == 1)
		{
			ES=0;//
			SBUF=dat;
			while(!TI);
			TI=0;
			ES=1;//
		}
		rec_flag = 0;
}

//����λ������һ���ַ���
void sendstr(void)
{
	unsigned int i = 0;
	if(flag == 1)
	{
		flag = 0;
		while(str[i] != '\0')
	{
		ES = 0;
		SBUF = str[i];
		while(!TI);
		TI = 0;
		i++;
		ES = 1;
	}
	i = 0;
	}
}

//������
void main(void)
{
	UART_Init();
	P0 = 0;//���θ���
	while(1);
	}

//���ڷ����ж��ӳ����
void Uart_Timer2(void) interrupt 4//�жϽ���һ���ֽ�����,�����жϺΪ4�
{
	unsigned char i = 0;
	if(RI == 1)//���ձ�־λ//��Ӳ�����յ�����ʱ����λ
	{
		RI = 0;//�رս����	
		RecData = SBUF;
		rec_flag = 1;//������һ���ַ���1
		switch(RecData)
		{
			case '1'://ǰ��
			  go();
				senddata('1');
			break;
			case '2'://����
				back();
				senddata('2');
			break;
			case '3'://��ת
				right();
			  senddata('3');
			break;
			case '4'://��ת
				left();
				senddata('4');
			break;
			default:
				stop();
			  flag = 1;
				sendstr();
				break;
		}
	}
	else
	{
		TI = 0;
	}
}