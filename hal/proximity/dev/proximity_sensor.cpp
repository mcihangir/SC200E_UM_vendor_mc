#include "dev/proximity_sensor.h" //please note that "proximity/include" is alredy added to local include dir

#define PROX_FD 2424
/********************************************************************************
 * 
********************************************************************************/
int open_sensor(proximity_params_t &params)
{
	params.precision.min = 0;
	params.precision.max = 100;
	params.proximity.min = 0;
	params.proximity.min = 100;

	return PROX_FD; //fake file descriptor
}
/********************************************************************************
 * 
********************************************************************************/
int poll_sensor(int fd, int precision)
{
	if(precision < 0 || fd != PROX_FD){
		return -1;
	}
	if(precision < 50){
		return 5;
	}
	if(precision < 80){
		return 8;
	}
	return 10;
}
/********************************************************************************
 * 
********************************************************************************/
int close_sensor(int fd)
{
	if( fd != PROX_FD ){
		return -1;
	}
	return 0;
}