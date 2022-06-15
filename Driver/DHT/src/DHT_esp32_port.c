/**
  ******************************************************************************
  * @file           : DHT_esp32_port.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Ing. Jhonny A. Velasco
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  *
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#include "../inc/DHT_port.h"

void _set_gpio_mode ( uint8_t DHT_pin, uint8_t gpio_mode )
{
    switch( gpio_mode ){
        case MODE_INPUT:
            gpio_set_direction ( ( gpio_num_t )DHT_pin, ( gpio_mode_t )GPIO_MODE_INPUT );
            break;
        case MODE_OUTPUT:
            gpio_set_direction ( ( gpio_num_t )DHT_pin, ( gpio_mode_t )GPIO_MODE_OUTPUT );
            break;
    }
}

void _set_gpio_level ( uint8_t DHT_pin, uint8_t level )
{
    gpio_set_level ( ( gpio_num_t )DHT_pin, ( uint32_t )level );
}

uint8_t _get_gpio_level ( uint8_t DHT_pin )
{
    return ( uint8_t ) gpio_get_level ( ( gpio_num_t )DHT_pin );
}

void _set_delay_us ( uint32_t uSeconds )
{
    ets_delay_us ( ( uint32_t )uSeconds );
}
