#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <tty.h>

#if defined(__linux__)
	#error Please use the appropriate cross compiler
#endif

#if !defined(__i386__)
	#error Please use the appropriate cross compiler
#endif

void rn_main(void) {
	tty_init();

	int i = 0;
    char *str = "My predefined char *!\n";

	for(i = 0; i < 80; i++) {
		tty_puts("Hello world!\n");
	}

	for(i = 0; i < 10; i++) {
		tty_puts("\t[ADDITIONAL]\n");
	}

    printk("Printk works! %s", str);
}
