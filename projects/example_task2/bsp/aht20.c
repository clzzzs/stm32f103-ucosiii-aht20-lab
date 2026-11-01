#include "aht20.h"

#define AHT20_ADDR_W      0x70u
#define AHT20_ADDR_R      0x71u

#define SCL_PORT          GPIOB
#define SCL_PIN           GPIO_PIN_6
#define SDA_PORT          GPIOB
#define SDA_PIN           GPIO_PIN_7

volatile uint8_t g_i2c_scl;
volatile uint8_t g_i2c_sda;


static void SCL_H(void)
{
    HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_SET);
    g_i2c_scl = 1;
}

static void SCL_L(void)
{
    HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_RESET);
    g_i2c_scl = 0;
}

static void SDA_H(void)
{
    HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_SET);
    g_i2c_sda = 1;
}

static void SDA_L(void)
{
    HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_RESET);
    g_i2c_sda = 0;
}

static uint8_t SDA_READ(void)
{
    uint8_t v = HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN);
    g_i2c_sda = v;
    return v;
}

static void I2C_Delay(void)
{
    for (volatile uint32_t i = 0; i < 40u; i++) {
        __NOP();
    }
}

static void I2C_Start(void)
{
    SDA_H();
    SCL_H();
    I2C_Delay();
    SDA_L();
    I2C_Delay();
    SCL_L();
    I2C_Delay();
}

static void I2C_Stop(void)
{
    SDA_L();
    SCL_H();
    I2C_Delay();
    SDA_H();
    I2C_Delay();
}

/* 返回 0 表示收到 ACK，1 表示 NACK；本实验不检查返回值 */
static uint8_t I2C_WriteByte(uint8_t byte)
{
    uint8_t i, ack;

    for (i = 0; i < 8u; i++) {
        SCL_L();
        I2C_Delay();
        if (byte & 0x80u) {
            SDA_H();
        } else {
            SDA_L();
        }
        I2C_Delay();
        SCL_H();
        I2C_Delay();
        byte <<= 1;
    }

    SCL_L();
    I2C_Delay();
    SDA_H();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    ack = SDA_READ();
    SCL_L();
    I2C_Delay();

    return ack;
}

static uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t i, byte = 0u;

    SDA_H();
    for (i = 0; i < 8u; i++) {
        SCL_L();
        I2C_Delay();
        SCL_H();
        I2C_Delay();
        byte = (uint8_t)((byte << 1) | SDA_READ());
        SCL_L();
        I2C_Delay();
    }

    if (ack) {
        SDA_L();
    } else {
        SDA_H();
    }
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SCL_L();
    I2C_Delay();
    SDA_H();

    return byte;
}

void AHT20_Init(void)
{
    HAL_Delay(100);

    I2C_Start();
    I2C_WriteByte(AHT20_ADDR_W);
    I2C_WriteByte(0xBEu);       /* 初始化命令 */
    I2C_WriteByte(0x08u);       /* 校准使能 */
    I2C_WriteByte(0x00u);
    I2C_Stop();

    HAL_Delay(10);
}

void AHT20_Read(int32_t *temp_x10, int32_t *humi_x10)
{
    uint8_t  buf[7];
    uint32_t raw_h, raw_t;
    uint8_t  i;

    /* 触发测量：0xAC 0x33 0x00 */
    I2C_Start();
    I2C_WriteByte(AHT20_ADDR_W);
    I2C_WriteByte(0xACu);
    I2C_WriteByte(0x33u);
    I2C_WriteByte(0x00u);
    I2C_Stop();

    HAL_Delay(80);              /* 等待转换完成 */

    /* 读 7 字节：状态 + 湿度20位 + 温度20位 + CRC */
    I2C_Start();
    I2C_WriteByte(AHT20_ADDR_R);
    for (i = 0; i < 6u; i++) {
        buf[i] = I2C_ReadByte(1u);
    }
    buf[6] = I2C_ReadByte(0u);
    I2C_Stop();

    raw_h = ((uint32_t)buf[1] << 12) | ((uint32_t)buf[2] << 4) | (buf[3] >> 4);
    raw_t = (((uint32_t)buf[3] & 0x0Fu) << 16) | ((uint32_t)buf[4] << 8) | buf[5];

    /* 湿度 = raw_h / 2^20 * 100%，温度 = raw_t / 2^20 * 200 - 50 */
    *humi_x10 = (int32_t)((raw_h * 1000u) / 1048576u);
    *temp_x10 = (int32_t)((raw_t * 2000u) / 1048576u) - 500;
}


