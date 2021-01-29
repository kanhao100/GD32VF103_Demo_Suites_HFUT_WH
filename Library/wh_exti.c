/*！
	\file  wh_exti.c
	\brief EXTI 和 ECLIC 中间库
*/

#include "wh_exit.h"

/*!
    \brief      EXTI 初始化
    \param[in]  linex: 选择EXTI line number, 请参见 exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[in]  mode: 设置中断模式或者事件模式, 请参见 exti_mode_enum
      \arg        EXTI_INTERRUPT: 中断模式
      \arg        EXTI_EVENT: 事件模式
    \param[in]  trig_type: 设置触发方式, 请参见 exti_trig_type_enum
      \arg        EXTI_TRIG_RISING: 上升沿触发
      \arg        EXTI_TRIG_FALLING: 下降沿触发
      \arg        EXTI_TRIG_BOTH: 上升沿和下降沿均触发
      \arg        EXTI_TRIG_NONE: 上升沿和下降沿均不触发
    \param[out] 无
    \retval     无
*/
void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type)
{
    /* 重新设置 EXTI line x */
    EXTI_INTEN &= ~(uint32_t) linex;
    EXTI_EVEN &= ~(uint32_t) linex;
    EXTI_RTEN &= ~(uint32_t) linex;
    EXTI_FTEN &= ~(uint32_t) linex;

    /* 设置EXIT模式，使能中断或者事件 */
    switch (mode) {
    case EXTI_INTERRUPT:
        EXTI_INTEN |= (uint32_t) linex;
        break;
    case EXTI_EVENT:
        EXTI_EVEN |= (uint32_t) linex;
        break;
    default:
        break;
    }

    /* 设置 EXTI 触发方式 */
    switch (trig_type) {
    case EXTI_TRIG_RISING:
        EXTI_RTEN |= (uint32_t) linex;
        EXTI_FTEN &= ~(uint32_t) linex;
        break;
    case EXTI_TRIG_FALLING:
        EXTI_RTEN &= ~(uint32_t) linex;
        EXTI_FTEN |= (uint32_t) linex;
        break;
    case EXTI_TRIG_BOTH:
        EXTI_RTEN |= (uint32_t) linex;
        EXTI_FTEN |= (uint32_t) linex;
        break;
    case EXTI_TRIG_NONE:
    default:
        break;
    }
}

/*!
    \brief      EXIT中断使能
    \param[in]  linex: EXTI line number, 请参加 exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] 无
    \retval     无
*/
void exti_interrupt_enable(exti_line_enum linex)
{
    EXTI_INTEN |= (uint32_t) linex;
}

/*!
    \brief      EXIT事件使能
    \param[in]  linex: EXTI line number, 请参见 exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] 无
    \retval     无
*/
void exti_event_enable(exti_line_enum linex)
{
    EXTI_EVEN |= (uint32_t) linex;
}

/*!
    \brief      EXIT中断失能
    \param[in]  linex: EXTI line number, 请参见 exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] 无
    \retval     无
*/
void exti_interrupt_disable(exti_line_enum linex)
{
    EXTI_INTEN &= ~(uint32_t) linex;
}

/*!
    \brief      EXIT事件失能
    \param[in]  linex: EXTI line number, 请参见 exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] 无
    \retval     无
*/
void exti_event_disable(exti_line_enum linex)
{
    EXTI_EVEN &= ~(uint32_t) linex;
}

/*!
    \brief      清除EXIT挂起标志位
    \param[in]  linex: EXTI line number, 请参见 exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] 无
    \retval     无
*/
void exti_interrupt_flag_clear(exti_line_enum linex)
{
    EXTI_PD = (uint32_t) linex;
}

/*!
    \brief      开启全局中断
    \param[in]  无
    \param[out] 无
    \retval     无
*/
void eclic_global_interrupt_enable(void){
    /* 设置机器中断使能位 */
    set_csr(mstatus, MSTATUS_MIE);
}

/*!
    \brief      关闭全局中断
    \param[in]  无
    \param[out] 无
    \retval     无
*/
void eclic_global_interrupt_disable(void){
    /* 清楚机器中断使能位 */
    clear_csr(mstatus, MSTATUS_MIE);
}

/*!
    \brief      设置优先级组<priority group>
    \param[in]  prigroup: 指定优先级组<priority group>
      \arg        ECLIC_PRIGROUP_LEVEL0_PRIO4
      \arg        ECLIC_PRIGROUP_LEVEL1_PRIO3
      \arg        ECLIC_PRIGROUP_LEVEL2_PRIO2
      \arg        ECLIC_PRIGROUP_LEVEL3_PRIO1
      \arg        ECLIC_PRIGROUP_LEVEL4_PRIO0
    \param[out] 无
    \retval     无
*/
void eclic_priority_group_set(uint32_t prigroup) {
    eclic_set_nlbits(prigroup);
}

/*!
    \brief      打开中断请求<interrupt request>
    \param[in]  source: 中断请求<interrupt request>, 具体参见 IRQn_Type
    \param[in]  level: 需要设置的级别(最大值为15，参考优先级组<priority group>)
    \param[in]  priority: 需要设置的优先级(最大值为15，参考优先级组<priority group>)
    \param[out] 无
    \retval     无
*/
void eclic_irq_enable(uint32_t source, uint8_t lvl_abs, uint8_t priority) {
    eclic_enable_interrupt(source);
    eclic_set_irq_lvl_abs(source, lvl_abs);
    eclic_set_irq_priority(source, priority);
}

/*!
    \brief      打开中断请求<interrupt request>
    \param[in]  source: 中断请求<interrupt request>, 具体参见 IRQn_Type
    \param[out] 无
    \retval     无
*/
void eclic_irq_disable(uint32_t source) {
    eclic_disable_interrupt(source);
}