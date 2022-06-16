/*!
 * @mainpage
 *
 * This driver allows you to configure and interact with the DHT11/DHT22 sensors.
 *
 */

#ifndef DHT_INC_DHT_H_
#define DHT_INC_DHT_H_

#include <stdio.h>

typedef int8_t DHT_STATUS;

#define DHT_OK 0
#define DHT_CHECKSUM_ERROR -1
#define DHT_TIMEOUT_ERROR -2
#define DHT_UNKNOWN_SENSOR_ERROR -3

#define PIN_MODE_INPUT	0
#define PIN_MODE_OUTPUT	1

typedef enum DHT_TYPE{
	DHT11,
	DHT22
} DHT_TYPE;

/**
  *	@brief	Inicializa el sensor DHT11/DHT22.
  * @param	model: Modelo del sensor, se puede usar los sensores DHT11 / DHT22.
  * @param	gpio: GPIO donde esta conectado el sensor.
  * @retval	DHT_STATUS: Codigo del resultado de la configuracion.
  */
DHT_STATUS	DHT_init( DHT_TYPE model, uint8_t gpio );

/**
  *	@brief	Handler para controlar los errores de lectura del sensor.
  * @param	response: Codigo del resultado de la lectura del sensor.
  * @retval	none.
  */
void 		DHT_errorHandler( DHT_STATUS response );

/**
  *	@brief	Inicia el proceso de lectura del sensor DHT11/DHT22.
  * @retval	DHT_STATUS: Codigo del resultado de la lectura del sensor.
  */
DHT_STATUS	DHT_readSensor();

/**
  *	@brief	Obtiene el % humedad.
  * @retval	float: Humedad relativa.
  */
float 		DHT_getHumidity();

/**
  *	@brief	Obtiene la temperatura en grados centigrados.
  * @retval	float: Temperatura ambiental.
  */
float 		DHT_getTemperature();

#endif /* DHT_INC_DHT_H_ */
