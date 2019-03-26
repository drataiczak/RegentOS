#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdint.h>
#include <stddef.h>

#define TTY_WIDTH (80)
#define TTY_HEIGHT (25)

typedef enum vga_color {
	VGA_BLACK = 		0,
	VGA_BLUE = 		    1,
	VGA_GREEN = 		2,
	VGA_CYAN = 		    3,
	VGA_RED = 		    4,
	VGA_MAGENTA = 		5,
	VGA_BROWN = 		6,
	VGA_LT_GREY = 		7,
	VGA_DK_GREY = 		8,
	VGA_LT_BLUE = 		9,
	VGA_LG_GREEN = 		10,
	VGA_LT_CYAN = 		11,
	VGA_LT_RED = 		12,
	VGA_LT_MAGENTA =	13,
	VGA_LT_BROWN = 		14,
	VGA_WHITE = 		15,
} vga_col_t;

typedef struct tty {
	size_t row;
	size_t col;
	uint8_t fg;
	uint8_t bg;
	uint8_t color;
	uint16_t *buf;
} tty_t;

static inline uint8_t entry_color(vga_col_t fg, vga_col_t bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(char c, uint8_t color) {
	return (uint16_t) c | (uint16_t) color << 8;
}

void tty_init(void);
void tty_set_color(uint8_t color);
void tty_putc(char c);
void tty_puts(const char *str);

#endif
