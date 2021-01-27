/*!
    \file  systick.c
    \brief the systick configuration file
*/

#include "gd32vf103.h"
#include "systick.h"

/*!
    \brief      ��ʱ1ms
    \param[in]  count:��ʱ1ms
    \param[out] ��
    \retval     ��
*/
void delay_1ms(uint32_t count)
{
    uint64_t start_mtime, delta_mtime;
    uint64_t tmp = get_timer_value();
    do {
    start_mtime = get_timer_value();
    } while (start_mtime == tmp);

    do {
    delta_mtime = get_timer_value() - start_mtime;
    }while(delta_mtime <(SystemCoreClock/4000.0 *count ));
}
