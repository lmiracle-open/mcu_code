/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_driver_led.h
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#ifndef __LM_DRIVER_LED_H__
#define __LM_DRIVER_LED_H__

#include "lm_types.h"

/*******************************************************************************
* Description    : 宏定义区
*******************************************************************************/
#define LED_ON                  0                   /* LED点亮-低电平 */
#define LED_OFF                 1                   /* LED熄灭-高电平 */

#define LED1                    "PD3"               /* LED1端口 */
#define LED2                    "PD4"               /* LED2端口 */
#define LED3                    "PD7"               /* LED3端口 */

#define LED1_ON         lm_gpio_pin_set(LED1, LED_ON)
#define LED1_OFF        lm_gpio_pin_set(LED1, LED_OFF)
#define LED2_ON         lm_gpio_pin_set(LED2, LED_ON)
#define LED2_OFF        lm_gpio_pin_set(LED2, LED_OFF)
#define LED3_ON         lm_gpio_pin_set(LED3, LED_ON)
#define LED3_OFF        lm_gpio_pin_set(LED3, LED_OFF)

#endif

/* end of file */
