#ifndef PROXIMITY_HAL_H
#define PROXIMITY_HAL_H

#include <hardware/hardware.h>

#define ACME_PROXIMITY_SENSOR_MODULE "libproximityhal"

typedef struct proximity_sensor_device proximity_sensor_device_t;
//////////////////////////////////////////////////////////////////////////////////////////////////
struct value_range{
	int min;
	int max;
};
//////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct proximity_params{
	struct value_range precision;
	struct value_range proximity;
}proximity_params_t;
//////////////////////////////////////////////////////////////////////////////////////////////////
/**
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

 * Every device data structure must begin with hw_device_t
 * followed by module specific public methods and attributes.

 typedef struct hw_device_t {
    uint32_t tag;  
    uint32_t version;
    struct hw_module_t* module;
    int (*close)(struct hw_device_t* device);
 } hw_device_t;
*/

struct proximity_sensor_device { 
	hw_device_t common;
	int fd;
	proximity_params_t params;
	int (*poll_sensor) (proximity_sensor_device_t *dev, int precision);
};

#endif //PROXIMITY_HAL_H