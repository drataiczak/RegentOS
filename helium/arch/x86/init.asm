bits 16
org 0x7C00

init_stack:
	mov bp, 0x8000			; Put our stack just above BIOS
	mov sp, bp

enter:
	mov si, enter_msg
	call prints

exit:
	mov si, exit_msg
	call prints

hang:
	cli
	hlt

%include "io.asm"

enter_msg: db 'Hello world!', 0x0D, 0x0A, 0
exit_msg: db 'Goodbye world!', 0x0D, 0x0A, 0

times 510 - ($ - $$) db 0		; Pad with 0s
dw 0xAA55				; Magic number

