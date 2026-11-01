#include "my_main.h"
#include "includes.h"

#define LED1_PIN            GPIO_PIN_5
#define LED1_PORT           GPIOA
#define LED2_PIN            GPIO_PIN_6
#define LED2_PORT           GPIOA

static OS_TCB      Led1TCB;
static OS_TCB      Led2TCB;
static OS_TCB      UartTCB;

static CPU_STK     Led1Stk[APP_CFG_TASK_STK_SIZE];
static CPU_STK     Led2Stk[APP_CFG_TASK_STK_SIZE];
static CPU_STK     UartStk[APP_CFG_UART_STK_SIZE];

static void led1_task(void *p_arg);
static void led2_task(void *p_arg);
static void uart_task(void *p_arg);

// 始化 uC/OS-III、创建 3 个任务并启动调度器 
void setup(void)
{
    OS_ERR err;

    OSInit(&err);

    OSTaskCreate(&Led1TCB, "led1", led1_task, (void *)0,APP_CFG_TASK_LED1_PRIO, &Led1Stk[0], APP_CFG_TASK_STK_SIZE / 10u, APP_CFG_TASK_STK_SIZE, 0u, 0u, (void *)0,OS_OPT_TASK_STK_CLR, &err);

    OSTaskCreate(&Led2TCB, "led2", led2_task, (void *)0,APP_CFG_TASK_LED2_PRIO,&Led2Stk[0], APP_CFG_TASK_STK_SIZE / 10u, APP_CFG_TASK_STK_SIZE,0u, 0u, (void *)0,OS_OPT_TASK_STK_CLR, &err);

    OSTaskCreate(&UartTCB, "uart", uart_task, (void *)0,APP_CFG_TASK_UART_PRIO,&UartStk[0], APP_CFG_UART_STK_SIZE / 10u, APP_CFG_UART_STK_SIZE, 0u, 0u, (void *)0,OS_OPT_TASK_STK_CLR, &err);

    OSStart(&err);              /* 不返回 */
}

void loop(void)
{
}

// 任务 1：每 1 秒翻转一次 LED1 
static void led1_task(void *p_arg)
{
    OS_ERR err;

    (void)p_arg;
    OS_CPU_SysTickInitFreq(SystemCoreClock);

    for (;;) 
	 {
        HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
        OSTimeDlyHMSM(0u, 0u, 1u, 0u, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

// 任务 2：每 3 秒翻转一次 LED2
static void led2_task(void *p_arg)
{
    OS_ERR err;

    (void)p_arg;

    for (;;) {
        HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN);
        OSTimeDlyHMSM(0u, 0u, 3u, 0u, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

// 任务 3：每 2 秒通过 USART1 发送一次指定字符串（GBK 编码）
static void uart_task(void *p_arg)
{
    static const char hello[] = {
        'h', 'e', 'l', 'l', 'o', ' ', 'u', 'c', '/', 'O', 'S', '!', ' ',
        0xBB, 0xB6, 0xD3, 0xAD, 0xC0, 0xB4, 0xB5, 0xBD,     /* 欢迎来到 */
        'R', 'T', 'O', 'S',
        0xB6, 0xE0, 0xC8, 0xCE, 0xCE, 0xF1, 0xBB, 0xB7, 0xBE, 0xB3, /* 多任务环境 */
        0xA3, 0xA1,                                         /* ！ */
        '\r', '\n', 0x00
    };
    OS_ERR err;

    (void)p_arg;

    for (;;) {
        HAL_UART_Transmit(&huart1, (uint8_t *)hello, sizeof(hello) - 1u, 1000u);
        OSTimeDlyHMSM(0u, 0u, 2u, 0u, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}
