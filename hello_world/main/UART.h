
#include <stdio.h>
#include "driver/uart.h"

#define BUF_READ_SIZE (1024)            //接收数据缓冲区大小
#define BUF_SEND_SIZE (BUF_READ_SIZE)   //发送数据缓冲区大小
QueueHandle_t uart0_queue;
QueueHandle_t uart1_queue;

uart_event_t uart0_event;
uart_event_t uart1_event;


void UART0_INIT(void);
void UART1_INIT(void);
