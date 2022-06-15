/**
  ******************************************************************************
  * @file			DHT.c
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

#include "../inc/DHT.h"

#include "../inc/DHT_port.h"


static int32_t _getSignalLevel ( uint32_t usTimeOut, uint8_t state );

// *************************************************
// *			Variables / Constantes
// * ***********************************************

#define MAXdhtData 5    // 40 bits = 5*8 bits

typedef struct DHT{
    DHT_TYPE    model;
    uint8_t     DHT_pin;
	uint32_t    us_startSignal;
} DHT;

DHT myDHT;

static float humidity      = 0.0;
static float temperature   = 0.0;


// *************************************************
// *					Funciones
// * ***********************************************

DHT_STATUS DHT_init ( DHT_TYPE model, uint8_t gpio )
{
    myDHT.model = model;
    myDHT.DHT_pin = gpio;

    switch( myDHT.model )
    {
        case DHT11:
            myDHT.us_startSignal = 20000;
            break;
        case DHT22:
            myDHT.us_startSignal = 3000;
            break;
        default:
            return DHT_UNKNOWN_SENSOR_ERROR;
    }
    return DHT_OK;
}

void DHT_errorHandler ( DHT_STATUS response )
{
	switch(response) {
        case DHT_UNKNOWN_SENSOR_ERROR:
            temperature = -00.00;
            humidity = -00.00;
			break;

		case DHT_TIMEOUT_ERROR :
            temperature = -127.00;
            humidity = -127.00;
			break;

		case DHT_CHECKSUM_ERROR:
            temperature = -99.99;
            humidity = -99.99;
			break;

		case DHT_OK:
			break;

		default :
            temperature = -111.00;
            humidity = -111.00;
	}
}

DHT_STATUS DHT_readSensor ()
{
    int32_t uSec = 0;

    uint8_t dhtData[MAXdhtData];
    uint8_t byteInx = 0;
    uint8_t bitInx = 7;

    for ( uint8_t k=0; k<MAXdhtData; k++ )
		dhtData[k] = 0;

    // =========== Send start signal to DHT sensor ===========
    _set_gpio_mode( myDHT.DHT_pin, PIN_MODE_OUTPUT );

    // Pull down for 3ms. (DHT22) or 18ms. (DHT11) for a smooth and nice wake up
    _set_gpio_level( myDHT.DHT_pin, 0 );
    _set_delay_us( myDHT.us_startSignal );

    // Pull up for 25us. to 40us for a gentile asking for data
	_set_gpio_level( myDHT.DHT_pin, 1);
    _set_delay_us(40);

    // Change to input mode
    _set_gpio_mode( myDHT.DHT_pin, PIN_MODE_INPUT );


    // =========== DHT will keep the line low for 80us. and then high for 80us. ===========
    uSec = _getSignalLevel( 85, 0 );

	if( uSec<0 ) return DHT_TIMEOUT_ERROR;

    // 80us up
    uSec = _getSignalLevel( 85, 1 );

    if( uSec<0 ) return DHT_TIMEOUT_ERROR;


    // =========== No errors, read the 40 data bits ===========
    for( uint8_t k=0; k<40; k++ )
    {
		// -- starts new data transmission with >50us low signal
		uSec = _getSignalLevel( 66, 0 );
		if( uSec<0 ) return DHT_TIMEOUT_ERROR;

		// -- check to see if after >70us rx data is a 0 or a 1
		uSec = _getSignalLevel( 75, 1 );

		if( uSec<0 ) return DHT_TIMEOUT_ERROR;

		// add the current read to the output data
		// since all dhtData array where set to 0 at the start,
		// only look for "1" (>28us us)
		if ( uSec > 40 )
		{
		    dhtData[ byteInx ] |= ( 1 << bitInx );
		}

		// index to next byte
		if ( bitInx == 0 )
		{
            bitInx = 7;
            ++byteInx;
        }
		else
		{
            bitInx--;
        }
	}

    // == get humidity from Data[0] and Data[1] ==========================
    switch ( myDHT.model )
    {
    case DHT11:
        humidity = dhtData[0];
        temperature = dhtData[2];
        break;

    case DHT22:
    	humidity = dhtData[0] & 0x7F;		// Humidity = dhtData[0] & 0b0111 1111
        humidity *= 0x100;					// Humidity = Humidity << 8
        humidity += dhtData[1];
        humidity /= 10;						// get the decimal

        // == get temperature from Data[2] and Data[3]
        temperature = dhtData[2] & 0x7F;	// temperature = dhtData[2] & 0b0111 1111
        temperature *= 0x100;				// temperature = temperature << 8
        temperature += dhtData[3];
        temperature /= 10;					// get the decimal

        if( dhtData[2] & 0x80 ) 			// negative temperature: dhtData[2] & 0b1000 0000
            temperature *= -1;

        break;
    }

	// == verify if checksum is ok ===========================================
	// Checksum is the sum of Data 8 bits masked out 0xFF
	if ( dhtData[4] == ( ( dhtData[0] + dhtData[1] + dhtData[2] + dhtData[3] ) & 0xFF ) )
		return DHT_OK;

	else
		return DHT_CHECKSUM_ERROR;
}

float DHT_getHumidity ()
{
    return humidity;
}

float DHT_getTemperature ()
{
    return temperature;
}

static int32_t _getSignalLevel ( uint32_t usTimeOut, uint8_t state )
{
	uint32_t uSec = 0;
	while( _get_gpio_level( myDHT.DHT_pin ) == state )
	{
		if( uSec > usTimeOut )
			return -1;

		++uSec;
        _set_delay_us( 1 );
	}
	return uSec;
}
