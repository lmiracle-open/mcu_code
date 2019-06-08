/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_driver_rs232.c
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#include "lm_driver_rs232.h"
#include "lm_driver_uart.h"
#include "lm_error.h"
#include "lm_app_config.h"
#include "lm_driver_config.h"

#include "lm_driver.h"

/*******************************************************************************
* Description   : 模块内部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_uart_init()
* Description   : UART初始化
* EntryParam    : None
* ReturnValue   : 错误码
*******************************************************************************/
static int8_t lm_uart_init(void)
{
    /* 1.设置uart参数 */
    lm_uart_para_set(UART1, UART1_BOUND);
    lm_uart_para_set(UART2, UART2_BOUND);
    lm_uart_para_set(UART3, UART3_BOUND);

    return LM_ERR_SUCCESS;
}

/*******************************************************************************
* Description   : 注册UART初始化模块
*******************************************************************************/
LM_DRIVER_INIT(lm_uart_init);

/* end of file */
