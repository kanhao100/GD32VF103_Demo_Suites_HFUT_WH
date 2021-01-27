/*!
    \file    main.c
    \brief   GPIO_LED��ˮ��
*/

#include "gd32vf103.h"
#include "gd32vf103v_eval.h"
#include "systick.h"
#include <stdio.h>

/*!
    \brief      ������
    \param[in]  ��
    \param[out] ��
    \retval     ��
*/
int main(void)
{
    /* �� LED ʱ�� */
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOE);
    /* ���� LED GPIO �˿� */
    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_2);
    gpio_init(GPIOE, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
    gpio_bit_reset(GPIOC, GPIO_PIN_0 | GPIO_PIN_2);
    gpio_bit_reset(GPIOE, GPIO_PIN_0 | GPIO_PIN_1);

    while(1){
        /* �� LED1 */
        gpio_bit_set(GPIOC, GPIO_PIN_0);
        /* ��ʱ400ms */
        delay_1ms(400);
        /* �� LED2 */
        gpio_bit_set(GPIOC, GPIO_PIN_2);
        /* ��ʱ400ms */
        delay_1ms(400);
        /* �� LED3 */
        gpio_bit_set(GPIOE, GPIO_PIN_0);
        /* ��ʱ400ms */
        delay_1ms(400);
        /* �� LED4 */
        gpio_bit_set(GPIOE, GPIO_PIN_1);
        /* ��ʱ400ms */
        delay_1ms(400);
        /* �ر�4�� LED */
        gpio_bit_reset(GPIOC, GPIO_PIN_0 | GPIO_PIN_2);
        gpio_bit_reset(GPIOE, GPIO_PIN_0 | GPIO_PIN_1);
        /* ��ʱ400ms */
        delay_1ms(400);
    }
}
