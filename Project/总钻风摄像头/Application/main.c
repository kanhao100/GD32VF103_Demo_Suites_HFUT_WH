/*********************************************************************************************************************
					���������ͷ���߶��壺
					------------------------------------ 
					ģ��ܽ�            ��Ƭ���ܽ�
					SDA                A2
					SCL                A3
					���ж�              B7
					���ж�              A4   
					�����ж�            A6       
					
					D0                 C6
					D1                 C7
					D2                 C8
					D3                 C9
					D4                 C11
					D5                 B6
					D6                 E5
					D7                 E6
                        
					------------------------------------ 
                    USBתTTL���߶���         
					USBתTTL����        ��Ƭ������
					TX                  A10
					RX                  A9
					
					Ĭ�Ϸֱ���              �鿴SEEKFREE_MT9V032.h �ļ��ڵĺ궨�� COL ROW
					Ĭ��FPS                 50֡
 ********************************************************************************************************************/
#include "headfile.h"
#include "gd32vf103.h"
#include "gd32vf103v_eval.h"
#include "gd32vf103v_lcd_eval.h"
#include "systick.h"
#include <stdio.h>

int main(void)
{ 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	delay_init(168);                                //��ʼ����ʱ����
	uart_init(115200);		                        //��ʼ�����ڲ�����Ϊ115200,���ڷ���ͼ�����λ��
    mt9v032_init();

 	while(1)
	{	
        if(finish_flag_032) 
        {
            finish_flag_032 = 0;
            seekfree_sendimg_032();

        }
    }
}
