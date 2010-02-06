
#include "uart.h"

#define uart_reg(n)	(*(volatile uint32_t*)(UART_BASE + n))

void uart_putc(char c)
{
	int timeout=4000;

	if (UART_STATUS1 & 0x1E) return;
	while (timeout > 0) {
		if ((UART_STATUS2 & 0x10) && ((UART_STATUS3 & 4) == 0)) {
			UART_DATA = c;
			break;
		}
		timeout--;
	}
//	if (timeout < 1) diag_printf("timeout\n");
}

int uart_getc(char *c)
{
	int timeout=4000;

	while (timeout > 0) {
		if ((UART_STATUS3 & 0x10) == 0) break;
		timeout--;
	}
	if (timeout < 1) return 0;

	if (UART_STATUS1 & 0x1E) return 0;

	*c = UART_DATA;
	return 1;
}

