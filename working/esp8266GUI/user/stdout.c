//Stupid bit of code that does the bare minimum to make os_printf work.

/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */


#include "espmissingincludes.h"
#include "ets_sys.h"
#include "osapi.h"
#include "uart_hw.h"


extern UartDevice    UartDev;

static void ICACHE_FLASH_ATTR stdoutUartTxd(char c) {
	//Wait until there is room in the FIFO
	while (((READ_PERI_REG(UART_STATUS(0))>>UART_TXFIFO_CNT_S)&UART_TXFIFO_CNT)>=126) ;
	//Send the character
	WRITE_PERI_REG(UART_FIFO(0), c);
}

static void ICACHE_FLASH_ATTR stdoutPutchar(char c) {
	//convert \n -> \r\n
	if (c=='\n') stdoutUartTxd('\r');
	stdoutUartTxd(c);
}

LOCAL void uart0_rx_intr_handler(void *para) {
  /* uart0 and uart1 intr combine togther, when interrupt occur, see reg 0x3ff20020, bit2, bit0 represents
    * uart1 and uart0 respectively
    */
//  RcvMsgBuff *pRxBuff = (RcvMsgBuff *)para;
  //uint8 RcvChar;
  uint8 uart_no = UART0;//UartDev.buff_uart_no;

  if(UART_FRM_ERR_INT_ST == (READ_PERI_REG(UART_INT_ST(uart_no)) & UART_FRM_ERR_INT_ST))
  {
    os_printf("FRM_ERR\r\n");
    WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_FRM_ERR_INT_CLR);
  }

  if(UART_RXFIFO_FULL_INT_ST == (READ_PERI_REG(UART_INT_ST(uart_no)) & UART_RXFIFO_FULL_INT_ST))
  {
    ETS_UART_INTR_DISABLE();
    //system_os_post(0, 0, 0);
  }
  else if(UART_RXFIFO_TOUT_INT_ST == (READ_PERI_REG(UART_INT_ST(uart_no)) & UART_RXFIFO_TOUT_INT_ST))
  {
    ETS_UART_INTR_DISABLE();
    //system_os_post(0, 0, 0);
  }
}


void stdoutInit() {

	// rogerio
	ETS_UART_INTR_ATTACH(uart0_rx_intr_handler,  &(UartDev.rcv_buff));

	//Enable TxD pin
	PIN_PULLUP_DIS(PERIPHS_IO_MUX_U0TXD_U);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_U0TXD);

	// rogerio
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_U0RTS);
	
	//Set baud rate and other serial parameters to 115200,n,8,1
	uart_div_modify(0, UART_CLK_FREQ/BIT_RATE_115200);
	WRITE_PERI_REG(UART_CONF0(0), (STICK_PARITY_DIS)|(ONE_STOP_BIT << UART_STOP_BIT_NUM_S)| \
				(EIGHT_BITS << UART_BIT_NUM_S));

	//Reset tx & rx fifo
	SET_PERI_REG_MASK(UART_CONF0(0), UART_RXFIFO_RST|UART_TXFIFO_RST);
	CLEAR_PERI_REG_MASK(UART_CONF0(0), UART_RXFIFO_RST|UART_TXFIFO_RST);

	
	// rogerio set rx
	WRITE_PERI_REG(UART_CONF1(0),
			((0x10 & UART_RXFIFO_FULL_THRHD) << UART_RXFIFO_FULL_THRHD_S) |
			((0x10 & UART_RX_FLOW_THRHD) << UART_RX_FLOW_THRHD_S) |
			UART_RX_FLOW_EN |
			(0x02 & UART_RX_TOUT_THRHD) << UART_RX_TOUT_THRHD_S |
			UART_RX_TOUT_EN);
	SET_PERI_REG_MASK(UART_INT_ENA(0), UART_RXFIFO_TOUT_INT_ENA |
			UART_FRM_ERR_INT_ENA);



	//Clear pending interrupts
	WRITE_PERI_REG(UART_INT_CLR(0), 0xffff);

	// rogerio enable rx_interrupt
	SET_PERI_REG_MASK(UART_INT_ENA(0), UART_RXFIFO_FULL_INT_ENA);
	ETS_UART_INTR_ENABLE();

	//Install our own putchar handler
	os_install_putc1((void *)stdoutPutchar);
}
