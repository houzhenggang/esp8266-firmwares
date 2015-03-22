#include "espmissingincludes.h"
#include "c_types.h"
#include "user_interface.h"
#include "espconn.h"
#include "mem.h"
#include "osapi.h"
#include "ip_addr.h"

#include "io.h"
#include "tempd.h"
#include "dht.h"


/*
 * ----------------------------------------------------------------------------
 * "THE MODIFIED BEER-WARE LICENSE" (Revision 42):
 * Mathew Hall wrote this file. As long as you
 * retain
 * this notice you can do whatever you want with this stuff. If we meet some
 * day,
 * and you think this stuff is worth it, you can buy sprite_tm a beer in return.
 * ----------------------------------------------------------------------------
 */

#define SLEEP_MODE 0
#define SLEEP_TIME 45
static struct espconn tempConn;
static struct _esp_udp socket;
static ip_addr_t master_addr;

#define DATA_PORT 8000
#define DATA_HOST "ninja.roge.us"

static ETSTimer broadcastTimer;
static ETSTimer lookupTimer;
//static ETSTimer sleepTimer;


static void transmitReading(struct sensor_reading* result){
    char buf[256];
    os_sprintf(buf, "{\"type\":\"%s\", \"temperature\":\"%d\", \"humidity\":\"%d\", \"ip\":\"%d\", \"success\":\"%d\"}\n", result->source,(int)(result->temperature), (int)(result->humidity), result->success, result->success);
    espconn_sent(&tempConn, (uint8*)buf, os_strlen(buf));
}

//static void goToSleep(void* arg){
//    os_printf("Going to deep sleep mode now \n");
    //system_deep_sleep(SLEEP_TIME * 1000 * 1000);
//}

static void broadcastReading(void* arg){

    os_printf("Sending heartbeat\n");
//#ifdef SLEEP_MODE
//    struct sensor_reading* result = readDHT(1);
//#else
    struct sensor_reading* result = readDHT();
//#endif
    transmitReading(result);    
    //result = readDS18B20();
    //transmitReading(result);
//#ifdef SLEEP_MODE


//    os_printf("Scheduling power down\n");
//    os_timer_setfn(&sleepTimer, goToSleep, NULL);
//    os_timer_arm(&sleepTimer, 2000, 0);
//#endif
}

static void dnsLookupCb(const char *name, ip_addr_t *ipaddr, void *arg){
    struct espconn* conn = arg;
    ip_addr_t broadcast;
    if(ipaddr == NULL){
        os_printf("Logger: couldn't resolve IP address for %s; will broadcast instead\n", name);
        
        broadcast.addr = (uint32)0x0A00007B;
        IP4_ADDR(&broadcast, 104,236,229,76);
        os_printf("Falling back on %x for logging\n",broadcast.addr);
        ipaddr = &broadcast;
    }
    
    os_printf("Successfully resolved %s as %x\n", name, ipaddr->addr);
    
    if(master_addr.addr == 0 && ipaddr->addr != 0){
        master_addr.addr = ipaddr->addr;
        os_memcpy(conn->proto.udp->remote_ip, &ipaddr->addr, 4);
        os_printf("Will send to %d.%d.%d.%d\n", (int)conn->proto.udp->remote_ip[0], (int)conn->proto.udp->remote_ip[1], (int)conn->proto.udp->remote_ip[2], (int)conn->proto.udp->remote_ip[3]);
        conn->proto.udp->local_port = espconn_port();
    }
    
    espconn_create(conn);
//#ifdef SLEEP_MODE
//    os_printf("Sending data\n");
//    broadcastReading(NULL);
//#else
    os_printf("Arming broadcast timer\n");
    os_timer_arm(&broadcastTimer, 10000, 1);
     
//#endif
}

static void lookupTask(void* arg){
    os_sprintf("Attempting to resolve %s\n", DATA_HOST);
    espconn_gethostbyname(&tempConn, DATA_HOST, &master_addr, dnsLookupCb);
    os_timer_disarm(&lookupTimer);
}

void tempdInit(void){
	os_printf("Temperature logging initialising\n");
	tempConn.type=ESPCONN_UDP;
	tempConn.state=ESPCONN_NONE;
	tempConn.proto.udp=&socket;
        
    master_addr.addr = 0;
    socket.remote_port=DATA_PORT;
    os_timer_setfn(&lookupTimer, lookupTask, NULL);
    os_timer_arm(&lookupTimer, 1000, 1);

    os_timer_setfn(&broadcastTimer, broadcastReading, NULL);
}
