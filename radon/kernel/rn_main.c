#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <tty.h>
#include <itoa.h>

#if defined(__linux__)
	#error Please use the appropriate cross compiler
#endif

#if !defined(__i386__)
	#error Please use the appropriate cross compiler
#endif

void rn_main(void) {
	tty_init();

	int i = 0;

	for(i = 0; i < 85; i++) {
		if(i % 2 == 0) {
            printk("\tHello, world\n");
        }
        else {
            printk("%s", "Hello, world\n");
        }
    }

    printk("Decimal < 0: %d\n", -559);
    printk("Decimal == 0: %d\n", 0);
    printk("Decimal > 0: %d\n", 9824);
    printk("Hex == 0: %x\n", 0);
    printk("Hex > 0: %x\n", 112);
}
