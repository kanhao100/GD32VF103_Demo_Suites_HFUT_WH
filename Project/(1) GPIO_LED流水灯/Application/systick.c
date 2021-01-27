/*!
    \file  systick.c
    \brief the systick configuration file
*/

#include "gd32vf103.h"
#include "systick.h"

/*!
    \brief      延时1ms
    \param[in]  count:延时1ms
    \param[out] 无
    \retval     无
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
