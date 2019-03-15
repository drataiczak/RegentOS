#include <console.h>

console_t cnsl;

static void _term_puts(const char *str, size_t size) {
	size_t i = 0;

	for(i = 0; i < size; i++) {
		term_putc(str[i]);
	}
}

static void _term_putc(char c, uint8_t color, size_t x, size_t y) {
	size_t index = y * CNSL_WIDTH + x;

	cnsl.buf[index] = vga_entry(c, color);
}

size_t strlen(const char *str) {
	size_t len = 0;

	while(str[len]) {
		len++;
	}

	return len;
}

void console_init(void) {
	size_t x;
	size_t y;
	
	cnsl.row = 0;
	cnsl.col = 0;
	cnsl.fg = VGA_GREEN;
	cnsl.bg = VGA_BLACK;
	cnsl.color = entry_color(cnsl.fg, cnsl.bg);
	cnsl.buf = (uint16_t *)0xB8000;

	for(y = 0; y < CNSL_HEIGHT; y++) {
		for(x = 0; x < CNSL_WIDTH; x++) {
			const size_t index = y * CNSL_WIDTH + x;
			cnsl.buf[index] = vga_entry(' ', cnsl.color);
		}
	}
}

void console_set_color(uint8_t color) {
	cnsl.color = color;
}

void term_putc(char c) {	
	_term_putc(c, cnsl.color, cnsl.col, cnsl.row);

	/* Check for end of line/terminal */
	if(++cnsl.col == CNSL_WIDTH) {
		cnsl.col = 0;

		if(++cnsl.row == CNSL_HEIGHT) {
			cnsl.row = 0;
		}
	}
}

void term_puts(const char *str) {
	_term_puts(str, strlen(str));
}
