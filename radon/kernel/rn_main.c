#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <tty.h>

#if defined(__linux__)
	#error Please use the appropriate cross compiler
#endif

#if !defined(__i386__)
	#error Please use the appropriate cross compiler
#endif

void rn_main(void) {
	tty_init();
	term_puts("Hello world!");
}
