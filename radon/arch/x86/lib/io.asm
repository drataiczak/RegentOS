global outb

section .text

; void outb(unsigned short port, unsigned char data)
outb:
    mov al, [esp + 8]   ; argv[1]
    mov dx, [esp + 4]   ; argv[0]
    out dx, al
    ret
