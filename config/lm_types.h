/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_types.h
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#ifndef __LM_TYPES_H__
#define __LM_TYPES_H__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

/*******************************************************************************
* Description   : 宏定义区
*******************************************************************************/

#define likely(exp)         __builtin_expect(!!(exp), 1)    /* 期望位真 */
#define unlikely(Exp)       __builtin_expect(!!(Exp), 0)    /* 期望为假 */

#define ARRAY_LEN(x)        (sizeof(x) / sizeof((x)[0]))    /* 获取一个数组元素个数 */

#endif

/* end of file */
