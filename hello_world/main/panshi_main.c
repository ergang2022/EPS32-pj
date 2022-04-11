/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "GPIO.h"
#include "UART.h"

//#include "driver/gpio.h"
//#include "driver/uart.h"
//#include "esp_system.h"
//#include "esp_spi_flash.h"
//#include "esp_log.h

int ledflag=0;//蓝色发光二极管标志位


void System_INIT(void)
{
    printf("Hello world!\n");

    for (int i = 3; i > 0; i--) {
        printf("Starting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Starting now.\n");
    fflush(stdout);
    //esp_restart();
}

/*串口任务*/
static void uart0_event_task(void *arg)
{
    /*申请一块内存,用于临时存储接收的数据*/
    uint8_t *data = (uint8_t *) malloc(BUF_READ_SIZE);
    while (1) {
        if(xQueueReceive(uart0_queue, (void * )&uart0_event, portMAX_DELAY))
        {
            switch(uart0_event.type) {
                case UART_DATA://接收到数据
                    //读取接收的数据
                    uart_read_bytes(UART_NUM_0, data, uart0_event.size, portMAX_DELAY);
                    //返回接收的数据
                    uart_write_bytes(UART_NUM_0, (const char*) data, uart0_event.size);
                    break;
                case UART_FIFO_OVF://FIFO溢出(建议加上数据流控制)
                    uart_flush_input(UART_NUM_0);
                    xQueueReset(uart0_queue);
                    break;
                case UART_BUFFER_FULL://接收缓存满(建议加大缓存 BUF_SIZE)
                    uart_flush_input(UART_NUM_0);
                    xQueueReset(uart0_queue);
                    break;
                case UART_BREAK://检测到接收数据中断
                    break;
                case UART_PARITY_ERR://数据校验错误
                    break;
                case UART_FRAME_ERR://数据帧错误
                    break;
                case UART_PATTERN_DET://接收到相匹配的字符(没用到)
                    break;
                default:
                    break;
            }
        }
    }
    free(data);
    data = NULL;
    vTaskDelete(NULL);
}

void app_main(void)
{
    System_INIT();
    GPIO_INIT();
    UART0_INIT();

    //Create a task to handler UART0 event from ISR
    xTaskCreate(uart0_event_task, "uart0_event_task", 2048, NULL, 12, NULL);

    /*
    while(1){
        if(ledflag==0){
            ledflag=1;
            vTaskDelay(1000 / portTICK_RATE_MS);
           gpio_set_level(GPIO_OUTPUT_IO_2, 1);
           printf("LEN ON.\n");
        }
        if(ledflag==1){
            ledflag=0;
            vTaskDelay(1000 / portTICK_RATE_MS);
            gpio_set_level(GPIO_OUTPUT_IO_2, 0);
            printf("LED OFF.\n");
        }
    }
    */
}
