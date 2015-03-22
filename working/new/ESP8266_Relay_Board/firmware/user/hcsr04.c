/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you
 * retain
 * this notice you can do whatever you want with this stuff. If we meet some
 * day,
 * and you think this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include "ping.h"
#include "espmissingincludes.h"
#include <osapi.h>

#define TRIG_PIN 4
#define ECHO_PIN 4

float distance = 0;

/*static void ICACHE_FLASH_ATTR pollHCSR04(void * arg){
    float maxDistance = 4000;

    if (ping_pingDistance(PING_MM, maxDistance, &distance) ) {
          os_printf("Response ~ %d mm \n", (int)distance);
    } else {
          os_printf("Failed to get any response.\n");
    }
}
*/
int ICACHE_FLASH_ATTR pollHCSR04(char *buff){
    float maxDistance = 4000;

    if (ping_pingDistance(PING_MM, maxDistance, &distance) ) {
          return os_sprintf(buff, "%d", (int)distance);
          //os_printf("Response ~ %d mm \n", (int)distance);
    } else {
          return os_sprintf(buff, "N/A" );
    //      os_printf("Failed to get any response.\n");
    }
}

void HCSR04Init() {
  os_printf("HCSR04 Init...");

  ping_init(TRIG_PIN,ECHO_PIN);

//  static ETSTimer hcsr04Timer;
//  os_timer_setfn(&hcsr04Timer, pollHCSR04, NULL);
//  os_timer_arm(&hcsr04Timer, 10000, 1);
}

