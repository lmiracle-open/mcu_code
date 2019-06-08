/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_driver.c
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#include "lm_driver.h"
#include "lm_error.h"

/*******************************************************************************
* Description   : 外部变量声明区
*******************************************************************************/
extern PDRIVER_INIT LM_DRIVER_INIT_START[];  /* 驱动初始化起始地址 */
extern PDRIVER_INIT LM_DRIVER_INIT_END[];    /* 驱动初始化结束地址 */

/*******************************************************************************
* Description   : 外部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_driver_all_init()
* Description   : 初始化所有驱动
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
void lm_driver_all_init(void)
{
    uint32_t total = 0;
    uint32_t failed = 0;

    PDRIVER_INIT *init = NULL;

    /* 1.初始化所有驱动 */
    for (init = LM_DRIVER_INIT_START; init < LM_DRIVER_INIT_END; ) {
        if (NULL != (*init)->driver_init) {
            total++;
            if (LM_ERR_SUCCESS != ((*init)->driver_init)()) {
                failed++;
            }
        }
    }

    /* 2.打印初始化统计信息 */

}

/* end of file */
