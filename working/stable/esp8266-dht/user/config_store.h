/* Copyright (c) 2014 Ivan Grokhotkov. All rights reserved.
 * This file is part of the atproto AT protocol library
 *
 * Redistribution and use is permitted according to the conditions of the
 * 3-clause BSD license to be found in the LICENSE file.
 */

#ifndef CONFIG_STORE_H
#define CONFIG_STORE_H

#include "c_types.h"

#define CONFIG_MAGIC   0x42
#define CONFIG_VERSION 1
#define DEFAULT_INTERVAL 300
#define DEFAULT_TOKEN "http://www.google.com"

typedef struct {
    uint32 magic;
    uint32 version;
    uint32 interval_sec;
    char ninja_token [256];
    // bump CONFIG_VERSION when adding new fields
} config_t;


config_t* config_get();
void config_save();
config_t* config_init();
void config_init_default();
void config_update_ninja_token(char token[256]);
char* config_get_ninja_token();

#endif//CONFIG_STORE_H
