global outb

section .text

;--------------------------------------------------------------------------------------------------
; Outputs a single byte of data to the given port
;
; void outb(unsigned short port, unsigned char data)
;--------------------------------------------------------------------------------------------------
outb:
    mov al, [esp + 8]   ; Byte to output
    mov dx, [esp + 4]   ; Address of the I/O port
    out dx, al
    ret
