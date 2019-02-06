#ifndef ARCH_H_
#define ARCH_H_

#ifdef QEMU
	volatile unsigned int *const UART0 = (unsigned int *) 0x101f1000;
#else
	#error "Architecture unsupported!"
#endif

#endif
