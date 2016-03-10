#include "include/types.h"
#include "include/video.h"
#include "include/string.h"
#include "./draw.h"

#define SIDE_LENGTH 11

void
draw_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color) {
	uint32_t x, y;
	if (x1 == x0) {
		if (y0 > y1) {
			y = y1;
			y1 = y0;
			y0 = y;
		}
		y = y0;
		while (y <= y1) {
			draw_point(x0, y, color);
			y++;
		}
	} 
	else if (y1 == y0) {
		if (x0 > x1) {
			x = x1;
			x1 = x0;
			x0 = x;
		}
		x = x0;
		while (x <= x1) {
			draw_point(x, y1, color);
			x++;
		}
	} else {
		
	}
}

void draw_piece(uint32_t x, uint32_t y, uint32_t color) {
	int i, len;
	len = (SIDE_LENGTH - 1) / 2;
	x = x * 13 + 70;
	y = y * 13 + 9;
	for (i = x - len; i <= x + len; i++) {
		draw_line(i, y - len, i, y + len, color);
	}
}

void draw_cursor(uint32_t x, uint32_t y, uint32_t color) {
	int len;
	len = (SIDE_LENGTH + 1) / 2;
	x = x * 13 + 70;
	y = y * 13 + 9;
	draw_line(x - len, y - len, x + len, y - len, color);
	draw_line(x + len, y - len, x + len, y + len, color);
	draw_line(x + len, y + len, x - len, y + len, color);
	draw_line(x - len, y + len, x - len, y - len, color);
}

void draw_point(uint32_t x, uint32_t y, uint32_t color) {
	memset((void *)vmem + 320 * y + x, color, 1);
}
