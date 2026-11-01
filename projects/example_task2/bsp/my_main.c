#include "my_main.h"
#include "includes.h"

#define LED1_PIN            GPIO_PIN_5
#define LED1_PORT           GPIOA
#define LED2_PIN            GPIO_PIN_6
#define LED2_PORT           GPIOA

static OS_TCB      Led1TCB;
static OS_TCB      Led2TCB;
static OS_TCB      Aht20TCB;

static CPU_STK     Led1Stk[APP_CFG_TASK_STK_SIZE];
static CPU_STK     Led2Stk[APP_CFG_TASK_STK_SIZE];
static CPU_STK     Aht20Stk[APP_CFG_AHT20_STK_SIZE];

static void led1_task(void *p_arg);
static void led2_task(void *p_arg);
static void aht20_task(void *p_arg);

// 由 main() 调用：初始化 uC/OS-III、创建 3 个任务并启动调度器 
void setup(void)
{
    OS_ERR err;

    OSInit(&err);

    OSTaskCreate(&Led1TCB, "led1", led1_task, (void *)0,APP_CFG_TASK_LED1_PRIO,&Led1Stk[0], APP_CFG_TASK_STK_SIZE / 10u, APP_CFG_TASK_STK_SIZE,0u, 0u, (void *)0,OS_OPT_TASK_STK_CLR, &err);

    OSTaskCreate(&Led2TCB, "led2", led2_task, (void *)0,APP_CFG_TASK_LED2_PRIO,&Led2Stk[0], APP_CFG_TASK_STK_SIZE / 10u, APP_CFG_TASK_STK_SIZE,0u, 0u, (void *)0, OS_OPT_TASK_STK_CLR, &err);

    OSTaskCreate(&Aht20TCB, "aht20", aht20_task, (void *)0, APP_CFG_TASK_AHT20_PRIO, &Aht20Stk[0], APP_CFG_AHT20_STK_SIZE / 10u, APP_CFG_AHT20_STK_SIZE,0u, 0u, (void *)0,OS_OPT_TASK_STK_CLR, &err);

    OSStart(&err);              // 不返回 
}

void loop(void)
{
}

/* 任务 1：每 1 秒翻转一次 LED1 */
static void led1_task(void *p_arg)
{
    OS_ERR err;

    (void)p_arg;
    OS_CPU_SysTickInitFreq(SystemCoreClock);

    for (;;) {
        HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
        OSTimeDlyHMSM(0u, 0u, 1u, 0u, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

/* 任务 2：每 3 秒翻转一次 LED2 */
static void led2_task(void *p_arg)
{
    OS_ERR err;

    (void)p_arg;

    for (;;) {
        HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN);
        OSTimeDlyHMSM(0u, 0u, 3u, 0u, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

/* 任务 3：每 2 秒采集一次 AHT20 并通过 USART1 发送温湿度 */
static void aht20_task(void *p_arg)
{
    char    msg[64];
    int32_t temp_x10, humi_x10, temp_abs;
    OS_ERR  err;

    (void)p_arg;
    AHT20_Init();

    for (;;) {
        AHT20_Read(&temp_x10, &humi_x10);

        temp_abs = (temp_x10 < 0) ? -temp_x10 : temp_x10;
        sprintf(msg, "T=%s%ld.%ld C, H=%ld.%ld %%RH\r\n",
                (temp_x10 < 0) ? "-" : "",
                (long)(temp_abs / 10), (long)(temp_abs % 10),
                (long)(humi_x10 / 10), (long)(humi_x10 % 10));

        HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), 1000u);
        OSTimeDlyHMSM(0u, 0u, 2u, 0u, OS_OPT_TIME_PERIODIC, &err);
    }
}
