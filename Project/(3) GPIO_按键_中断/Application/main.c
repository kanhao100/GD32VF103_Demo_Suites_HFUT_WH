/*��
	\file  main.c
	\brief GPIO_����_�ж�
*/

#include "gd32vf103.h"
#include "gd32vf103c_start.h"

/*!
    \brief      ������
    \param[in]  ��
    \param[out] ��
    \retval     ��
*/
int main(void)
{
	/* ��ʼ��start�������ϵ�LED */
    led_init();
    /* �������ж� */
    eclic_global_interrupt_enable();
    eclic_priority_group_set(ECLIC_PRIGROUP_LEVEL3_PRIO1);
    /* ��start�������ϵİ���Wakeup clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);
    /* ������Ϊ����ڵİ����Ķ˿ں� */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    /* ���������ⲿ�ж�����Ϊ������ȼ� */
    eclic_irq_enable(EXTI0_IRQn, 1, 1);
    /* ���Ӱ������ⲿ�ж��ߵ�GPIO */
    gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_0);
    /* ���ð������ⲿ�ж��� */
    exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    /* ����жϱ�־λ */
    exti_interrupt_flag_clear(EXTI_0);
    while(1)
    {
    }
}

/*!
    \brief      ��ʼ��  LED
    \param[in]  ��
    \param[out] ��
    \retval     ��
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
    \param[in]  count:��ʱ1ms
    \param[out] ��
    \retval     ��
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


/*!
    \brief      ��תLED�ź�
    \param[in]  times: ��תLED�źŵĴ���
    \param[out] ��
    \retval     ��
*/
void led_flash(int times)
{
    int i;
    for(i=0; i<times; i++)
    {
        /* ��ʱ 400 ms */
        delay_1ms(400);
        /* ��ת LED�ź� */
        gpio_bit_write(GPIOA, GPIO_PIN_7, (bit_status)(1-gpio_input_bit_get(GPIOA, GPIO_PIN_7)));
        /* ��ʱ 400 ms */
        delay_1ms(400);
        /* ��ת LED�ź� */
        gpio_bit_write(GPIOA, GPIO_PIN_7, (bit_status)(1-gpio_input_bit_get(GPIOA, GPIO_PIN_7)));
    }
}
