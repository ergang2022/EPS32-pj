#include <stdio.h>
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_2    2
#define GPIO_OUTPUT_PIN_SEL  (1ULL<<GPIO_OUTPUT_IO_2)

void GPIO_INIT(void);