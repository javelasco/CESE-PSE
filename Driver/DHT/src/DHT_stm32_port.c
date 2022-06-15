/**
  ******************************************************************************
  * @file           : DHT_stm32_port.c
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

#include <main.h>
#include "../inc/DHT_port.h"

extern TIM_HandleTypeDef htim1;

void _set_gpio_mode ( uint8_t DHT_pin, uint8_t gpio_mode )
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	__HAL_RCC_GPIOA_CLK_ENABLE();

    switch(gpio_mode){
        case MODE_INPUT:
        	GPIO_InitStruct.Pin = ( uint16_t )DHT_pin;
        	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        	GPIO_InitStruct.Pull = GPIO_NOPULL;
        	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        	HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );
            break;

        case MODE_OUTPUT:
        	GPIO_InitStruct.Pin = ( uint16_t )DHT_pin;
        	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        	GPIO_InitStruct.Pull = GPIO_NOPULL;
        	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        	HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );
            break;
    }
}

void _set_gpio_level ( uint8_t DHT_pin, uint8_t level )
{
	HAL_GPIO_WritePin( GPIOA, ( uint16_t )DHT_pin, ( GPIO_PinState )level );
}

uint8_t _get_gpio_level ( uint8_t DHT_pin )
{
    return ( uint8_t )HAL_GPIO_ReadPin( GPIOA, (uint16_t)DHT_pin );
}

void _set_delay_us ( uint32_t uSeconds )
{
	__HAL_TIM_SET_COUNTER( &htim1,0 );  						// set the counter value a 0
	while ( __HAL_TIM_GET_COUNTER( &htim1 ) < uSeconds );  		// wait for the counter to reach the us. input in the parameter
}
