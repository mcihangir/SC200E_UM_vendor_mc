#include <unistd.h>
#include <stdio.h>
#include <android/log.h>
#include "dev/proximity_sensor.h"

#define DELAY_SECS 60
#define ALOG(msg) __android_log_write(ANDROID_LOG_DEBUG, "Simple-Daemon", msg)

int main(int argc, char *argv[])
{
	proximity_params_t config;
	char message[128];
	
	int fd = open_sensor(config);
	if(fd < 0){
		return -1;
	}
	int n = 0;
	int precision;
	while(1){
		sleep(DELAY_SECS);

		n++;
		int proximity = poll_sensor(fd, n%2?30:90);

		snprintf(message, sizeof(message), "proximity: %d", proximity);
		ALOG(message);
	}
}