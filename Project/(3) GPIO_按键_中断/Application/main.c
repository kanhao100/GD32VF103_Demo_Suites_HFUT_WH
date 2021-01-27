/*！
	\file  main.c
	\brief GPIO_按键_中断
*/

#include "gd32vf103.h"
#include "gd32vf103c_start.h"

/*!
    \brief      主函数
    \param[in]  无
    \param[out] 无
    \retval     无
*/
int main(void)
{
	/* 初始化start开发板上的LED */
    led_init();
    /* 开启总中断 */
    eclic_global_interrupt_enable();
    eclic_priority_group_set(ECLIC_PRIGROUP_LEVEL3_PRIO1);
    /* 打开start开发板上的按键Wakeup clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);
    /* 配置作为输入口的按键的端口号 */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    /* 将按键的外部中断设置为最低优先级 */
    eclic_irq_enable(EXTI0_IRQn, 1, 1);
    /* 连接按键的外部中断线到GPIO */
    gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_0);
    /* 配置按键的外部中断线 */
    exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    /* 清除中断标志位 */
    exti_interrupt_flag_clear(EXTI_0);
    while(1)
    {
    }
}

/*!
    \brief      初始化  LED
    \param[in]  无
    \param[out] 无
    \retval     无
*/
void led_init(void)
{
    /* 打开 LED clock */
   rcu_periph_clock_enable(RCU_GPIOA);
   /* 确定 LED 的 GPIO编号 */
   gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
   /* 关闭 LEDs */
   gpio_bit_reset(GPIOA, GPIO_PIN_7);
}

/*!
    \brief      延时1ms
    \param[in]  count:延时1ms
    \param[out] 无
    \retval     无
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
    \brief      翻转LED信号
    \param[in]  times: 翻转LED信号的次数
    \param[out] 无
    \retval     无
*/
void led_flash(int times)
{
    int i;
    for(i=0; i<times; i++)
    {
        /* 延时 400 ms */
        delay_1ms(400);
        /* 翻转 LED信号 */
        gpio_bit_write(GPIOA, GPIO_PIN_7, (bit_status)(1-gpio_input_bit_get(GPIOA, GPIO_PIN_7)));
        /* 延时 400 ms */
        delay_1ms(400);
        /* 翻转 LED信号 */
        gpio_bit_write(GPIOA, GPIO_PIN_7, (bit_status)(1-gpio_input_bit_get(GPIOA, GPIO_PIN_7)));
    }
}
