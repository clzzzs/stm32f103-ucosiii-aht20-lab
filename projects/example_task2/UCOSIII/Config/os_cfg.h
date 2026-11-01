/*
*********************************************************************************************************
*                                              uC/OS-III
*                                        The Real-Time Kernel
*
*                    Copyright 2009-2022 Silicon Laboratories Inc. www.silabs.com
*
*                                 SPDX-License-Identifier: APACHE-2.0
*
*               This software is subject to an open source license and is distributed by
*                Silicon Laboratories Inc. pursuant to the terms of the Apache License,
*                    Version 2.0 available at www.apache.org/licenses/LICENSE-2.0.
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          CONFIGURATION FILE
*
* Filename : os_cfg.h
* Version  : V3.08.02
*********************************************************************************************************
*/

#ifndef OS_CFG_H
#define OS_CFG_H

                                                                /* --------------------------- MISCELLANEOUS --------------------------- */
#define OS_CFG_APP_HOOKS_EN                        0u           /* 本实验不使用应用钩子，关闭以减小代码量 */
#define OS_CFG_ARG_CHK_EN                          0u           /* 教学工程不做参数检查，代码更简洁 */
#define OS_CFG_CALLED_FROM_ISR_CHK_EN              0u           /* 不检查 API 是否在中断中误调用 */
#define OS_CFG_DBG_EN                              0u           /* 关闭调试变量 */
#define OS_CFG_TICK_EN                             1u           /* 使能系统节拍 */
#define OS_CFG_DYN_TICK_EN                         0u           /* 不使用动态节拍 */
#define OS_CFG_INVALID_OS_CALLS_CHK_EN             0u           /* 不检查非法内核调用 */
#define OS_CFG_OBJ_TYPE_CHK_EN                     0u           /* 不检查对象类型 */
#define OS_CFG_OBJ_CREATED_CHK_EN                  0u           /* 不检查对象是否已创建 */
#define OS_CFG_TS_EN                               0u           /* 不使用时间戳 */

#define OS_CFG_PRIO_MAX                           32u           /* 本实验只需要少量优先级 */

#define OS_CFG_SCHED_LOCK_TIME_MEAS_EN             0u           /* 不测量调度器锁定时间 */
#define OS_CFG_SCHED_ROUND_ROBIN_EN                0u           /* 三个任务周期不同，不需要时间片轮转 */

#define OS_CFG_STK_SIZE_MIN                       64u           /* Minimum allowable task stack size                                     */


                                                                /* 本实验只使用任务与延时，以下内核对象全部关闭 */
#define OS_CFG_FLAG_EN                             0u
#define OS_CFG_FLAG_DEL_EN                         0u
#define OS_CFG_FLAG_MODE_CLR_EN                    0u
#define OS_CFG_FLAG_PEND_ABORT_EN                  0u

#define OS_CFG_MEM_EN                              0u

#define OS_CFG_MUTEX_EN                            0u
#define OS_CFG_MUTEX_DEL_EN                        0u
#define OS_CFG_MUTEX_PEND_ABORT_EN                 0u

#define OS_CFG_Q_EN                                0u
#define OS_CFG_Q_DEL_EN                            0u
#define OS_CFG_Q_FLUSH_EN                          0u
#define OS_CFG_Q_PEND_ABORT_EN                     0u

#define OS_CFG_SEM_EN                              0u
#define OS_CFG_SEM_DEL_EN                          0u
#define OS_CFG_SEM_PEND_ABORT_EN                   0u
#define OS_CFG_SEM_SET_EN                          0u


                                                                /* -------------------------- TASK MANAGEMENT -------------------------- */
#define OS_CFG_STAT_TASK_EN                        0u           /* 不创建统计任务 */
#define OS_CFG_STAT_TASK_STK_CHK_EN                0u

#define OS_CFG_TASK_CHANGE_PRIO_EN                 0u           /* 不修改任务优先级 */
#define OS_CFG_TASK_DEL_EN                         0u           /* 不删除任务 */
#define OS_CFG_TASK_IDLE_EN                        1u           /* 保留空闲任务 */
#define OS_CFG_TASK_PROFILE_EN                     0u           /* 不统计任务运行信息 */
#define OS_CFG_TASK_Q_EN                           0u           /* 不使用任务消息队列 */
#define OS_CFG_TASK_Q_PEND_ABORT_EN                0u
#define OS_CFG_TASK_REG_TBL_SIZE                   1u           /* 不调用任务寄存器 API，但保留 1 个元素避免零长数组 */

#define OS_CFG_TASK_STK_REDZONE_EN                 0u           /* 不启用栈警戒区 */
#define OS_CFG_TASK_STK_REDZONE_DEPTH              0u

#define OS_CFG_TASK_SEM_PEND_ABORT_EN              0u
#define OS_CFG_TASK_SUSPEND_EN                     0u           /* 不挂起/恢复任务 */


                                                                /* ------------------ TASK LOCAL STORAGE MANAGEMENT -------------------  */
#define OS_CFG_TLS_TBL_SIZE                        0u           /* Include code for Task Local Storage (TLS) registers                   */


                                                                /* ------------------------- TIME MANAGEMENT --------------------------  */
#define OS_CFG_TIME_DLY_HMSM_EN                    1u           /* 使用 OSTimeDlyHMSM() 做周期延时 */
#define OS_CFG_TIME_DLY_RESUME_EN                  0u           /* 不恢复延时任务 */


                                                                /* ------------------------- TIMER MANAGEMENT -------------------------- */
#define OS_CFG_TMR_EN                              0u           /* 不使用软件定时器 */
#define OS_CFG_TMR_DEL_EN                          0u


                                                                /* ------------------------- TRACE RECORDER ---------------------------- */
#define OS_CFG_TRACE_EN                            0u           /* Enable (1) or Disable (0) uC/OS-III Trace instrumentation             */
#define OS_CFG_TRACE_API_ENTER_EN                  0u           /* Enable (1) or Disable (0) uC/OS-III Trace API enter instrumentation   */
#define OS_CFG_TRACE_API_EXIT_EN                   0u           /* Enable (1) or Disable (0) uC/OS-III Trace API exit  instrumentation   */

#endif
