#ifndef APP_CFG_H
#define APP_CFG_H

/* 任务优先级：数值越小优先级越高 */
#define APP_CFG_TASK_LED1_PRIO      4u
#define APP_CFG_TASK_LED2_PRIO      5u
#define APP_CFG_TASK_AHT20_PRIO     6u

/* 任务栈：CPU_STK 为 32 位，128 个元素 = 512 字节 */
#define APP_CFG_TASK_STK_SIZE       128u
#define APP_CFG_AHT20_STK_SIZE      256u

#endif
