/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_driver_uart.h
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#ifndef __LM_DRIVER_UART_H__
#define __LM_DRIVER_UART_H__

#include "stm32f4xx.h"
#include "lm_types.h"

/*******************************************************************************
* Description   : 宏定义区
*******************************************************************************/
#define USART1_IRQ_EN           0                       /* 串口1使能开关 */
#define USART2_IRQ_EN           0                       /* 串口2使能开关 */
#define USART3_IRQ_EN           0                       /* 串口3使能开关 */

#define lm_uart_msp_init        HAL_UART_MspInit        /* 串口底层初始化 */
#define lm_uart_rx_callback     HAL_UART_RxCpltCallback /* 串口接收回调 */

#define lm_uart1_irq_handler    USART1_IRQHandler       /* 串口1中断 */
#define lm_uart2_irq_handler    USART2_IRQHandler       /* 串口2中断 */
#define lm_uart3_irq_handler    USART3_IRQHandler       /* 串口3中断 */

#define HAL_RX_BUF_SIZE         1                       /* HAL接收缓存大小 */
#define UART_RX_MAX_LEN         1024                    /* 串口接收缓存大小 */

#define UART1                   USART1                  /* 串口1端口映射 */
#define UART2                   USART2                  /* 串口2端口映射 */
#define UART3                   USART3                  /* 串口3端口映射 */

#define UART1_BOUND             115200                  /* 串口1波特率 */
#define UART2_BOUND             115200                  /* 串口2波特率 */
#define UART3_BOUND             115200                  /* 串口3波特率 */

/*******************************************************************************
* Description   : 外部函数声明区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_uart_para_set()
* Description   : 设置UART参数
* EntryParam    : port,端口号   bound,波特率
* ReturnValue   : None
*******************************************************************************/
extern void lm_uart_para_set(USART_TypeDef *port, uint32_t bound);

#endif

/* end of file */
