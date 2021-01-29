/*��
	\file  wh_exti.c
	\brief EXTI �� ECLIC �м��
*/

#include "wh_exit.h"

/*!
    \brief      EXTI ��ʼ��
    \param[in]  linex: ѡ��EXTI line number, ��μ� exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[in]  mode: �����ж�ģʽ�����¼�ģʽ, ��μ� exti_mode_enum
      \arg        EXTI_INTERRUPT: �ж�ģʽ
      \arg        EXTI_EVENT: �¼�ģʽ
    \param[in]  trig_type: ���ô�����ʽ, ��μ� exti_trig_type_enum
      \arg        EXTI_TRIG_RISING: �����ش���
      \arg        EXTI_TRIG_FALLING: �½��ش���
      \arg        EXTI_TRIG_BOTH: �����غ��½��ؾ�����
      \arg        EXTI_TRIG_NONE: �����غ��½��ؾ�������
    \param[out] ��
    \retval     ��
*/
void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type)
{
    /* �������� EXTI line x */
    EXTI_INTEN &= ~(uint32_t) linex;
    EXTI_EVEN &= ~(uint32_t) linex;
    EXTI_RTEN &= ~(uint32_t) linex;
    EXTI_FTEN &= ~(uint32_t) linex;

    /* ����EXITģʽ��ʹ���жϻ����¼� */
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

    /* ���� EXTI ������ʽ */
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
    \brief      EXIT�ж�ʹ��
    \param[in]  linex: EXTI line number, ��μ� exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] ��
    \retval     ��
*/
void exti_interrupt_enable(exti_line_enum linex)
{
    EXTI_INTEN |= (uint32_t) linex;
}

/*!
    \brief      EXIT�¼�ʹ��
    \param[in]  linex: EXTI line number, ��μ� exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] ��
    \retval     ��
*/
void exti_event_enable(exti_line_enum linex)
{
    EXTI_EVEN |= (uint32_t) linex;
}

/*!
    \brief      EXIT�ж�ʧ��
    \param[in]  linex: EXTI line number, ��μ� exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] ��
    \retval     ��
*/
void exti_interrupt_disable(exti_line_enum linex)
{
    EXTI_INTEN &= ~(uint32_t) linex;
}

/*!
    \brief      EXIT�¼�ʧ��
    \param[in]  linex: EXTI line number, ��μ� exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] ��
    \retval     ��
*/
void exti_event_disable(exti_line_enum linex)
{
    EXTI_EVEN &= ~(uint32_t) linex;
}

/*!
    \brief      ���EXIT�����־λ
    \param[in]  linex: EXTI line number, ��μ� exti_line_enum
      \arg        EXTI_x (x=0..18): EXTI line x
    \param[out] ��
    \retval     ��
*/
void exti_interrupt_flag_clear(exti_line_enum linex)
{
    EXTI_PD = (uint32_t) linex;
}

/*!
    \brief      ����ȫ���ж�
    \param[in]  ��
    \param[out] ��
    \retval     ��
*/
void eclic_global_interrupt_enable(void){
    /* ���û����ж�ʹ��λ */
    set_csr(mstatus, MSTATUS_MIE);
}

/*!
    \brief      �ر�ȫ���ж�
    \param[in]  ��
    \param[out] ��
    \retval     ��
*/
void eclic_global_interrupt_disable(void){
    /* ��������ж�ʹ��λ */
    clear_csr(mstatus, MSTATUS_MIE);
}

/*!
    \brief      �������ȼ���<priority group>
    \param[in]  prigroup: ָ�����ȼ���<priority group>
      \arg        ECLIC_PRIGROUP_LEVEL0_PRIO4
      \arg        ECLIC_PRIGROUP_LEVEL1_PRIO3
      \arg        ECLIC_PRIGROUP_LEVEL2_PRIO2
      \arg        ECLIC_PRIGROUP_LEVEL3_PRIO1
      \arg        ECLIC_PRIGROUP_LEVEL4_PRIO0
    \param[out] ��
    \retval     ��
*/
void eclic_priority_group_set(uint32_t prigroup) {
    eclic_set_nlbits(prigroup);
}

/*!
    \brief      ���ж�����<interrupt request>
    \param[in]  source: �ж�����<interrupt request>, ����μ� IRQn_Type
    \param[in]  level: ��Ҫ���õļ���(���ֵΪ15���ο����ȼ���<priority group>)
    \param[in]  priority: ��Ҫ���õ����ȼ�(���ֵΪ15���ο����ȼ���<priority group>)
    \param[out] ��
    \retval     ��
*/
void eclic_irq_enable(uint32_t source, uint8_t lvl_abs, uint8_t priority) {
    eclic_enable_interrupt(source);
    eclic_set_irq_lvl_abs(source, lvl_abs);
    eclic_set_irq_priority(source, priority);
}

/*!
    \brief      ���ж�����<interrupt request>
    \param[in]  source: �ж�����<interrupt request>, ����μ� IRQn_Type
    \param[out] ��
    \retval     ��
*/
void eclic_irq_disable(uint32_t source) {
    eclic_disable_interrupt(source);
}