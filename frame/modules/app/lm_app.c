/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_app.c
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#include "lm_app.h"
#include "lm_error.h"

/*******************************************************************************
* Description   : 外部变量声明区
*******************************************************************************/
extern PAPP_INIT LM_APP_INIT_START[];    /* 应用程序初始化起始地址 */
extern PAPP_INIT LM_APP_INIT_END[];      /* 应用程序初始化结束地址 */

extern PAPP_TASK LM_APP_TASK_1S_START[]; /* 应用程序1s任务起始地址 */
extern PAPP_TASK LM_APP_TASK_1S_END[];   /* 应用程序1s任务结束地址 */

extern PAPP_TASK LM_APP_TASK_2S_START[]; /* 应用程序2s任务起始地址 */
extern PAPP_TASK LM_APP_TASK_2S_END[];   /* 应用程序2s任务结束地址 */

extern PAPP_TASK LM_APP_TASK_3S_START[]; /* 应用程序3s任务起始地址 */
extern PAPP_TASK LM_APP_TASK_3S_END[];   /* 应用程序3s任务结束地址 */

/*******************************************************************************
* Description   : 外部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_app_all_init()
* Description   : 应用程序初始化模块
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
void lm_app_all_init(void)
{
    uint32_t total = 0;
    uint32_t failed = 0;

    PAPP_INIT *init = NULL;

    /* 1.初始化所有应用程序 */
    for (init = LM_APP_INIT_START; init < LM_APP_INIT_END; init++) {
        if (NULL != (*init)->app_init) {
            total++;
            if (LM_ERR_SUCCESS != ((*init)->app_init)()) {
                failed++;
            }
        }
    }

    /* 2.打印初始化统计信息 */

}

/*******************************************************************************
* FunName       : lm_app_task_1s()
* Description   : 1s应用程序任务
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
void lm_app_task_1s(void)
{
    PAPP_TASK *task = NULL;

    /* 1.遍历所有1s应用程序 */
    for (task = LM_APP_TASK_1S_START; task < LM_APP_TASK_1S_END; task++) {
        if (NULL != (*task)->app_task) {
            ((*task)->app_task)();
        }
    }
}

/*******************************************************************************
* FunName       : lm_app_task_2s()
* Description   : 2s应用程序任务
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
void lm_app_task_2s(void)
{
    PAPP_TASK *task = NULL;

    /* 1.遍历所有2s应用程序 */
    for (task = LM_APP_TASK_2S_START; task < LM_APP_TASK_2S_END; task++) {
        if (NULL != (*task)->app_task) {
            ((*task)->app_task)();
        }
    }
}

/*******************************************************************************
* FunName       : lm_app_task_3s()
* Description   : 3s应用程序任务
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
void lm_app_task_3s(void)
{
    PAPP_TASK *task = NULL;

    /* 1.遍历所有3s应用程序 */
    for (task = LM_APP_TASK_3S_START; task < LM_APP_TASK_3S_END; task++) {
        if (NULL != (*task)->app_task) {
            ((*task)->app_task)();
        }
    }
}

/* end of file */
