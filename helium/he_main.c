volatile unsigned int *const UART0DR = (unsigned int *) 0x101f1000;

void print_uart0(const char *str) {
	while(*str) {
		*UART0DR = *str;
		str++;
	}
}

void he_main() {
	print_uart0("Hello world!\n");
}
