/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_test_shell.c
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#include "lm_driver_led.h"
#include "lm_error.h"
#include "lm_app_config.h"

#include <finsh.h>

/*******************************************************************************
* Description   : 模块内部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_test_shell()
* Description   : shell测试
* EntryParam    : value,控制命令
* ReturnValue   : None
*******************************************************************************/
static void lm_test_shell(int8_t value)
{
    switch (value) {
    case 0:
        LED3_ON;
        break;
    case 1:
        LED3_OFF;
        break;
    default :
        break;
    }
}

/*******************************************************************************
* Description   : 注册shell命令
*******************************************************************************/
FINSH_FUNCTION_EXPORT(lm_test_shell, test shell on or off led)

/* end of file */
