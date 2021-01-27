/*��
	\file  main.c
	\brief GPIO_����_��ѯ��ѯ
*/

#include "gd32vf103.h"
#include "gd32vf103c_start.h"

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* ��ʼ��start�������ϵ�LED */
    led_init();
    /* ��start�������ϵİ���Wakeup clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);
    /* ������Ϊ����ڵİ����Ķ˿ں� */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    while(1)
	{
		if(SET ==  gpio_input_bit_get(GPIOA, GPIO_PIN_0))
		{
			/* �������� */
			delay_1ms(50);
			if(SET == gpio_input_bit_get(GPIOA, GPIO_PIN_0))
			{
				/* ��ת LED ��״̬ */
				gpio_bit_write(GPIOA, GPIO_PIN_7, (bit_status)(1-gpio_input_bit_get(GPIOA, GPIO_PIN_7)));
			}
			while(SET == gpio_input_bit_get(GPIOA, GPIO_PIN_0))
			{
			}
		}
	}
}

/*!
    \brief      ��ʼ��  LED
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_init(void)
{
    /* �� LED clock */
   rcu_periph_clock_enable(RCU_GPIOA);
   /* ȷ�� LED �� GPIO��� */
   gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
   /* �ر� LEDs */
   gpio_bit_reset(GPIOA, GPIO_PIN_7);
}

/*!
    \brief      ��ʱ1ms
    \param[in]  count: ��ʱ1ms
    \param[out] none
    \retval     none
*/
void delay_1ms(uint32_t count)
{
    uint64_t start_mtime, delta_mtime;
    // Don't start measuruing until we see an mtime tick
    uint64_t tmp = get_timer_value();
    do
    {
    start_mtime = get_timer_value();
    }
    while (start_mtime == tmp);
    do
    {
    delta_mtime = get_timer_value() - start_mtime;
    }
    while(delta_mtime <(SystemCoreClock/4000.0 *count ));
}

