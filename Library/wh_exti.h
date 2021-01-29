/*！
	\file  wh_exti.h
	\brief EXTI 和 ECLIC 中间库
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

/* 外部中断和事件  */
typedef enum {
    EXTI_INTERRUPT = 0,                                       /*!< EXTI 中断模式 */
    EXTI_EVENT                                                /*!< EXTI 事件模式 */
} exti_mode_enum;

/* 中断触发模式 */
typedef enum {
    EXTI_TRIG_RISING = 0,                                     /*!< EXTI 上升沿触发 */
    EXTI_TRIG_FALLING,                                        /*!< EXTI 下降沿触发 */
    EXTI_TRIG_BOTH,                                           /*!< EXTI 上升沿和下降沿触发 */
    EXTI_TRIG_NONE                                            /*!< 不是上升沿也不是下降沿 */
} exti_trig_type_enum;

/* EXTI 初始化 */
void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type);
/* EXTI 中断使能 */
void exti_interrupt_enable(exti_line_enum linex);
/* EXTI 事件使能 */
void exti_event_enable(exti_line_enum linex);
/* EXTI 中断失能 */
void exti_interrupt_disable(exti_line_enum linex);
/* EXTI 事件失能 */
void exti_event_disable(exti_line_enum linex);
/* 清除EXIT挂起标志位 */
void exti_interrupt_flag_clear(exti_line_enum linex);


/* 打开全局中断 */
void eclic_global_interrupt_enable(void);
/* 关闭全局中断 */
void eclic_global_interrupt_disable(void);
/* 设置优先级组<priority group> */
void eclic_priority_group_set(uint32_t prigroup);
/* 打开中断请求<interrupt request> */
void eclic_irq_enable(uint32_t source, uint8_t level, uint8_t priority);
/* 关闭中断请求<interrupt request> */
void eclic_irq_disable(uint32_t source);

#endif
