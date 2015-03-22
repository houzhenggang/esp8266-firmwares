# Automatically generated. Not recommended to edit
ifeq ($(CONFIG_DEPLOY_AVRDUDE),y)
DEPLOY+=avrdude
endif

ifeq ($(CONFIG_DEPLOY_DFU_PROGRAMMER),y)
DEPLOY+=dfu-programmer
endif

ifeq ($(CONFIG_DEPLOY_DFUUTIL),y)
DEPLOY+=dfuutil
endif

ifeq ($(CONFIG_DEPLOY_ESPTOOL),y)
DEPLOY+=esptool
endif

ifeq ($(CONFIG_DEPLOY_MSPDEBUG),y)
DEPLOY+=mspdebug
endif

ifeq ($(CONFIG_DEPLOY_NRFDUDE),y)
DEPLOY+=nrfdude
endif

ifeq ($(CONFIG_DEPLOY_OPENOCD),y)
DEPLOY+=openocd
endif

ifeq ($(CONFIG_DEPLOY_RF24TOOL),y)
DEPLOY+=rf24tool
endif

ifeq ($(CONFIG_DEPLOY_RUN),y)
DEPLOY+=run
endif

ifeq ($(CONFIG_DEPLOY_STCDUDE),y)
DEPLOY+=stcdude
endif

ifeq ($(CONFIG_DEPLOY_STLINK),y)
DEPLOY+=stlink
endif

ifeq ($(CONFIG_DEPLOY_STM32FLASH),y)
DEPLOY+=stm32flash
endif

ifeq ($(CONFIG_DEPLOY_UISPTOOL),y)
DEPLOY+=uisptool
endif

ifeq ($(CONFIG_DEPLOY_ZMODEM),y)
DEPLOY+=zmodem
endif

