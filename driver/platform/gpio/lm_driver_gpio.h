/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_driver_gpio.h
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#ifndef __LM_DRIVER_GPIO_H__
#define __LM_DRIVER_GPIO_H__

#include "lm_types.h"

/*******************************************************************************
* Description   : 外部函数声明区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_gpio_rcc_set()
* Description   : 设置GPIO端口时钟  eg: lm_gpio_rcc_set("PD3", 1)
* EntryParam    : name,IO名称    value,   0:失能     1:使能
* ReturnValue   : None
*******************************************************************************/
extern void lm_gpio_rcc_set(const char *name, uint8_t value);

/*******************************************************************************
* FunName       : lm_gpio_pin_set()
* Description   : 设置GPIO端口电平  eg: lm_gpio_pin_set("PD3", 0)
* EntryParam    : name,IO名称, value,   0:输出低电平     1:输出高电平  输出默认推挽
* ReturnValue   : None
*******************************************************************************/
extern void lm_gpio_pin_set(const char *name, uint8_t value);

/*******************************************************************************
* FunName       : lm_gpio_pin_get()
* Description   : 读取GPIO端口电平  eg: lm_gpio_pin_get("PD3")
* EntryParam    : name,IO名称   输入默认上拉
* ReturnValue   : 端口有效电平
*******************************************************************************/
extern int8_t lm_gpio_pin_get(const char *name);

#endif

/* end of file */
