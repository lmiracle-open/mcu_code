/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_stdio.h
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#ifndef __LM_STDIO_H__
#define __LM_STDIO_H__

#include "lm_types.h"
#include "lm_driver_uart.h"

/*******************************************************************************
* Description    : 宏定义区
*******************************************************************************/
#define STDIO_OUT_SIZE              200                 /* 标准输出缓冲区SIZE */

#define STDIO_OUTPUT(data, len) \
        lm_uart_send(UART3, buf, strlen((void *)buf));  /* 重定向 */

/*******************************************************************************
* Description   : 外部函数声明区
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* FunName       : lm_kprintf()
* Description   : 格式化输出
* EntryParam    : format,格式化字符串, ...,可变参数
* ReturnValue   : None
*******************************************************************************/
extern void lm_kprintf(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
