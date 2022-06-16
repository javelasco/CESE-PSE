#ifndef DHT_INC_DHT_PORT_H_
#define DHT_INC_DHT_PORT_H_

#include <stdio.h>

/**
  *	@brief	Funcion utilizada para configurar el modo del GPIO (input/output).
  * @param	DHT_pin: GPIO al que esta conectado el sensor DHT11/DHT22.
  * @param	gpio_mode: Modo del GPIO (input/output).
  * @retval	none
  */
void _set_gpio_mode ( uint8_t DHT_pin, uint8_t gpio_mode );

/**
  *	@brief	Funcion utilizada para configurar el estado del GPIO (high/low).
  * @param	DHT_pin: GPIO al que esta conectado el sensor DHT11/DHT22.
  * @param	level: Nivel logico del GPIO (high/low).
  * @retval	none
  */
void _set_gpio_level ( uint8_t DHT_pin, uint8_t level );

/**
  *	@brief	Funcion utilizada para obtener el estado del GPIO (high/low).
  * @param	DHT_pin: GPIO al que esta conectado el sensor DHT11/DHT22.
  * @retval	uint8_t: Nivel logico del GPIO.
  */
uint8_t _get_gpio_level( uint8_t DHT_pin );

/**
  *	@brief	Funcion utilizada para realizar retardos bloqueantes en microsegundos.
  * @param	uSeconds: Cantidad de microsegundos.
  * @retval	none
  */
void _set_delay_us(uint32_t uSeconds);


#endif /* DHT_INC_DHT_PORT_H_ */
