#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
	#error Please use the appropriate cross compiler
#endif

#if !defined(__i386__)
	#error Please use the appropriate cross compiler
#endif

typedef enum VGA_Color {
	VGA_BLACK = 0,
	VGA_BLUE = 1,
	VGA_GREEN = 2,
	VGA_CYAN = 3,
	VGA_RED = 4,
	VGA_MAGENTA = 5,
	VGA_BROWN = 6,
	VGA_LT_GREY = 7,
	VGA_DK_GREY = 8,
	VGA_LT_BLUE = 9,
	VGA_LT_GREEN = 10,
	VGA_LT_CYAN = 11,
	VGA_LT_RED = 12,
	VGA_LT_MAGENTA = 13,
	VGA_LT_BROWN = 14,
	VGA_WHITE = 15,
} vga_col_t;

static inline uint8_t vga_entry_color(vga_col_t fg, vga_col_t bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(char c, uint8_t color) {
	return (uint16_t) c | (uint16_t) color << 8;
}

size_t strlen(const char *str) {
	size_t len = 0;

	while(str[len]) {
		len++;
	}

	return len;
}

static const size_t TERM_WIDTH = 80;
static const size_t TERM_HEIGHT = 25;
size_t term_row;
size_t term_col;
uint8_t term_color;
uint16_t *term_buf;

void term_init(void) {
	size_t x;
	size_t y;

	term_row = 0;
	term_col = 0;
	term_color = vga_entry_color(VGA_BLACK, VGA_GREEN);
	term_buf = (uint16_t *) 0xB8000;

	for(y = 0; y < TERM_HEIGHT; y++) {
		for(x = 0; x < TERM_WIDTH; x++) {
			const size_t i = y * TERM_WIDTH + x;
			term_buf[i] = vga_entry(' ', term_color);
		}
	}
}

void terminal_set_color(uint8_t color) {
	term_color = color;
}

void term_puts(char c, uint8_t color, size_t x, size_t y) {
	const size_t i = y * TERM_WIDTH + x;

	term_buf[i] = vga_entry(c, color);
}

void term_putchar(char c) {
	term_puts(c, term_color, term_col, term_row);
	
	if(++term_col == TERM_WIDTH) {
		term_col = 0;

		if(++term_row == TERM_HEIGHT) {
			term_row = 0;
		}
	}
}

void term_write(const char *data, size_t size) {
	size_t i = 0;

	for(i = 0; i < size; i++) {
		term_putchar(data[i]);
	}
}

void term_writestring(const char *data) {
	term_write(data, strlen(data));
}

void rn_main(void) {
	term_init();
	term_writestring("Hello world!");
}
