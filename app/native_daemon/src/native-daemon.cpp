#include <unistd.h>
//#include <string.h>
#include <stdio.h>
#include <android/log.h>
#include <hardware/hardware.h>

#include "proximity_hal.h"

#define DELAY_SECS 30
#define ALOG(msg) __android_log_write(ANDROID_LOG_DEBUG, "Native-Daemon-3", msg)

/*
 * Get the module info associated with a module by id.
 *
 * @return: 0 == success, <0 == error and *module == NULL
 int hw_get_module(const char *id, const struct hw_module_t **module);
*/

int main(int argc, char *argv[])
{
	//this is the common for every hw HAL module
	const hw_module_t *module;
	int ret;
	
	ret = hw_get_module(ACME_PROXIMITY_SENSOR_MODULE, &module); 
	if( ret ){
		ALOG("Failed to load the Acme Proximity HAL module");
		char message[128];
		snprintf(message, sizeof(message), "hw_get_module(): %d", ret);
		//snprintf(message, sizeof(message), "hw_get_module(): (%s)", strerror(-ret));
		ALOG(message);
		return -1;
	}
	ALOG("Finished loading...");

	//this is the specific for our device and defined in the HAL header file
	proximity_sensor_device_t *device;

	//this is the common, we open the module and load our device
	if ( module->methods->open(module, nullptr, reinterpret_cast<hw_device_t**>(&device) ) ){
		ALOG("Failed to open Acme Proximity HAL");
		return -1;
	}

	proximity_params_t config = device->params;
	char message[128];

	int n = 0;
	int precision;
	while(1){
		sleep(DELAY_SECS);
		n++;
		int proximity = device->poll_sensor(device, n%2?10:90);

		snprintf(message, sizeof(message), "proximity: %d", proximity);
		ALOG(message);
	}

	return 0;
}