#include <jni.h>
#include <string.h>
#include <hardware/hardware.h>

#include "dev/proximity_sensor.h"

/*******************************************************************************************************
*
*******************************************************************************************************/
JNIEXPORT jlong JNICALL Java_com_acme_device_proximity_AcmeProximitySensor_open  
  (JNIEnv *env, jclass clazz){
	const hw_module_t *module;

	int ret = hw_get_module(ACME_PROXIMITY_SENSOR_MODULE, &module);
	if(ret){
		return -1;
	}
	long device;
	ret = module->methods->open( module, nullptr, reinterpret_cast<hw_device_t **>(&device) );
	if(ret){
		return -1;
	}
	return (jlong) device;
	
}
/*******************************************************************************************************
*
*******************************************************************************************************/
JNIEXPORT jint JNICALL Java_com_acme_device_proximity_AcmeProximitySensor_poll
  (JNIEnv *env, jclass clazz, jlong handle, jint precision){

	auto *device = reinterpret_cast<proximity_sensor_device_t *>(handle);
	return device->poll_sensor(device, precision);

  }

/*******************************************************************************************************
*
*******************************************************************************************************/
JNIEXPORT jint JNICALL Java_com_acme_device_proximity_AcmeProximitySensor_close
  (JNIEnv *env, jclass clazz, jlong handle){
	
	auto *device = reinterpret_cast<proximity_sensor_device_t *>(handle);
	return device->common.close( reinterpret_cast<hw_device_t *>(device) );

  }