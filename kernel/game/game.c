#include "./include/string.h"
#include "./include/x86.h"
#include "./include/video.h"
#include "./include/i8259.h"
#include "./include/timer.h"
#include "./draw.h"
#include "./include/serial.h"
#include "./include/keyboard.h"

void draw_board() {
	int x, y;
	for (x = 0; x < 15; x++) {
		draw_line(70 + x * 13, 9, 70 + x * 13, 191, 3);
	}
	for (y = 0; y < 15; y++) {
		draw_line(70, 9 + y * 13, 251, 9 + y * 13, 3);
	}
}

void test_keyboard(int code) {
	serial_printc(code);
}

int main(){
	init_intr();				
//	init_timer();					
	init_idt();						
	asm volatile("sti");
	set_keyboard_intr_handler(test_keyboard);
	blue_screen();
	draw_board();
	draw_piece(0, 0, 0);
	draw_piece(1, 0, 15);
	draw_piece(14, 14, 0);
	draw_piece(14, 13, 15);
	draw_cursor(0, 0, 19);
//	hlt();
	printk("I am %d, %s", 29, "Wang Yue");
	while(1);
	return 0;
}
