/*串口配置
    选择需要的串口进行配置
*/
#include <stdio.h>
#include "driver/uart.h"
#include "UART.h"

/*串口0初始化*/
void UART0_INIT(void)
{
    /*配置串口参数*/
    uart_config_t uart_config = {
        .baud_rate = 115200,//波特率
        .data_bits = UART_DATA_8_BITS,//数据位8位
        .parity    = UART_PARITY_DISABLE,//无奇偶校验
        .stop_bits = UART_STOP_BITS_1,//停止位1位
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,//不使用硬件流控
        .source_clk = UART_SCLK_APB,//串口使用的时钟
    };
    /*初始化串口*/
    uart_driver_install(UART_NUM_0, 
        BUF_READ_SIZE, //串口接收缓存大小
        BUF_SEND_SIZE, //串口发送缓存大小
        20, //队列大小为20
        &uart0_queue, //缓存管理
        0 //设置串口中断优先级,设置为0意味着让系统从1-3级中自动选择一个
    );
    /*设置串口参数*/
    uart_param_config(UART_NUM_0, &uart_config);
    /*设置串口的TX,RX,RTS,DTR引脚*/             //不使用RTS,DTR
    uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}
/*串口1初始化*/
void UART1_INIT(void)
{
    /*配置串口参数*/
    uart_config_t uart_config = {
        .baud_rate = 115200,//波特率
        .data_bits = UART_DATA_8_BITS,//数据位8位
        .parity    = UART_PARITY_DISABLE,//无奇偶校验
        .stop_bits = UART_STOP_BITS_1,//停止位1位
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,//不使用硬件流控
        .source_clk = UART_SCLK_APB,//串口使用的时钟
    };
    /*初始化串口*/
    uart_driver_install(UART_NUM_1, 
        BUF_READ_SIZE, //串口接收缓存大小
        BUF_SEND_SIZE, //串口发送缓存大小
        20, //队列大小为20
        &uart1_queue, //缓存管理
        0 //设置串口中断优先级,设置为0意味着让系统从1-3级中自动选择一个
    );
    /*设置串口参数*/
    uart_param_config(UART_NUM_1, &uart_config);
    /*设置串口的TX,RX,RTS,DTR引脚*/             //不使用RTS,DTR
    uart_set_pin(UART_NUM_1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}
