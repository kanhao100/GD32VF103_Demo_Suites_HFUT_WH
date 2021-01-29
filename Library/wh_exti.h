/*��
	\file  wh_exti.h
	\brief EXTI �� ECLIC �м��
*/

#ifndef _wh_exti_h
#define _wh_exti_h

#include "gd32vf103.h"
#include "gd32vf103_exti.h"
#include "gd32vf103_eclic.h"

/* EXTI line number */
typedef enum {
    EXTI_0 = BIT(0),                                          /*!< EXTI line 0 */
    EXTI_1 = BIT(1),                                          /*!< EXTI line 1 */
    EXTI_2 = BIT(2),                                          /*!< EXTI line 2 */
    EXTI_3 = BIT(3),                                          /*!< EXTI line 3 */
    EXTI_4 = BIT(4),                                          /*!< EXTI line 4 */
    EXTI_5 = BIT(5),                                          /*!< EXTI line 5 */
    EXTI_6 = BIT(6),                                          /*!< EXTI line 6 */
    EXTI_7 = BIT(7),                                          /*!< EXTI line 7 */
    EXTI_8 = BIT(8),                                          /*!< EXTI line 8 */
    EXTI_9 = BIT(9),                                          /*!< EXTI line 9 */
    EXTI_10 = BIT(10),                                        /*!< EXTI line 10 */
    EXTI_11 = BIT(11),                                        /*!< EXTI line 11 */
    EXTI_12 = BIT(12),                                        /*!< EXTI line 12 */
    EXTI_13 = BIT(13),                                        /*!< EXTI line 13 */
    EXTI_14 = BIT(14),                                        /*!< EXTI line 14 */
    EXTI_15 = BIT(15),                                        /*!< EXTI line 15 */
    EXTI_16 = BIT(16),                                        /*!< EXTI line 16 */
    EXTI_17 = BIT(17),                                        /*!< EXTI line 17 */
    EXTI_18 = BIT(18),                                        /*!< EXTI line 18 */
} exti_line_enum;

/* �ⲿ�жϺ��¼�  */
typedef enum {
    EXTI_INTERRUPT = 0,                                       /*!< EXTI �ж�ģʽ */
    EXTI_EVENT                                                /*!< EXTI �¼�ģʽ */
} exti_mode_enum;

/* �жϴ���ģʽ */
typedef enum {
    EXTI_TRIG_RISING = 0,                                     /*!< EXTI �����ش��� */
    EXTI_TRIG_FALLING,                                        /*!< EXTI �½��ش��� */
    EXTI_TRIG_BOTH,                                           /*!< EXTI �����غ��½��ش��� */
    EXTI_TRIG_NONE                                            /*!< ����������Ҳ�����½��� */
} exti_trig_type_enum;

/* EXTI ��ʼ�� */
void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type);
/* EXTI �ж�ʹ�� */
void exti_interrupt_enable(exti_line_enum linex);
/* EXTI �¼�ʹ�� */
void exti_event_enable(exti_line_enum linex);
/* EXTI �ж�ʧ�� */
void exti_interrupt_disable(exti_line_enum linex);
/* EXTI �¼�ʧ�� */
void exti_event_disable(exti_line_enum linex);
/* ���EXIT�����־λ */
void exti_interrupt_flag_clear(exti_line_enum linex);


/* ��ȫ���ж� */
void eclic_global_interrupt_enable(void);
/* �ر�ȫ���ж� */
void eclic_global_interrupt_disable(void);
/* �������ȼ���<priority group> */
void eclic_priority_group_set(uint32_t prigroup);
/* ���ж�����<interrupt request> */
void eclic_irq_enable(uint32_t source, uint8_t level, uint8_t priority);
/* �ر��ж�����<interrupt request> */
void eclic_irq_disable(uint32_t source);

#endif
