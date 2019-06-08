/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_driver.h
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#ifndef __LM_DRIVER_H__
#define __LM_DRIVER_H__

#include "lm_types.h"

/*******************************************************************************
* Description   : 结构体定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_driver_cb()
* Description   : 驱动初始化回调函数类型
* EntryParam    : None
* ReturnValue   : 错误码
*******************************************************************************/
typedef int8_t (*lm_driver_cb)(void);

struct driver_init {
    const lm_driver_cb driver_init;             /* 初始化回调  */
};

typedef struct driver_init DRIVER_INIT;         /* 定义结构体类型  */
typedef DRIVER_INIT *PDRIVER_INIT;              /* 定义结构体指针类型  */

/*******************************************************************************
* Description   : 宏定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : LM_DRIVER_INIT()
* Description   : 驱动初始化注册函数
* EntryParam    : 初始化函数
* ReturnValue   : None
*******************************************************************************/
#define LM_DRIVER_INIT(fun)  \
    static const DRIVER_INIT \
    __attribute__((unused)) __lm_driver_init_##fun##__ = {fun};  \
    static const PDRIVER_INIT    \
    __attribute__((unused, section(".lm_driver_init")))  \
    __lm_driver_init_##fun##_point__ = &__lm_driver_init_##fun##__

/*******************************************************************************
* Description   : 外部函数声明区
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* FunName       : lm_driver_all_init()
* Description   : 初始化所有驱动
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
extern void lm_driver_all_init(void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
