# DHT11/DHT22 Driver
Este código es la implementación de un driver para los sensores de temperatura/humedad DHT11/DHT22 por comunicación OneWire. Está implementado de manera modular y maneja una capa de abstracción del hardware de tal manera que permite desplegarlo en varias arquitecturas. En esta versión es compatible con el ARM ST Cortex-M (NUCLEO-F429ZI) y Espressif SoC ESP32.

# Instalación:
El driver consta de varios archivos que deberán ser agregador a su proyecto:

1. Headers:
- DHT.h => Archivo que contiene los headers de las funciones públicas del driver.
- DHT_port.h => Archivo que contiene los headers de las funciones privadas propias del hardware donde se implementará el driver.

2. Sources:
- DHT.c => Archivo que contiene el código de desarollo de las funciones públicas del driver.
- DHT_stm32_port.c => Archivo que contiene el código de desarrollo de las funciones privadas propias del ARM ST Cortex-M (NUCLEO-F429ZI).
- DHT_esp32_port.c => Archivo que contiene el código de desarrollo de las funciones privadas propias del Espressif SoC ESP32.

# Funciones:
Las funciones públicas del driver son las siguientes:

1. Función que inicializa el sensor DHT11/DHT22, recibe como parametros el modelo del sensor (DHT11/DHT22) y el GPIO donde está conectado. Si los parametros ingresados son correctos devolverá un DHT_STATUS = DHT_OK de lo contrario devolverá un DHT_STATUS = DHT_UNKNOWN_SENSOR_ERROR.

- DHT_STATUS DHT_init( DHT_TYPE model, uint8_t gpio );

2. Handler para el control de errores, recibe como único parametro el código de error. Los posibles códigos de errores que puede recibir son: DHT_CHECKSUM_ERROR y DHT_TIMEOUT_ERROR.

- void DHT_errorHandler( DHT_STATUS response );

3. Función que inicia el proceso de lectura del sensor DHT11/DHT22, no recibe parametros. Esta función devuelve un DHT_STATUS con posibles códigos: DHT_OK, DHT_CHECKSUM_ERROR y DHT_TIMEOUT_ERROR.

- DHT_STATUS DHT_readSensor();

4. Función que obtiene el valor de la humedad relativa, no recibe parametros. Esta función devuelve un float con el valor de la humedad relativa.

- float DHT_getHumidity();

6. Función que obtiene el valor de la temperatura ambiente, no recibe parametros. Esta función devuelve un float con el valor de la temperatura ambiente.

- float DHT_getTemperature();

