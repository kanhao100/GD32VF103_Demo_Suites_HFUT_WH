/*********************************************************************************************************************
					接线定义：
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
#include "GD32_MT9V032.h"

u8 image[ROW][COL];      //内部使用


#define MT9V032_COF_UART    USART2


__align(4) u8   image[ROW][COL];      //图像数组
u8   receive[3];
u8   receive_num = 0;
u8   uart_receive_flag = 1;

//需要配置到摄像头的数据
s16 MT9V032_CFG[CONFIG_FINISH][2]=
{
    {AUTO_EXP,          0},   //自动曝光设置      范围1-63 0为关闭 如果自动曝光开启  EXP_TIME命令设置的数据将会变为最大曝光时间，也就是自动曝光时间的上限
                              //一般情况是不需要开启这个功能，因为比赛场地光线一般都比较均匀，如果遇到光线非常不均匀的情况可以尝试设置该值，增加图像稳定性
    {EXP_TIME,          500}, //曝光时间          摄像头收到后会自动计算出最大曝光时间，如果设置过大则设置为计算出来的最大曝光值
    {FPS,               50},  //图像帧率          摄像头收到后会自动计算出最大FPS，如果过大则设置为计算出来的最大FPS
    {SET_COL,           COL}, //图像列数量        范围1-752     K60采集不允许超过188
    {SET_ROW,           ROW}, //图像行数量        范围1-480
    {LR_OFFSET,         0},   //图像左右偏移量    正值 右偏移   负值 左偏移  列为188 376 752时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
    {UD_OFFSET,         0},   //图像上下偏移量    正值 上偏移   负值 下偏移  行为120 240 480时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
    {GAIN,              32},  //图像增益          范围16-64     增益可以在曝光时间固定的情况下改变图像亮暗程度

    
    {INIT,              0}    //摄像头开始初始化
};

//从摄像头内部获取到的配置数据
s16 GET_CFG[CONFIG_FINISH-1][2]=
{
    {AUTO_EXP,          0},   //自动曝光设置      
    {EXP_TIME,          0},   //曝光时间          
    {FPS,               0},   //图像帧率          
    {SET_COL,           0},   //图像列数量        
    {SET_ROW,           0},   //图像行数量        
    {LR_OFFSET,         0},   //图像左右偏移量    
    {UD_OFFSET,         0},   //图像上下偏移量    
    {GAIN,              0},   //图像增益          
};


//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V032摄像头串口中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在ISR文件 串口3中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
void mt9v032_cof_uart_interrupt(void)
{
    receive[receive_num] = USART_ReceiveData(MT9V032_COF_UART);
    receive_num++;
    
    if(1==receive_num && 0XA5!=receive[0])  receive_num = 0;
    if(3 == receive_num)
    {
        receive_num = 0;
        uart_receive_flag = 1;
    }
        
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取摄像头内部配置信息
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				调用该函数前请先初始化uart2
//-------------------------------------------------------------------------------------------------------------------
void get_config(void)
{
	u16 temp, i;
    u8  send_buffer[4];
    
    for(i=0; i<CONFIG_FINISH-1; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = GET_STATUS;
        temp = GET_CFG[i][0];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (u8)temp;
        
        uart_putbuff(MT9V032_COF_UART,send_buffer,4);
        
        //等待接受回传数据
        while(!uart_receive_flag);
        uart_receive_flag = 0;
        
        GET_CFG[i][1] = receive[1]<<8 | receive[2];
        
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取摄像头固件版本
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				调用该函数前请先初始化uart2
//-------------------------------------------------------------------------------------------------------------------
u16 get_version(void)
{
    u16 temp;
    u8  send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = GET_STATUS;
    temp = GET_VERSION;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (u8)temp;
    
    uart_putbuff(MT9V032_COF_UART,send_buffer,4);
        
    //等待接受回传数据
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    return ((u16)(receive[1]<<8) | receive[2]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      单独设置摄像头曝光时间
//  @param      light   设置曝光时间越大图像越亮，摄像头收到后会根据分辨率及FPS计算最大曝光时间如果设置的数据过大，那么摄像头将会设置这个最大值
//  @return     u16  当前曝光值，用于确认是否正确写入
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
u16 set_exposure_time(u16 light)
{
	u16 temp;
    u8  send_buffer[4];

    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_EXP_TIME;
    temp = light;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (u8)temp;
    
    uart_putbuff(MT9V032_COF_UART,send_buffer,4);
    
    //等待接受回传数据
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    temp = receive[1]<<8 | receive[2];
    return temp;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      对摄像头内部寄存器进行写操作
//  @param      addr    摄像头内部寄存器地址
//  @param      data    需要写入的数据
//  @return     u16  寄存器当前数据，用于确认是否写入成功
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
u16 set_mt9v032_reg(u8 addr, u16 data)
{
	u16 temp;
    u8  send_buffer[4];
    
    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_ADDR;
    temp = addr;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (u8)temp;
    
    uart_putbuff(MT9V032_COF_UART,send_buffer,4);
    delay_ms(10);
    
    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_DATA;
    temp = data;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (u8)temp;
    
    uart_putbuff(MT9V032_COF_UART,send_buffer,4);
    
    //等待接受回传数据
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    temp = receive[1]<<8 | receive[2];
    return temp;

}

void mt9v032_init(void)
{
    //设置参数    具体请参看使用手册
    u16 temp, i;
    u8  send_buffer[4];
    
    usart2_init(2,9600);		//初始化串口2波特率为9600
    
    delay_ms(1000);
    uart_receive_flag = 0;
    
    //开始配置摄像头并重新初始化
    for(i=0; i<CONFIG_FINISH; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = MT9V032_CFG[i][0];
        temp = MT9V032_CFG[i][1];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (u8)temp;
        
        uart_putbuff(MT9V032_COF_UART,send_buffer,4);
        delay_ms(2);
    }
    
    //等待摄像头初始化成功
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    while((0xff != receive[1]) || (0xff != receive[2]));
    //以上部分对摄像头配置的数据全部都会保存在摄像头上51单片机的eeprom中
    //利用set_exposure_time函数单独配置的曝光数据不存储在eeprom中
    
    //获取配置便于查看配置是否正确
    get_config();
    
    //初始化dcmi接口
    dcmi_init();
    //初始化dcmi的dma通道
    dcmi_dma_init((u32)image,COL*ROW/2/4,DMA_MemoryDataSize_Byte,DMA_MemoryInc_Enable);//DCMI DMA配置
    
    
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      总钻风摄像头图像发送至上位机查看图像
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:				调用该函数前请先初始化uart1
//-------------------------------------------------------------------------------------------------------------------
void gd32_sendimg_032(void)
{
	uint8_t send_buffer[4] = {0x00,0xff,0x01,0x01};
    uint8_t i;
    //如果图像数组过大，将分包发送。
    //以65535字节为单位将其分割。
    uint8_t pack_num = ROW*COL >> 16;       //分割pack_num个包
    uint16_t pack_tail = ROW*COL & 0xFFFF;  //尾包数据量
	
	
	
	//发送协议头
	uart_putbuff(USART1,send_buffer,4); 

    //先发送pack_num * 65535字节数
    for(i=0; i<pack_num; i++)
    {
		uart_putbuff(USART1,(uint8_t *)image + i*0xFFFF,0xFFFF); 
    }
    //然后发送尾包。
	uart_putbuff(USART1,(uint8_t *)image + ROW*COL - pack_tail,pack_tail); 

}


