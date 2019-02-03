.global _init

_init:
	ldr sp, =stack_top
	bl he_main
	b .
