#ifndef CGININJA_H
#define CGININJA_H

#include "httpd.h"

int cgiNinjaConf(HttpdConnData *connData);
void tplNinjaConf(HttpdConnData *connData, char *token, void **arg);

#endif
