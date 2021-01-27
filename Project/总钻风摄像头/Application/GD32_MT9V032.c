/*********************************************************************************************************************
					���߶��壺
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
#include "GD32_MT9V032.h"

u8 image[ROW][COL];      //�ڲ�ʹ��


#define MT9V032_COF_UART    USART2


__align(4) u8   image[ROW][COL];      //ͼ������
u8   receive[3];
u8   receive_num = 0;
u8   uart_receive_flag = 1;

//��Ҫ���õ�����ͷ������
s16 MT9V032_CFG[CONFIG_FINISH][2]=
{
    {AUTO_EXP,          0},   //�Զ��ع�����      ��Χ1-63 0Ϊ�ر� ����Զ��ع⿪��  EXP_TIME�������õ����ݽ����Ϊ����ع�ʱ�䣬Ҳ�����Զ��ع�ʱ�������
                              //һ������ǲ���Ҫ����������ܣ���Ϊ�������ع���һ�㶼�ȽϾ��ȣ�����������߷ǳ������ȵ�������Գ������ø�ֵ������ͼ���ȶ���
    {EXP_TIME,          500}, //�ع�ʱ��          ����ͷ�յ�����Զ����������ع�ʱ�䣬������ù���������Ϊ�������������ع�ֵ
    {FPS,               50},  //ͼ��֡��          ����ͷ�յ�����Զ���������FPS���������������Ϊ������������FPS
    {SET_COL,           COL}, //ͼ��������        ��Χ1-752     K60�ɼ���������188
    {SET_ROW,           ROW}, //ͼ��������        ��Χ1-480
    {LR_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ188 376 752ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
    {UD_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ120 240 480ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
    {GAIN,              32},  //ͼ������          ��Χ16-64     ����������ع�ʱ��̶�������¸ı�ͼ�������̶�

    
    {INIT,              0}    //����ͷ��ʼ��ʼ��
};

//������ͷ�ڲ���ȡ������������
s16 GET_CFG[CONFIG_FINISH-1][2]=
{
    {AUTO_EXP,          0},   //�Զ��ع�����      
    {EXP_TIME,          0},   //�ع�ʱ��          
    {FPS,               0},   //ͼ��֡��          
    {SET_COL,           0},   //ͼ��������        
    {SET_ROW,           0},   //ͼ��������        
    {LR_OFFSET,         0},   //ͼ������ƫ����    
    {UD_OFFSET,         0},   //ͼ������ƫ����    
    {GAIN,              0},   //ͼ������          
};


//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V032����ͷ�����жϺ���
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       �ú�����ISR�ļ� ����3�жϳ��򱻵���
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
//  @brief      ��ȡ����ͷ�ڲ�������Ϣ
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				���øú���ǰ���ȳ�ʼ��uart2
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
        
        //�ȴ����ܻش�����
        while(!uart_receive_flag);
        uart_receive_flag = 0;
        
        GET_CFG[i][1] = receive[1]<<8 | receive[2];
        
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ͷ�̼��汾
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				���øú���ǰ���ȳ�ʼ��uart2
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
        
    //�ȴ����ܻش�����
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    return ((u16)(receive[1]<<8) | receive[2]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������������ͷ�ع�ʱ��
//  @param      light   �����ع�ʱ��Խ��ͼ��Խ��������ͷ�յ������ݷֱ��ʼ�FPS��������ع�ʱ��������õ����ݹ�����ô����ͷ��������������ֵ
//  @return     u16  ��ǰ�ع�ֵ������ȷ���Ƿ���ȷд��
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
    
    //�ȴ����ܻش�����
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    temp = receive[1]<<8 | receive[2];
    return temp;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ͷ�ڲ��Ĵ�������д����
//  @param      addr    ����ͷ�ڲ��Ĵ�����ַ
//  @param      data    ��Ҫд�������
//  @return     u16  �Ĵ�����ǰ���ݣ�����ȷ���Ƿ�д��ɹ�
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
    
    //�ȴ����ܻش�����
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    temp = receive[1]<<8 | receive[2];
    return temp;

}

void mt9v032_init(void)
{
    //���ò���    ������ο�ʹ���ֲ�
    u16 temp, i;
    u8  send_buffer[4];
    
    usart2_init(2,9600);		//��ʼ������2������Ϊ9600
    
    delay_ms(1000);
    uart_receive_flag = 0;
    
    //��ʼ��������ͷ�����³�ʼ��
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
    
    //�ȴ�����ͷ��ʼ���ɹ�
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    while((0xff != receive[1]) || (0xff != receive[2]));
    //���ϲ��ֶ�����ͷ���õ�����ȫ�����ᱣ��������ͷ��51��Ƭ����eeprom��
    //����set_exposure_time�����������õ��ع����ݲ��洢��eeprom��
    
    //��ȡ���ñ��ڲ鿴�����Ƿ���ȷ
    get_config();
    
    //��ʼ��dcmi�ӿ�
    dcmi_init();
    //��ʼ��dcmi��dmaͨ��
    dcmi_dma_init((u32)image,COL*ROW/2/4,DMA_MemoryDataSize_Byte,DMA_MemoryInc_Enable);//DCMI DMA����
    
    
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������ͷͼ��������λ���鿴ͼ��
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:				���øú���ǰ���ȳ�ʼ��uart1
//-------------------------------------------------------------------------------------------------------------------
void gd32_sendimg_032(void)
{
	uint8_t send_buffer[4] = {0x00,0xff,0x01,0x01};
    uint8_t i;
    //���ͼ��������󣬽��ְ����͡�
    //��65535�ֽ�Ϊ��λ����ָ
    uint8_t pack_num = ROW*COL >> 16;       //�ָ�pack_num����
    uint16_t pack_tail = ROW*COL & 0xFFFF;  //β��������
	
	
	
	//����Э��ͷ
	uart_putbuff(USART1,send_buffer,4); 

    //�ȷ���pack_num * 65535�ֽ���
    for(i=0; i<pack_num; i++)
    {
		uart_putbuff(USART1,(uint8_t *)image + i*0xFFFF,0xFFFF); 
    }
    //Ȼ����β����
	uart_putbuff(USART1,(uint8_t *)image + ROW*COL - pack_tail,pack_tail); 

}


