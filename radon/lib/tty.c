#include <tty.h>
#include <string.h>

static tty_t tty;

static void _term_puts(const char *str, size_t size) {
	size_t i = 0;

	for(i = 0; i < size; i++) {
		term_putc(str[i]);
	}
}

static void _term_putc(char c, uint8_t color, size_t x, size_t y) {
	size_t index = y * TTY_WIDTH + x;

	tty.buf[index] = vga_entry(c, color);
}

void tty_init(void) {
	size_t x;
	size_t y;
	
	tty.row = 0;
	tty.col = 0;
	tty.fg = VGA_GREEN;
	tty.bg = VGA_BLACK;
	tty.color = entry_color(tty.fg, tty.bg);
	tty.buf = (uint16_t *)0xB8000;

	for(y = 0; y < TTY_HEIGHT; y++) {
		for(x = 0; x < TTY_WIDTH; x++) {
			const size_t index = y * TTY_WIDTH + x;
			tty.buf[index] = vga_entry(' ', tty.color);
		}
	}
}

void tty_set_color(uint8_t color) {
	tty.color = color;
}

void term_putc(char c) {	
	_term_putc(c, tty.color, tty.col, tty.row);

	/* Check for end of line/terminal */
	if(++tty.col == TTY_WIDTH) {
		tty.col = 0;

		if(++tty.row == TTY_HEIGHT) {
			tty.row = 0;
		}
	}
}

void term_puts(const char *str) {
	_term_puts(str, strlen(str));
}
