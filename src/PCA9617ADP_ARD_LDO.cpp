#include "PCA9617ADP_ARD_LDO.h"

LDO_control::LDO_control( int s0, int s1, int en ) : _s0( s0 ), _s1( s1 ), _en( en )
{
	pinMode( _s0, OUTPUT );
	pinMode( _s1, OUTPUT );
	pinMode( _en, OUTPUT );
}

void LDO_control::set( int v )
{
	digitalWrite( _s0,  v       & 0x01 );
	digitalWrite( _s1, (v >> 1) & 0x01 );
	if ( 0xFF != _en ) {
		digitalWrite( _en, (v >> 2) & 0x01 );
	}
	
	_settting	= v;
};

float	LDO1::voltage( void )
{
	return voltage_values[ _settting ];
}

float	LDO2::voltage( void )
{
	return voltage_values[ _settting ];
}

LDO1::LDO1() : LDO_control( LDO1::S0, LDO1::S1, LDO1::EN_B ) {}
LDO2::LDO2() : LDO_control( LDO2::S0, LDO2::S1, LDO2::EN_B ) {}

float	LDO1::voltage_values[ LDO1::VOLTAGES ]	=  { 1.8, 2.5, 3.3, 4.96, 0.8 };
float 	LDO2::voltage_values[ LDO2::VOLTAGES ]	=  { 2.5, 3.0, 3.3, 4.96 };
