#include "main.h"
#include "sens_adux1020.h"


static int initted = 0;

static uint8_t init_array[][3] = {
	{ 0x0c, 0x00, 0x0f },
	{ 0x10, 0x10, 0x10 },
	{ 0x11, 0x00, 0x4c },
	{ 0x12, 0x5f, 0x0c },
	{ 0x13, 0xad, 0xa5 },
	{ 0x14, 0x00, 0x80 },
	{ 0x15, 0x00, 0x00 },
	{ 0x16, 0x06, 0x00 },
	{ 0x17, 0x00, 0x00 },
	{ 0x18, 0x26, 0x93 },
	{ 0x19, 0x00, 0x04 },
	{ 0x1a, 0x42, 0x80 },
	{ 0x1b, 0x00, 0x60 },
	{ 0x1c, 0x20, 0x94 },
	{ 0x1d, 0x00, 0x20 },
	{ 0x1e, 0x00, 0x01 },
	{ 0x1f, 0x00, 0x00 },
	{ 0x20, 0x03, 0x20 },
	{ 0x21, 0x0A, 0x13 },
	{ 0x22, 0x03, 0x20 },
	{ 0x23, 0x01, 0x13 },
	{ 0x24, 0x00, 0x00 },
	{ 0x25, 0x24, 0x12 },
	{ 0x26, 0x24, 0x12 },
	{ 0x27, 0x00, 0x22 },
	{ 0x28, 0x00, 0x00 },
	{ 0x29, 0x03, 0x00 },
	{ 0x2a, 0x07, 0x00 },
	{ 0x2b, 0x06, 0x00 },
	{ 0x2c, 0x60, 0x00 },
	{ 0x2d, 0x40, 0x00 },
	{ 0x2e, 0x00, 0x00 },
	{ 0x2f, 0x00, 0x00 },
	{ 0x30, 0x00, 0x00 },
	{ 0x31, 0x00, 0x00 },
	{ 0x32, 0x00, 0x40 },
	{ 0x33, 0x00, 0x08 },
	{ 0x34, 0xE4, 0x00 },
	{ 0x38, 0x80, 0x80 },
	{ 0x39, 0x80, 0x80 },
	{ 0x3a, 0x20, 0x00 },
	{ 0x3b, 0x1f, 0x00 },
	{ 0x3c, 0x20, 0x00 },
	{ 0x3d, 0x20, 0x00 },
	{ 0x3e, 0x00, 0x00 },
	{ 0x40, 0x80, 0x69 },
	{ 0x41, 0x1f, 0x2f },
	{ 0x42, 0x40, 0x00 },
	{ 0x43, 0x00, 0x00 },
	{ 0x44, 0x00, 0x08 },
	{ 0x46, 0x00, 0x00 },
	{ 0x48, 0x00, 0xef },
	{ 0x49, 0x00, 0x00 },
	{ 0x45, 0x00, 0x00 },
	{ 0x48, 0x00, 0xF0 },
	{ 0x1f, 0x00, 0x00 },
	{ 0x2f, 0x08, 0x00 },
	{ 0x45, 0x01, 0x11 },
};


static int proximity_init( void )
{
	int cnt;
	int ret = 0;

	for ( cnt = 0 ; !ret && ( cnt < ( sizeof( init_array ) / sizeof( init_array[0] ) ) ) ; cnt++ ) {
		ret = i2c_write( ADUX1020_I2C_ADDRESS, init_array[cnt], 3 );
	}

	return ret;
}

static int read_reg16( uint8_t addr, uint16_t *p_reg )
{
	int ret;

	ret = i2c_write( ADUX1020_I2C_ADDRESS, &addr, 1 );
	if ( !ret )
		ret = i2c_read( ADUX1020_I2C_ADDRESS, (uint8_t *)p_reg, 2 );

	return ret;
}

int adux1020_read( adux1020_data *p_data ) {
	int ret = 0;

	if ( !initted ) {
		ret = proximity_init( );
		if (!ret)
			initted = 1;
	}

	if ( p_data == NULL )
		ret = 1;

	if ( !ret )
		ret = read_reg16( 0, &p_data->x1 );
	if ( !ret )
		ret = read_reg16( 1, &p_data->y1 );
	if ( !ret )
		ret = read_reg16( 2, &p_data->x2 );
	if ( !ret )
		ret = read_reg16( 3, &p_data->y2 );
	if ( !ret )
		ret = read_reg16( 4, &p_data->i );
	if ( !ret )
		ret = read_reg16( 5, &p_data->x );
	if ( !ret )
		ret = read_reg16( 6, &p_data->y );
	if ( !ret )
		ret = read_reg16( 7, &p_data->rezerv );

	return ret;
}
