;------------------------------------------------------------------------------
; Prints an ASCII string
; 
; Inputs:
;   si - The string to print. MUST contain a trailing NULL byte
;
; Outputs:
;   None
;------------------------------------------------------------------------------
prints:
	pusha
	
prints_loop:
	lodsb		; Load a single byte from si into al
	
	or al, al	; Search for our NULL byte
	jz printse	; Exit if we find NULL

	mov ah, 0x0E	; Set up ah for int 0x10
	int 0x10	; TTY print
	jmp prints_loop

printse:
	popa
	ret

;------------------------------------------------------------------------------
; Prints a hexadecimal value as an ASCII string
;
; Inputs:
;   ax - The hexadecimal value to convert to ASCII
;
; Outputs:
;   None
;------------------------------------------------------------------------------
printh:
	pusha

	; TODO ax -> ascii
	; Shift each byte based on its ascii value. 
	; i.e. 0x10 -> '0x0010'

	mov si, hex_out	; Do the actual printing to ascii
	call prints

hex_out: db '0x0000', 0

printhe:
	popa
	ret
