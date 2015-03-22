deps_config := \
	tmp/all-edeploy.kcnf \
	antares/deploy/zmodem/kcnf \
	antares/deploy/uisptool/kcnf \
	antares/deploy/stm32flash/kcnf \
	antares/deploy/stlink/kcnf \
	antares/deploy/stcdude/kcnf \
	antares/deploy/run/kcnf \
	antares/deploy/rf24tool/kcnf \
	antares/deploy/openocd/kcnf \
	antares/deploy/nrfdude/kcnf \
	antares/deploy/mspdebug/drv_selection.kcnf \
	antares/deploy/mspdebug/kcnf \
	antares/deploy/esptool/kcnf \
	antares/deploy/dfuutil/kcnf \
	antares/deploy/dfu-programmer/proglist.kcnf \
	antares/deploy/dfu-programmer/kcnf \
	antares/deploy/avrdude/proglist.kcnf \
	antares/deploy/avrdude/kcnf \
	tmp/all-deploy.kcnf \
	kcnf \
	antares/src/lib/contrib/Light_WS2812/kcnf \
	antares/src/lib/contrib/vusb/kcnf \
	antares/src/lib/contrib/lwip/lwip.kcnf \
	antares/src/lib/contrib/lwip/kcnf \
	antares/src/lib/contrib/kcnf \
	antares/src/lib/urpc/kcnf \
	antares/src/lib/stlinky/kcnf \
	antares/src/lib/delaylib/kcnf \
	antares/src/lib/wireless/kcnf \
	antares/src/lib/console/stm32.kcnf \
	antares/src/lib/console/kcnf \
	antares/src/lib/ulc/kcnf \
	antares/src/lib/kcnf \
	antares/toolchains/sdcc.kcnf \
	antares/toolchains/gcc.kcnf \
	antares/toolchains/kcnf \
	antares/src/arch/pic32/mcu_selection.kcnf \
	antares/src/arch/pic32/kcnf \
	antares/src/arch/native/kcnf \
	antares/src/arch/msp430/mcu_database.kcnf \
	antares/src/arch/msp430/kcnf \
	antares/src/arch/mips/1890/kcnf \
	antares/src/arch/mips/kcnf \
	antares/src/arch/gbz80/kcnf \
	antares/src/arch/esp8266/kcnf \
	antares/src/arch/avr/mcu_selection.kcnf \
	antares/src/arch/avr/kcnf \
	antares/src/arch/arm/stm32/usb-f1x/strings.kcnf \
	antares/src/arch/arm/stm32/usb-f1x/kcnf \
	antares/src/arch/arm/stm32/library-f4x/kcnf \
	antares/src/arch/arm/stm32/library-f1x/kcnf \
	antares/src/arch/arm/stm32/kcnf \
	antares/src/arch/arm/kcnf \
	antares/src/arch/8051/stc/iap/kcnf \
	antares/src/arch/8051/stc/kcnf \
	antares/src/arch/8051/kcnf \
	tmp/all-arch.kcnf \
	tmp/arch.kcnf \
	antares/features.kcnf \
	antares/kcnf

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
