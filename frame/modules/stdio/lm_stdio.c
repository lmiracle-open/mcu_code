/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_stdio.c
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#include "lm_stdio.h"
#include "lm_error.h"

#include <rtthread.h>

/*******************************************************************************
* Description   : 外部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_output()
* Description   : 格式化输出
* EntryParam    : format,格式化字符串, ...,可变参数
* ReturnValue   : None
*******************************************************************************/
void lm_output(const char *format, ...)
{
    va_list va;

    uint8_t buf[STDIO_OUT_SIZE] = {0};

    /* 1.格式化数据 */
    va_start(va, format);

    rt_vsnprintf((void *)buf, STDIO_OUT_SIZE, format, va);

    va_end(va);

    /* 2.输出数据 */
    STDIO_OUTPUT(buf, strlen((void *)buf));
}

/* end of file */
