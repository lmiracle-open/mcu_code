/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_driver_led.c
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#include "lm_driver_led.h"
#include "lm_driver_gpio.h"
#include "lm_error.h"
#include "lm_app_config.h"
#include "lm_driver_config.h"

#include "lm_driver.h"

/*******************************************************************************
* Description   : 模块内部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_led_init()
* Description   : LED初始化
* EntryParam    : None
* ReturnValue   : 错误码
*******************************************************************************/
static int8_t lm_led_init(void)
{
    /* 1.开启LED外设时钟 */
    lm_gpio_rcc_set(LED1, EN_SWITCH);
    lm_gpio_rcc_set(LED2, EN_SWITCH);
    lm_gpio_rcc_set(LED3, EN_SWITCH);

    /* 2.关闭LED */
    lm_gpio_pin_set(LED1, LED_OFF);
    lm_gpio_pin_set(LED2, LED_OFF);
    lm_gpio_pin_set(LED3, LED_OFF);

    return LM_ERR_SUCCESS;
}

/*******************************************************************************
* Description   : 注册LED初始化模块
*******************************************************************************/
LM_DRIVER_INIT(lm_led_init);

/* end of file */
