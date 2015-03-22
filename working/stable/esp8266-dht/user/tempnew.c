#include "espmissingincludes.h"
#include "c_types.h"
#include "user_interface.h"
#include "espconn.h"
#include "mem.h"
#include "osapi.h"
#include "ip_addr.h"

#include "io.h"
#include "tempnew.h"
#include "dht.h"
#include "httpclient.h"

#define DATA_HOST "http://ninja.roge.us/v0/Message"
#define POOL_TIME 60000

static ETSTimer broadcastTimer;

static void transmitReading(){
    char buf[256];

    struct sensor_reading* result = readDHT();

    os_sprintf(buf, "SensorType=%s&Temperature=%d&Humidity=%d", result->source,(int)(result->temperature), (int)(result->humidity));

    http_post(DATA_HOST, buf, http_callback_tostdout);
}

void tempnewInit(void){
	os_printf("tempnew starting\n");
        
    os_timer_setfn(&broadcastTimer, transmitReading, NULL);
    os_timer_arm(&broadcastTimer, POOL_TIME, 1);
}
