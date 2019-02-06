#include <arch.h>

void print_uart0(const char *str) {
	while(*str) {
		*UART0 = *str;
		str++;
	}
}

void he_main() {
	print_uart0("Hello world!\n");
}
