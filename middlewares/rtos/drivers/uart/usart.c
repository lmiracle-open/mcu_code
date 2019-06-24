/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-08-30     Aubr.Cool       the first version
 */
 
#include <rthw.h>
#include <rtthread.h>

#include "usart.h"

#ifdef RT_USING_UART

#ifdef RT_USING_DEVICE
#include <rtdevice.h>
#endif

#define UART_RX_BUFSZ 512

/* UART GPIO define. */
#define UART1_GPIO_TX       GPIO_PIN_9
#define UART1_GPIO_RX       GPIO_PIN_10
#define UART1_GPIO          GPIOA


#define UART2_GPIO_TX       GPIO_PIN_2
#define UART2_GPIO_RX       GPIO_PIN_3
#define UART2_GPIO          GPIOA

#define UART3_GPIO_TX       GPIO_PIN_8
#define UART3_GPIO_RX       GPIO_PIN_9
#define UART3_GPIO          GPIOD

/* STM32 uart driver */
struct stm32_uart
{
    struct rt_device parent;
    struct rt_ringbuffer rx_rb;
    USART_TypeDef * uart_base;
    IRQn_Type uart_irq;
    rt_uint8_t rx_buffer[UART_RX_BUFSZ];
    
};
#ifdef RT_USING_UART1
struct stm32_uart uart1_device;
#endif

#ifdef RT_USING_UART2
struct stm32_uart uart2_device;
#endif

#ifdef RT_USING_UART3
struct stm32_uart uart3_device;
#endif

UART_HandleTypeDef UART_Handler;

void uart_irq_handler(struct stm32_uart* uart)
{
	rt_uint8_t Res;
    /* enter interrupt */
    rt_interrupt_enter();
    
    if((__HAL_UART_GET_FLAG(&UART_Handler,UART_FLAG_RXNE)!=RESET)) 
    {
		HAL_UART_Receive(&UART_Handler,&Res,1,1000); 
        rt_ringbuffer_putchar_force(&(uart->rx_rb), Res);
        /* invoke callback */
        if(uart->parent.rx_indicate != RT_NULL)
        {
            uart->parent.rx_indicate(&uart->parent, rt_ringbuffer_data_len(&uart->rx_rb));
        }    
    }
		
    rt_interrupt_leave();
}

#ifdef RT_USING_UART1
void USART1_IRQHandler(void)
{
    uart_irq_handler(&uart1_device);
}
#endif
#ifdef RT_USING_UART2
void USART2_IRQHandler(void)
{
    uart_irq_handler(&uart2_device);
}
#endif

#ifdef RT_USING_UART3
void USART3_IRQHandler(void)
{
    uart_irq_handler(&uart3_device);
}
#endif

static void nvic_configuration(struct stm32_uart* uart)
{

	HAL_NVIC_EnableIRQ(uart->uart_irq);
	HAL_NVIC_SetPriority(uart->uart_irq,3,3);
}

static void uart_io_init(USART_TypeDef * uart_base)
{
    GPIO_InitTypeDef GPIO_Initure;

#ifdef RT_USING_UART1   
	GPIO_Initure.Pin=UART1_GPIO_TX|UART1_GPIO_RX;	
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 
	GPIO_Initure.Pull=GPIO_PULLUP;			 
	GPIO_Initure.Speed=GPIO_SPEED_FAST;		 
	GPIO_Initure.Alternate=GPIO_AF7_USART1;	 
	HAL_GPIO_Init(UART1_GPIO,&GPIO_Initure);	   	 

#endif /* RT_USING_UART1 */

#ifdef RT_USING_UART2
	GPIO_Initure.Pin=UART2_GPIO_TX|UART2_GPIO_RX;	
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;		 
	GPIO_Initure.Pull=GPIO_PULLUP;			 
	GPIO_Initure.Speed=GPIO_SPEED_FAST;		 
	GPIO_Initure.Alternate=GPIO_AF7_USART2;	 
	HAL_GPIO_Init(UART2_GPIO,&GPIO_Initure);
#endif /* RT_USING_UART2 */
	
#ifdef RT_USING_UART3
	GPIO_Initure.Pin=UART3_GPIO_TX|UART3_GPIO_RX;
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;
	GPIO_Initure.Pull=GPIO_PULLUP;
	GPIO_Initure.Speed=GPIO_SPEED_FAST;
	GPIO_Initure.Alternate=GPIO_AF7_USART3;
	HAL_GPIO_Init(UART3_GPIO,&GPIO_Initure);
#endif /* RT_USING_UART3 */
}

static void uart_ll_init(USART_TypeDef * uart)
{
	UART_Handler.Instance=uart;
	UART_Handler.Init.BaudRate=115200;
	UART_Handler.Init.WordLength=UART_WORDLENGTH_8B;
	UART_Handler.Init.StopBits=UART_STOPBITS_1;
	UART_Handler.Init.Parity=UART_PARITY_NONE;
	UART_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	UART_Handler.Init.Mode=UART_MODE_TX_RX;
	HAL_UART_Init(&UART_Handler);
}

static rt_err_t rt_uart_init (rt_device_t dev)
{
    struct stm32_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct stm32_uart *)dev;
    

#ifdef RT_USING_UART1
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();
#endif /* RT_USING_UART1 */

#ifdef RT_USING_UART2
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
#endif /* RT_USING_UART2 */
	
#ifdef RT_USING_UART3
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_USART3_CLK_ENABLE();
#endif /* RT_USING_UART3 */
       
	UART_Handler.Instance=uart->uart_base;
	__HAL_UART_ENABLE_IT(&UART_Handler,UART_IT_RXNE);
	
    uart_io_init(uart->uart_base);
    uart_ll_init(uart->uart_base);
    	
    return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct stm32_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct stm32_uart *)dev;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Enable the UART Interrupt */
        NVIC_EnableIRQ(uart->uart_irq);
    }

    return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
    struct stm32_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct stm32_uart *)dev;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Disable the UART Interrupt */
        NVIC_DisableIRQ(uart->uart_irq);
    }

    return RT_EOK;
}

static rt_size_t rt_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_size_t length;
    struct stm32_uart* uart;
    //RT_ASSERT(serial != RT_NULL);
    uart = (struct stm32_uart *)dev;
    /* interrupt receive */
    rt_base_t level;

    RT_ASSERT(uart != RT_NULL);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();
	
    length = rt_ringbuffer_get(&(uart->rx_rb), buffer, size);
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return length;
}

static rt_size_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    char *ptr = (char*) buffer;
    struct stm32_uart* uart;
    //RT_ASSERT(serial != RT_NULL);
    uart = (struct stm32_uart *)dev;

    if (dev->open_flag & RT_DEVICE_FLAG_STREAM)
    {
        /* stream mode */
        while (size)
        {
            if (*ptr == '\n')
            {
				while((uart->uart_base->SR&0X40)==0);
				uart->uart_base->DR =   '\r';  
            }

			while((uart->uart_base->SR&0X40)==0);
			uart->uart_base->DR = *ptr;  
 
            ptr ++;
            size --;
        }
    }
    else
    {
        while (size)
        {
			while((uart->uart_base->SR&0X40)==0);
			uart->uart_base->DR = *ptr;  
 
            ptr++;
            size--;
        }
    }

    return (rt_size_t) ptr - (rt_size_t) buffer;
}

int rt_hw_usart_init(void)
{
    
#ifdef RT_USING_UART1
    {
        struct stm32_uart* uart;

        /* get uart device */
        uart = &uart1_device;

        /* device initialization */
        uart->parent.type = RT_Device_Class_Char;
        uart->uart_base = USART1;
        uart->uart_irq = USART1_IRQn;
        
        rt_ringbuffer_init(&(uart->rx_rb), uart->rx_buffer, sizeof(uart->rx_buffer));

        /* device interface */
        uart->parent.init 	    = rt_uart_init;
        uart->parent.open 	    = rt_uart_open;
        uart->parent.close      = rt_uart_close;
        uart->parent.read 	    = rt_uart_read;
        uart->parent.write      = rt_uart_write;
        uart->parent.control    = RT_NULL;
        uart->parent.user_data  = RT_NULL;
			
	    nvic_configuration(uart);
              
        rt_device_register(&uart->parent, "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX );
    }
#endif

#ifdef RT_USING_UART2
    {
        struct stm32_uart* uart;

        /* get uart device */
        uart = &uart2_device;

        /* device initialization */
        uart->parent.type = RT_Device_Class_Char;
        uart->uart_base = USART2;
        uart->uart_irq = USART2_IRQn;
        rt_ringbuffer_init(&(uart->rx_rb), uart->rx_buffer, sizeof(uart->rx_buffer));

        /* device interface */
        uart->parent.init 	    = rt_uart_init;
        uart->parent.open 	    = rt_uart_open;
        uart->parent.close      = rt_uart_close;
        uart->parent.read 	    = rt_uart_read;
        uart->parent.write      = rt_uart_write;
        uart->parent.control    = RT_NULL;
        uart->parent.user_data  = RT_NULL;

	    nvic_configuration(uart);
			
        rt_device_register(&uart->parent, "uart2", RT_DEVICE_FLAG_RDWR |\
                                                    RT_DEVICE_FLAG_INT_RX);
    }
#endif /* RT_USING_UART2 */
		
#ifdef RT_USING_UART3
    {
        struct stm32_uart* uart;

        /* get uart device */
        uart = &uart3_device;

        /* device initialization */
        uart->parent.type = RT_Device_Class_Char;
        uart->uart_base = USART3;
        uart->uart_irq = USART3_IRQn;
        rt_ringbuffer_init(&(uart->rx_rb), uart->rx_buffer, sizeof(uart->rx_buffer));

        /* device interface */
        uart->parent.init 	    = rt_uart_init;
        uart->parent.open 	    = rt_uart_open;
        uart->parent.close      = rt_uart_close;
        uart->parent.read 	    = rt_uart_read;
        uart->parent.write      = rt_uart_write;
        uart->parent.control    = RT_NULL;
        uart->parent.user_data  = RT_NULL;

	    nvic_configuration(uart);
			
        rt_device_register(&uart->parent, "uart3", RT_DEVICE_FLAG_RDWR |\
                                                    RT_DEVICE_FLAG_INT_RX);
    }
#endif /* RT_USING_UART3 */
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

#endif /*RT_USING_UART*/

/* end of file */
