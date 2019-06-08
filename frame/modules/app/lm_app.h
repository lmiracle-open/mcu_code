/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_app.h
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#ifndef __LM_APP_H__
#define __LM_APP_H__

#include "lm_types.h"

/*******************************************************************************
* Description   : 结构体定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_app_cb()
* Description   : 应用程序回调函数类型
* EntryParam    : None
* ReturnValue   : 错误码
*******************************************************************************/
typedef int8_t (*lm_app_cb)(void);

struct app_init {
    const lm_app_cb app_init;               /* 初始化回调  */
};

typedef struct app_init APP_INIT;           /* 定义结构体类型  */
typedef APP_INIT *PAPP_INIT;                /* 定义结构体指针类型  */

struct app_task {
    const lm_app_cb app_task;               /* 应用程序回调  */
    const char *name;                       /* 应用程序名字 */
};

typedef struct app_task APP_TASK;           /* 定义结构体类型  */
typedef APP_TASK *PAPP_TASK;                /* 定义结构体指针类型  */

/*******************************************************************************
* Description   : 宏定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : LM_DRIVER_INIT()
* Description   : 应用程序初始化注册函数
* EntryParam    : 初始化函数
* ReturnValue   : None
*******************************************************************************/
#define LM_APP_INIT(fun)  \
    static const APP_INIT \
    __attribute__((unused)) __lm_app_init_##fun##__ = {fun};  \
    static const PAPP_INIT    \
    __attribute__((unused, section(".lm_app_init")))  \
    __lm_app_init_##fun##_point__ = &__lm_app_init_##fun##__

/*******************************************************************************
* FunName       : LM_APP_TASK_1S()
* Description   : 应用程序1s任务注册函数
* EntryParam    : fun,应用程序入口函数
* ReturnValue   : None
*******************************************************************************/
#define LM_APP_TASK_1S(fun)  \
    static const APP_TASK \
    __attribute__((unused)) __lm_app_task_1s_##fun##__ = {fun, #fun};  \
    static const PAPP_TASK    \
    __attribute__((unused, section(".lm_app_task_1s")))  \
    __lm_app_task_1s_##fun##_point__ = &__lm_app_task_1s_##fun##__

/*******************************************************************************
* FunName       : LM_APP_TASK_2S()
* Description   : 应用程序2s任务注册函数
* EntryParam    : fun,应用程序入口函数
* ReturnValue   : None
*******************************************************************************/
#define LM_APP_TASK_2S(fun)  \
    static const APP_TASK \
    __attribute__((unused)) __lm_app_task_2s_##fun##__ = {fun, #fun};  \
    static const PAPP_TASK    \
    __attribute__((unused, section(".lm_app_task_2s")))  \
    __lm_app_task_2s_##fun##_point__ = &__lm_app_task_2s_##fun##__

/*******************************************************************************
* FunName       : LM_APP_TASK_3S()
* Description   : 应用程序3s任务注册函数
* EntryParam    : fun,应用程序入口函数
* ReturnValue   : None
*******************************************************************************/
#define LM_APP_TASK_3S(fun)  \
    static const APP_TASK \
    __attribute__((unused)) __lm_app_task_3s_##fun##__ = {fun, #fun};  \
    static const PAPP_TASK    \
    __attribute__((unused, section(".lm_app_task_3s")))  \
    __lm_app_task_3s_##fun##_point__ = &__lm_app_task_3s_##fun##__

/*******************************************************************************
* Description   : 外部函数声明区
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* FunName       : lm_app_all_init()
* Description   : 初始化所有应用程序
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
extern void lm_app_all_init(void);

/*******************************************************************************
* FunName       : lm_app_task_1s()
* Description   : 1s应用程序任务
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
extern void lm_app_task_1s(void);

/*******************************************************************************
* FunName       : lm_app_task_2s()
* Description   : 2s应用程序任务
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
extern void lm_app_task_2s(void);

/*******************************************************************************
* FunName       : lm_app_task_3s()
* Description   : 3s应用程序任务
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
extern void lm_app_task_3s(void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
