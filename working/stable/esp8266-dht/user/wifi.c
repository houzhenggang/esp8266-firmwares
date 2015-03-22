#include <string.h>
#include <osapi.h>
#include "user_interface.h"
#include "espmissingincludes.h"
#include "wifi.h"
//Drop the soft AP if we are a valid client on the network.
static void ICACHE_FLASH_ATTR wifiCheckCb(void *arg) {
	int x=wifi_get_opmode();

	if (x!=1) {
            int y=wifi_station_get_connect_status();
            os_printf("WiFi State Update: %d - looking for %d (got IP)\n", y, STATION_GOT_IP);
            
            if (y==STATION_GOT_IP) {
                os_printf("Dropping soft AP because I got IP");
            	//Go to STA mode. This needs a reset, so do that.
            	wifi_set_opmode(1);
            	system_restart();
            } else {
            	os_printf("Connect fail. Not going into STA-only mode.\n");
                if (x==2) {
                    os_printf("Wrong WIFI mode. Going to STA+AP mode.\n");
                    wifi_set_opmode(3);
                    system_restart();
                }
            }
            
	}
}

void ICACHE_FLASH_ATTR wifiCheck(void){
    static ETSTimer wifiTimer;
    os_timer_setfn(&wifiTimer, wifiCheckCb, NULL);
    os_timer_arm(&wifiTimer, 5000, 0);
}
