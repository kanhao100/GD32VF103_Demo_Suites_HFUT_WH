/*!
    \file    main.c
    \brief   GPIO_LED流水灯
*/

#include "gd32vf103.h"
#include "gd32vf103v_eval.h"
#include "systick.h"
#include <stdio.h>

/*!
    \brief      主函数
    \param[in]  无
    \param[out] 无
    \retval     无
*/
int main(void)
{
    /* 打开 LED 时钟 */
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOE);
    /* 配置 LED GPIO 端口 */
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_2);
    gpio_init(GPIOE, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
    gpio_bit_reset(GPIOC, GPIO_PIN_0 | GPIO_PIN_2);
    gpio_bit_reset(GPIOE, GPIO_PIN_0 | GPIO_PIN_1);

    while(1){
        /* 打开 LED1 */
        gpio_bit_set(GPIOC, GPIO_PIN_0);
        /* 延时400ms */
        delay_1ms(400);
        /* 打开 LED2 */
        gpio_bit_set(GPIOC, GPIO_PIN_2);
        /* 延时400ms */
        delay_1ms(400);
        /* 打开 LED3 */
        gpio_bit_set(GPIOE, GPIO_PIN_0);
        /* 延时400ms */
        delay_1ms(400);
        /* 打开 LED4 */
        gpio_bit_set(GPIOE, GPIO_PIN_1);
        /* 延时400ms */
        delay_1ms(400);
        /* 关闭4个 LED */
        gpio_bit_reset(GPIOC, GPIO_PIN_0 | GPIO_PIN_2);
        gpio_bit_reset(GPIOE, GPIO_PIN_0 | GPIO_PIN_1);
        /* 延时400ms */
        delay_1ms(400);
    }
}
