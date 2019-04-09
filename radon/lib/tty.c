#include <tty.h>
#include <string.h>
#include <io.h>

tty_t tty;

static void _tty_puts(const char *str, size_t size) {
	size_t i = 0;

	for(i = 0; i < size; i++) {
		tty_putc(str[i]);
	}
}

static void _tty_move_cursor(unsigned short pos) {
    outb(TTY_CMD_PORT, TTY_HIGH_BYTE_CMD);
    outb(TTY_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(TTY_CMD_PORT, TTY_LOW_BYTE_CMD);
    outb(TTY_DATA_PORT, pos & 0x00FF);
}

static void _tty_putc(char c, uint8_t color, size_t x, size_t y) {
	size_t index = y * TTY_WIDTH + x;

	tty.buf[index] = vga_entry(c, color);
}

static void tty_scroll() {
	size_t x;
	size_t y;

	/* Always make sure you've got a blank line */
	tty.row = TTY_HEIGHT - 2;

	for(y = 0; y < TTY_HEIGHT - 1; y++) {
		for(x = 0; x < TTY_WIDTH; x++) {
			const size_t index = y * TTY_WIDTH + x;
			const size_t next = (y + 1) * TTY_WIDTH + x;
			tty.buf[index] = tty.buf[next];
		}
	}

    tty.cursor_pos = (tty.row) * TTY_WIDTH;
    _tty_move_cursor(tty.cursor_pos);
}

void tty_init(void) {
	size_t x;
	size_t y;
	
	tty.row = 0;
	tty.col = 0;
	tty.fg = VGA_GREEN;
	tty.bg = VGA_BLACK;
	tty.color = entry_color(tty.fg, tty.bg);
	tty.buf = (uint16_t *) FRAMEBUFFER;
    tty.cursor_pos = 0;

    _tty_move_cursor(tty.cursor_pos);

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

void tty_putc(char c) {
	int i;

	switch(c) {
		case '\n':
			tty.col = 0;
			if(TTY_HEIGHT - 1 == ++tty.row) {
				tty_scroll();
			}

			break;

		case '\t':
			for(i = 0; i < TTY_TABSTOP; i++) {
				tty_putc(' ');
			}

			break;

		default:
			_tty_putc(c, tty.color, tty.col, tty.row);
			
			/* Check for the end of the row and column */
			if(TTY_WIDTH == ++tty.col) {
				tty.col = 0;

				if(TTY_HEIGHT - 1 == ++ tty.row) {
					tty_scroll();
				}	
			}

			break;
	}
}

void tty_puts(const char *str) {
	_tty_puts(str, strlen(str));
}
