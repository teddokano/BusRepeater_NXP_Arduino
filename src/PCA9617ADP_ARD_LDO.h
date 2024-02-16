/** I2C multiplexer and switch operation library for Arduino
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#ifndef ARDUINO_PCA9617ADP_ARD_LDO_H
#define ARDUINO_PCA9617ADP_ARD_LDO_H

#include <Arduino.h>
#include <stdint.h>

#include <I2C_device.h>

/** LDO_control class
 *	
 *  @class LDO_control
 *
 *	LDO_control class is base class to control LDO on PCA9617ADP-ARD
 *	It controls the LDO output voltage via GPIO pins 
 */

class LDO_control {
public:
	LDO_control( int s0, int s1, int en );
	void	set( int v );
	virtual float voltage( void )	= 0;

protected:
	int		_settting;

private:
	int		_s0;
	int		_s1;
	int		_en;
};

/** LDO1 class
 *	
 *  @class LDO1
 *
 *	LDO1 class is for making instance of control LDO1
 */

class LDO1 : public LDO_control
{
public:
	LDO1();
	
	float  voltage( void );

	enum voltages {
		v1_8,
		v2_5,
		v3_3,
		v4_96,
		v0_8, 
		VOLTAGES
	};

private:
	enum pin_num {
		EN_B	= 3,
		S1,
		S0
	};
	static float	voltage_values[ VOLTAGES ];
};

/** LDO2 class
 *	
 *  @class LDO2
 *
 *	LDO1 class is for making instance of control LDO2
 */

class LDO2 : public LDO_control
{
public:
	LDO2();

	float	voltage( void );

	enum voltages {
		v2_5,
		v3_0,
		v3_3,
		v4_96, 
		VOLTAGES
	};

private:
	enum pin_num {
		S1		= 1,
		S0,
		EN_B	= 0xFF
	};
	static float	voltage_values[ VOLTAGES ];
};

#endif //	ARDUINO_PCA9617ADP_ARD_LDO_H
