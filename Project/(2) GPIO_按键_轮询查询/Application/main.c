/*！
	\file  main.c
	\brief GPIO_按键_轮询查询
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
    /* 初始化start开发板上的LED */
    led_init();
    /* 打开start开发板上的按键Wakeup clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);
    /* 配置作为输入口的按键的端口号 */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    while(1)
	{
		if(SET ==  gpio_input_bit_get(GPIOA, GPIO_PIN_0))
		{
			/* 按键防抖 */
			delay_1ms(50);
			if(SET == gpio_input_bit_get(GPIOA, GPIO_PIN_0))
			{
				/* 翻转 LED 的状态 */
				gpio_bit_write(GPIOA, GPIO_PIN_7, (bit_status)(1-gpio_input_bit_get(GPIOA, GPIO_PIN_7)));
			}
			while(SET == gpio_input_bit_get(GPIOA, GPIO_PIN_0))
			{
			}
		}
	}
}

/*!
    \brief      初始化  LED
    \param[in]  none
    \param[out] none
    \retval     none
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
    \param[in]  count: 延时1ms
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

