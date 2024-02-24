/*
	Three-step process for creating a HAL
	1.  The first step in the process consists of defining a HAL module. (hw_module_t HAL_MODULE_INFO_SYM) 
		The HAL module contains metadata about a device and is also the factory for instances of the HAL.
	2. Create the device methods (hw_module_methods_t proximity_sensor_methods ) 
	3. Create the device struct (proximity_sensor_device_t) includes hw_device_t 	
*/

#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <log/log_system.h>

#include "proximity_hal.h"
#include "dev/proximity_sensor.h"	//real driver of the hardware (shim) poll_sensor(), close_sensor() , open_sensor() comes fron this driver

#define LOG_TAG "PROX"
/********************************************************************************
 * 
********************************************************************************/
static int poll_proximity_sensor(proximity_sensor_device_t *dev, int precision)
{
	SLOGV("Polling Proximity Sensor");

	if(!dev){
		return -1;
	}

	return poll_sensor(dev->fd, precision);
}
/********************************************************************************
 * 
********************************************************************************/
static int close_proximity_sensor(proximity_sensor_device_t *dev)
{
	SLOGV("Closing Proximity Sensor");

	if(!dev){
		return 0;
	}

	close_sensor(dev->fd);
	free(dev);
	return 0;
}
/********************************************************************************
 * 
********************************************************************************/
/*
 * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM
 * and the fields of this data structure must begin with hw_module_t
 * followed by module specific information.

typedef struct hw_module_t {
    uint32_t tag;
    uint16_t module_api_version;
    uint16_t hal_api_version;
    const char *id;
    const char *name;
    const char *author;
    struct hw_module_methods_t* methods;
    void* dso;
} hw_module_t;

 typedef struct hw_device_t {
    uint32_t tag;  
    uint32_t version;
    struct hw_module_t* module;
    int (*close)(struct hw_device_t* device);
 } hw_device_t;

struct proximity_sensor_device { 
	hw_device_t common;
	int fd;
	proximity_params_t params;
	int (*poll_sensor) (proximity_sensor_device_t *dev, int precision);
}proximity_sensor_device_t;
*/
static int open_proximity_sensor_module(const struct hw_module_t *module, const char *name, struct hw_device_t **device)
{
	SLOGV("Opening Proximity Sensor");

	auto *dev = static_cast<proximity_sensor_device_t*>(malloc(sizeof(proximity_sensor_device_t)));
	if(!dev){
		return -ENOMEM;
	}
	memset(dev, 0, sizeof(*dev));

	int fd = open_sensor(dev->params);
	if(fd < 0){
		SLOGV("Failed to open Proximity Sensor");
		free(dev);
		return -1;
	}
	dev->fd = fd;
	dev->common.tag = HARDWARE_DEVICE_TAG;
	dev->common.version = 0;
	dev->common.module = (struct hw_module_t*) module;
	dev->common.close = (int (*)(struct hw_device_t *))close_proximity_sensor;
	dev->poll_sensor = poll_proximity_sensor;//(int (*)(proximity_sensor_device_t *, int))poll_proximity_sensor;

	*device = reinterpret_cast<hw_device_t *>(dev);

	return 0;
}
/********************************************************************************
 * 
********************************************************************************/
/*
typedef struct hw_module_methods_t {
    int (*open)(const struct hw_module_t* module, const char* id, struct hw_device_t** device);

} hw_module_methods_t;
*/
static hw_module_methods_t proximity_sensor_methods = {
	.open = open_proximity_sensor_module
};
/*
The hw_module_t struct for the proximity sensor is now complete. 
Its .methods.open field contains a reference to a method that opens the underlying device for use: 
open_proximity_sensor_module. That method will be defined in a moment.
*/

/********************************************************************************
 * 
********************************************************************************/
/*
 * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM
 * and the fields of this data structure must begin with hw_module_t
 */
hw_module_t HAL_MODULE_INFO_SYM = {
	.tag 				= HARDWARE_MODULE_TAG,
	.module_api_version = HARDWARE_HAL_API_VERSION,
	.hal_api_version	= 0,
	.id 				= ACME_PROXIMITY_SENSOR_MODULE,
	.name 				= "Acme Proximity Sensor",
	.author				= "Mehmet Cihangir",
	.methods			= &proximity_sensor_methods,
};













