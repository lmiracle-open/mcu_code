/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : main.c
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#include <rtthread.h>

#include "lm_app_config.h"
#include "lm_driver.h"
#include "lm_app.h"

/*******************************************************************************
* Description    : 宏定义区
*******************************************************************************/
#define LM_THREAD_1s_PRIO                   3               /* 线程1优先级 */
#define LM_THREAD_1s_TICK                   20              /* 线程1时间片 */

#define LM_THREAD_2s_PRIO                   4               /* 线程2优先级 */
#define LM_THREAD_2s_TICK                   20              /* 线程2时间片 */

#define LM_THREAD_3s_PRIO                   5               /* 线程3优先级 */
#define LM_THREAD_3s_TICK                   20              /* 线程3时间片 */

/*******************************************************************************
* Description    : 模块内部变量定义区
*******************************************************************************/
static struct rt_thread lm_thread_1s;                       /* 线程1控制块 */
static rt_uint8_t lm_thread_1s_stack[1024];                 /* 线程1栈内存 */

static struct rt_thread lm_thread_2s;                       /* 线程2控制块 */
static rt_uint8_t lm_thread_2s_stack[1024];                 /* 线程2栈内存 */

static struct rt_thread lm_thread_3s;                       /* 线程3控制块 */
static rt_uint8_t lm_thread_3s_stack[1024];                 /* 线程3栈内存 */

/*******************************************************************************
* Description    : 模块内部函数声明区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_logo_show()
* Description   : 蓝梦平台信息展示
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
static void lm_logo_show(void);

/*******************************************************************************
* FunName       : lm_thread_1s_entry()
* Description   : 用户线程1-->1s运行一次
* EntryParam    : parameter,线程参数
* ReturnValue   : None
*******************************************************************************/
static void lm_thread_1s_entry(void* parameter);            /* 线程1函数体 */

/*******************************************************************************
* FunName       : lm_thread_2s_entry()
* Description   : 用户线程2-->2s运行一次
* EntryParam    : parameter,线程参数
* ReturnValue   : None
*******************************************************************************/
static void lm_thread_2s_entry(void* parameter);            /* 线程2函数体 */

/*******************************************************************************
* FunName       : lm_thread_3s_entry()
* Description   : 用户线程3-->3s运行一次
* EntryParam    : parameter,线程参数
* ReturnValue   : None
*******************************************************************************/
static void lm_thread_3s_entry(void* parameter);            /* 线程3函数体 */

/*******************************************************************************
* Description    : 模块内部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_logo_show()
* Description   : 蓝梦平台信息展示
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
static void lm_logo_show(void)
{
    /* 1.硬件版本 */

    /* 2.软件版本 */

    return ;
}

/*******************************************************************************
* FunName       : lm_thread_1s_entry()
* Description   : 用户线程1-->1s运行一次
* EntryParam    : parameter,线程参数
* ReturnValue   : None
*******************************************************************************/
static void lm_thread_1s_entry(void *parameter)
{
    (void)parameter;

    /* 1.1s轮训一次任务 */
    while (1) {
        lm_app_task_1s();
        lm_delay_ms(1000);
    }
}

/*******************************************************************************
* FunName       : lm_thread_2s_entry()
* Description   : 用户线程2-->2s运行一次
* EntryParam    : parameter,线程参数
* ReturnValue   : None
*******************************************************************************/
static void lm_thread_2s_entry(void *parameter)
{
    (void)parameter;

    /* 1.2s轮训一次任务 */
    while (1) {
        lm_app_task_2s();
        lm_delay_ms(2000);
    }
}

/*******************************************************************************
* FunName       : lm_thread_3s_entry()
* Description   : 用户线程3-->3s运行一次
* EntryParam    : parameter,线程参数
* ReturnValue   : None
*******************************************************************************/
static void lm_thread_3s_entry(void *parameter)
{
    (void)parameter;

    /* 1.3s轮训一次任务 */
    while (1) {
        lm_app_task_3s();
        lm_delay_ms(3000);
    }
}

/*******************************************************************************
* FunName       : lm_app_start()
* Description   : 用户程序启动
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
static void lm_app_start(void)
{
    rt_err_t result;

    /* 1.初始化驱动模块 */
    lm_driver_all_init();

    /* 2.初始化应用程序 */
    lm_app_all_init();

    /* 3.显示用户logo */
    lm_logo_show();

    /* 4.创建子线程1 */
    result = rt_thread_init(&lm_thread_1s,\
                            "thread1s",\
                            lm_thread_1s_entry,\
                            RT_NULL,\
                            &lm_thread_1s_stack[0],\
                            sizeof(lm_thread_1s_stack),\
                            LM_THREAD_1s_PRIO,\
                            LM_THREAD_1s_TICK);
    if (result == RT_EOK) {
        rt_thread_startup(&lm_thread_1s);
    } else {
        /* thread1s start fail */
    }

    /* 5.创建子线程2 */
    result = rt_thread_init(&lm_thread_2s,\
                            "thread2s",\
                            lm_thread_2s_entry,\
                            RT_NULL,\
                            &lm_thread_2s_stack[0],\
                            sizeof(lm_thread_2s_stack),\
                            LM_THREAD_2s_PRIO,\
                            LM_THREAD_2s_TICK);
    if (result == RT_EOK) {
        rt_thread_startup(&lm_thread_2s);
    } else {
        /* thread2s start fail */
    }

    /* 6.创建子线程3 */
    result = rt_thread_init(&lm_thread_3s,\
                            "thread3s",\
                            lm_thread_3s_entry,\
                            RT_NULL,\
                            &lm_thread_3s_stack[0],\
                            sizeof(lm_thread_3s_stack),\
                            LM_THREAD_3s_PRIO,\
                            LM_THREAD_3s_TICK);
    if (result == RT_EOK) {
        rt_thread_startup(&lm_thread_3s);
    } else {
        /* thread3s start fail */
    }
}

/*******************************************************************************
* FunName       : main()
* Description   : 程序入口
* EntryParam    : None
* ReturnValue   : 错误码
*******************************************************************************/
int main(void)
{
    /* 1.启动用户程序 */
    lm_app_start();

    return -1;
}

/* end of file */
