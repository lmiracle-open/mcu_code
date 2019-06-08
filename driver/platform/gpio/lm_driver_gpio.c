/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_driver_gpio.c
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#include "stm32f4xx.h"
#include "lm_driver_gpio.h"
#include "lm_error.h"

/*******************************************************************************
* Description   : 模块内部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_gpio_para_set()
* Description   : 设置GPIO端口参数
* EntryParam    : port,GPIO端口, pin,端口引脚编号, mode,模式
* ReturnValue   : None
*******************************************************************************/
static void lm_gpio_para_set(GPIO_TypeDef *port, uint16_t pin, uint32_t mode)
{
    GPIO_InitTypeDef GPIO_Initure;

    /* 1.设置GPIO参数 */
    GPIO_Initure.Pin = pin;
    GPIO_Initure.Mode = mode;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;

    /* 2.初始化参数配置 */
    HAL_GPIO_Init(port, &GPIO_Initure);
}

/*******************************************************************************
* Description   : 外部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_gpio_rcc_set()
* Description   : 设置GPIO端口时钟  eg: lm_gpio_rcc_set("PD3", 1)
* EntryParam    : name,IO名称    value,   0:失能     1:使能
* ReturnValue   : None
*******************************************************************************/
void lm_gpio_rcc_set(const char *name, uint8_t value)
{
    /* 1.GPIO参数检查 */
    if (unlikely(name[0] != 'P')) {
        return ;
    }

    /* 2.获取GPIO口 设置时钟 */
    switch (name[1]) {
    case 'A':
        if (value) {
            __HAL_RCC_GPIOA_CLK_ENABLE();
        } else {
            __HAL_RCC_GPIOA_CLK_DISABLE();
        }
        break;
    case 'B':
        if (value) {
            __HAL_RCC_GPIOB_CLK_ENABLE();
        } else {
            __HAL_RCC_GPIOB_CLK_DISABLE();
        }
        break;
    case 'C':
        if (value) {
            __HAL_RCC_GPIOC_CLK_ENABLE();
        } else {
            __HAL_RCC_GPIOC_CLK_DISABLE();
        }
        break;
    case 'D':
        if (value) {
            __HAL_RCC_GPIOD_CLK_ENABLE();
        } else {
            __HAL_RCC_GPIOD_CLK_DISABLE();
        }
        break;
    case 'E':
        if (value) {
            __HAL_RCC_GPIOE_CLK_ENABLE();
        } else {
            __HAL_RCC_GPIOE_CLK_DISABLE();
        }
        break;
    default :
        /* STM32F407VE 最大到E >E的GPIO此版本不支持 */
        return ;
        break;
    }
}

/*******************************************************************************
* FunName       : lm_gpio_pin_set()
* Description   : 设置GPIO端口电平  eg: lm_gpio_pin_set("PD3", 0)
* EntryParam    : name,IO名称, value,   0:输出低电平     1:输出高电平  输出默认推挽
* ReturnValue   : None
*******************************************************************************/
void lm_gpio_pin_set(const char *name, uint8_t value)
{
    uint16_t io_pin = 0;                /* 保存pin脚地址 */
    GPIO_TypeDef *port = NULL;          /* 保存IO地址 */

    /* 1.GPIO参数检查 */
    if (unlikely(name[0] != 'P')) {
        return ;
    }

    /* 2.计算pin脚地址 */
    io_pin = atoi(name+2);
    io_pin = 1 << io_pin;

    /* 3.pin脚有效值检测 */
    if (unlikely(io_pin >= GPIO_PIN_All)) {
        return ;
    }

    /* 4.取出GPIO端口 */
    switch (name[1]) {
    case 'A':
        port = GPIOA;
        break;
    case 'B':
        port = GPIOB;
        break;
    case 'C':
        port = GPIOC;
        break;
    case 'D':
        port = GPIOD;
        break;
    case 'E':
        port = GPIOE;
        break;
    default :
        /* STM32F407VE 最大到E >E的GPIO此版本不支持 */
        return ;
        break;
    }

    /* 5.设置GPIO端口参数 默认为推挽输出 */
    lm_gpio_para_set(port, io_pin, GPIO_MODE_OUTPUT_PP);

    /* 6.设置GPIO_pin电平 */
    HAL_GPIO_WritePin(port, io_pin, value);
}

/*******************************************************************************
* FunName       : lm_gpio_pin_get()
* Description   : 读取GPIO端口电平  eg: lm_gpio_pin_get("PD3")
* EntryParam    : name,IO名称   输入默认上拉
* ReturnValue   : 端口有效电平
*******************************************************************************/
int8_t lm_gpio_pin_get(const char *name)
{
    uint16_t io_pin = 0;                /* 保存pin脚地址 */
    GPIO_TypeDef *port = NULL;          /* 保存IO地址 */

    /* 1.参数检查 */
    if (unlikely(name[0] != 'P')) {
        return LM_ERR_FAILED;
    }

    /* 2.计算pin脚地址 */
    io_pin = atoi(name+2);
    io_pin = 1 << io_pin;

    /* 3.pin脚有效值检测 */
    if (unlikely(io_pin >= GPIO_PIN_All)) {
        return LM_ERR_FAILED;
    }

    /* 4.取出GPIO端口 */
    switch (name[1]) {
    case 'A':
        port = GPIOA;
        break;
    case 'B':
        port = GPIOB;
        break;
    case 'C':
        port = GPIOC;
        break;
    case 'D':
        port = GPIOD;
        break;
    case 'E':
        port = GPIOE;
        break;
    default :
        /* STM32F407VE 最大到E >E的GPIO此版本不支持 */
        return LM_ERR_FAILED;
        break;
    }

    /* 5.设置GPIO端口参数 默认为上拉输入 */
    lm_gpio_para_set(port, io_pin, GPIO_MODE_INPUT);

    /* 6.读取端口值  */
    return (HAL_GPIO_ReadPin(port, io_pin) != 0 ? 1 : 0);
}

/* end of file */
