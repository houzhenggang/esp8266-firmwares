/*
Cgi/template routines for the /ninja url.
*/

#include <string.h>
#include <osapi.h>
#include "user_interface.h"
#include "mem.h"
#include "httpd.h"
#include "cgi.h"
#include "io.h"
#include "espmissingincludes.h"
#include "config_store.h"

int ICACHE_FLASH_ATTR cgiNinjaConf(HttpdConnData *connData) {
    char buff[1024];

    if (connData->conn==NULL) {
        return HTTPD_CGI_DONE;
    }

    httpdFindArg(connData->postBuff, "ninja_token", buff, sizeof(buff));
    config_update_ninja_token(buff);

    os_printf("post ninja_token: %s\r\n", buff);

    httpdRedirect(connData, "/");

    return HTTPD_CGI_DONE;
}

//Template code for the Ninja page.
void ICACHE_FLASH_ATTR tplNinjaConf(HttpdConnData *connData, char *token, void **arg) {
	char buff[1024];

    if (token==NULL) return;

    os_strcpy(buff, "Unknown");
    if (os_strcmp(token, "ninja_token")==0) {
        os_sprintf(buff, "%s", config_get_ninja_token()); 
    }

	espconn_sent(connData->conn, (uint8 *)buff, os_strlen(buff));
}


