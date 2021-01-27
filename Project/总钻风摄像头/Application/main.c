/*********************************************************************************************************************
					总钻风摄像头接线定义：
					------------------------------------ 
					模块管脚            单片机管脚
					SDA                A2
					SCL                A3
					场中断              B7
					行中断              A4   
					像素中断            A6       
					
					D0                 C6
					D1                 C7
					D2                 C8
					D3                 C9
					D4                 C11
					D5                 B6
					D6                 E5
					D7                 E6
                        
					------------------------------------ 
                    USB转TTL接线定义         
					USB转TTL引脚        单片机引脚
					TX                  A10
					RX                  A9
					
					默认分辨率              查看SEEKFREE_MT9V032.h 文件内的宏定义 COL ROW
					默认FPS                 50帧
 ********************************************************************************************************************/
#include "headfile.h"
#include "gd32vf103.h"
#include "gd32vf103v_eval.h"
#include "gd32vf103v_lcd_eval.h"
#include "systick.h"
#include <stdio.h>

int main(void)
{ 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
	delay_init(168);                                //初始化延时函数
	uart_init(115200);		                        //初始化串口波特率为115200,用于发送图像给上位机
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
