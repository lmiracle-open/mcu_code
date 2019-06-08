/********************************* Copyright(c) ********************************
*
*                          LANMENG Scientific Creation
*                          https: //www.lmiracle.com
*
* File Name     : lm_driver_uart.c
* Change Logs   :
* Date         Author      Notes
* 2019-06-07   terryall    V1.0    first version
*******************************************************************************/

/*******************************************************************************
* Description   : 文件包含区
*******************************************************************************/
#include "lm_driver_uart.h"
#include "lm_error.h"

/*******************************************************************************
* Description   : 模块内部变量定义区
*******************************************************************************/
static UART_HandleTypeDef __g_uart_handler;             /* uart 句柄 */

#if USART1_IRQ_EN
static uint8_t __g_hal_u1_rx_buf[HAL_RX_BUF_SIZE];      /* hal串口1接收缓存 */
static uint8_t __g_u1_rx_buf[UART_RX_MAX_LEN];          /* 串口1接收缓存 */
static uint16_t __g_u1_rx_offset = 0;                   /* 串口1接收偏移 */
#endif

#if USART2_IRQ_EN
static uint8_t __g_hal_u2_rx_buf[HAL_RX_BUF_SIZE];      /* hal串口2接收缓存 */
static uint8_t __g_u2_rx_buf[UART_RX_MAX_LEN];          /* 串口2接收缓存 */
static uint16_t __g_u2_rx_offset = 0;                   /* 串口2接收偏移 */
#endif

#if USART3_IRQ_EN
static uint8_t __g_hal_u3_rx_buf[HAL_RX_BUF_SIZE];      /* hal串口3接收缓存 */
static uint8_t __g_u3_rx_buf[UART_RX_MAX_LEN];          /* 串口3接收缓存 */
static uint16_t __g_u3_rx_offset = 0;                   /* 串口3接收偏移 */
#endif

/*******************************************************************************
* Description   : 外部函数定义区
*******************************************************************************/

/*******************************************************************************
* FunName       : lm_uart_para_set()
* Description   : 设置UART参数
* EntryParam    : port,端口号   bound,波特率
* ReturnValue   : None
*******************************************************************************/
void lm_uart_para_set(USART_TypeDef *port, uint32_t bound)
{
    /* 1.设置UART参数 */
    __g_uart_handler.Instance = port;
    __g_uart_handler.Init.BaudRate = bound;
    __g_uart_handler.Init.WordLength = UART_WORDLENGTH_8B;
    __g_uart_handler.Init.Parity = UART_PARITY_NONE;
    __g_uart_handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    __g_uart_handler.Init.Mode = UART_MODE_TX_RX;

    /* 2.初始化参数配置 */
    HAL_UART_Init(&__g_uart_handler);

    /* 3.开启接收中断 */
#if USART1_IRQ_EN
    HAL_UART_Receive_IT(&__g_uart_handler, __g_hal_u1_rx_buf, HAL_RX_BUF_SIZE);
#endif

#if USART2_IRQ_EN
    HAL_UART_Receive_IT(&__g_uart_handler, __g_hal_u2_rx_buf, HAL_RX_BUF_SIZE);
#endif

#if USART3_IRQ_EN
    HAL_UART_Receive_IT(&__g_uart_handler, __g_hal_u3_rx_buf, HAL_RX_BUF_SIZE);
#endif
}

/*******************************************************************************
* FunName       : lm_uart_msp_init()
* Description   : UART底层初始化  此函数在HAL_UART_Init中调用
* EntryParam    : huart,串口句柄
* ReturnValue   : None
*******************************************************************************/
void lm_uart_msp_init(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_Initure;

    if (huart->Instance == USART1) {

        /* 1.开启外设时钟 */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();

        /* 2.GPIO参数配置 */
        GPIO_Initure.Pin = GPIO_PIN_9;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);

        GPIO_Initure.Pin = GPIO_PIN_10;
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);

        /* 3.使能中断 */
        #if USART1_IRQ_EN
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        HAL_NVIC_SetPriority(USART1_IRQn,3,3);
        #endif
    } else if (huart->Instance == USART2) {

        /* 1.开启外设时钟 */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART2_CLK_ENABLE();

        /* 2.GPIO参数配置 */
        GPIO_Initure.Pin = GPIO_PIN_2;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);

        GPIO_Initure.Pin = GPIO_PIN_3;
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);

        /* 3.使能中断 */
        #if USART2_IRQ_EN
        HAL_NVIC_EnableIRQ(USART2_IRQn);
        HAL_NVIC_SetPriority(USART2_IRQn,3,3);
        #endif
    } else if (huart->Instance == USART3) {

        /* 1.开启外设时钟 */
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_USART3_CLK_ENABLE();

        /* 2.GPIO参数配置 */
        GPIO_Initure.Pin = GPIO_PIN_10;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF7_USART3;
        HAL_GPIO_Init(GPIOB,&GPIO_Initure);

        GPIO_Initure.Pin = GPIO_PIN_11;
        HAL_GPIO_Init(GPIOB,&GPIO_Initure);

        /* 3.使能中断 */
        #if USART3_IRQ_EN
        HAL_NVIC_EnableIRQ(USART3_IRQn);
        HAL_NVIC_SetPriority(USART3_IRQn,3,3);
        #endif
    } else {
        /* 不处理 */
    }
}

/*******************************************************************************
* FunName       : lm_uart_rx_callback()
* Description   : UART接收回调  此函数在UART_Receive_IT中调用
* EntryParam    : huart,串口句柄
* ReturnValue   : None
*******************************************************************************/
void lm_uart_rx_callback(UART_HandleTypeDef *huart)
{
    if (USART1 == huart->Instance) {
        #if USART1_IRQ_EN
        __g_u1_rx_buf[__g_u1_rx_offset] = __g_hal_u1_rx_buf[0];
        __g_u1_rx_offset++;
        if (__g_u1_rx_offset > (UART_RX_MAX_LEN - 1)) {
            __g_u1_rx_offset = 0;
        }
        #endif
    } else if (USART2 == huart->Instance) {
        #if USART2_IRQ_EN
        __g_u2_rx_buf[__g_u2_rx_offset] = __g_hal_u2_rx_buf[0];
        __g_u2_rx_offset++;
        if (__g_u2_rx_offset > (UART_RX_MAX_LEN - 1)) {
            __g_u2_rx_offset = 0;
        }
        #endif
    } else if (USART3 == huart->Instance) {
        #if USART3_IRQ_EN
        __g_u3_rx_buf[__g_u3_rx_offset] = __g_hal_u3_rx_buf[0];
        __g_u3_rx_offset++;
        if (__g_u3_rx_offset > (UART_RX_MAX_LEN - 1)) {
            __g_u3_rx_offset = 0;
        }
        #endif
    } else {
        /* 不处理 */
    }
}

#if USART1_IRQ_EN

/*******************************************************************************
* FunName       : lm_uart1_irq_handler()
* Description   : UART1中断函数
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
void lm_uart1_irq_handler(void)
{
    uint32_t timeout = 0;

    /* enter interrupt */
    rt_interrupt_enter();

    HAL_UART_IRQHandler(&__g_uart_handler);

    timeout = 0;
    while (HAL_UART_GetState(&__g_uart_handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout>HAL_MAX_DELAY) break;
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&__g_uart_handler, \
           __g_hal_u1_rx_buf, HAL_RX_BUF_SIZE) != HAL_OK) {
        timeout++;
        if (timeout > HAL_MAX_DELAY) break;
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if USART2_IRQ_EN
/*******************************************************************************
* FunName       : lm_uart2_irq_handler()
* Description   : UART2中断函数
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
void lm_uart2_irq_handler(void)
{
    uint32_t timeout = 0;

    /* enter interrupt */
    rt_interrupt_enter();

    HAL_UART_IRQHandler(&__g_uart_handler);

    timeout = 0;
    while (HAL_UART_GetState(&__g_uart_handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout>HAL_MAX_DELAY) break;
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&__g_uart_handler, \
           __g_hal_u2_rx_buf, HAL_RX_BUF_SIZE) != HAL_OK) {
        timeout++;
        if (timeout > HAL_MAX_DELAY) break;
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if USART3_IRQ_EN
/*******************************************************************************
* FunName       : lm_uart3_irq_handler()
* Description   : UART3中断函数
* EntryParam    : None
* ReturnValue   : None
*******************************************************************************/
void lm_uart3_irq_handler(void)
{
    uint32_t timeout = 0;

    /* enter interrupt */
    rt_interrupt_enter();

    HAL_UART_IRQHandler(&__g_uart_handler);

    timeout = 0;
    while (HAL_UART_GetState(&__g_uart_handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout>HAL_MAX_DELAY) break;
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&__g_uart_handler, \
           __g_hal_u3_rx_buf, HAL_RX_BUF_SIZE) != HAL_OK) {
        timeout++;
        if (timeout > HAL_MAX_DELAY) break;
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

/* end of file */
