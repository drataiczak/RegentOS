MAGIC equ 0xE85250D6
ARCH  equ 0
TYPE  equ 0
FLAGS equ 0
SIZE  equ 8

section .multiboot_header
init_hdr:
	dd MAGIC
	dd ARCH
	dd fini_hdr - init_hdr
	dd 0x100000000 - (MAGIC + ARCH + (fini_hdr - init_hdr))

	; Optional multiboot tags

	dw TYPE
	dw FLAGS
	dd SIZE
fini_hdr:

section .bss
ALIGN 16
stack_bot:
	resb 16384 ; 16 KiB
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top
	
	extern ar_main

	; EAX = 0x36D76289
	; EBX = Physical address of mb2 information structure
	; CS = 32 bit RX code segment with an offset of 0 and a limit of 0xFFFFFFFF
	; DS
	; ES
	; FS
	; GS
	; SS = Same as CS
	; A20 Gate = enabled
	; CR0 = Bit 31 = 0, bit 0 = 1
	; EFLAGS = Bit 17 = 0, Bit 9 = 0
	; ESP - Must be OS defined. Defined above.
	; GDTR - The OS Must set up its own GDT before using GDTR since it may be invalid
	; IDTR - Same as GDTR except must set up IDT
	call ar_main

	cli
.hang:
	hlt
	jmp .hang

.end:
