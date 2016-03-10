#include "include/x86.h"
#include "include/serial.h"

#define SERIAL_PORT  0x3F8

void
init_serial(void) {
	outb(SERIAL_PORT + 1, 0x00);
	outb(SERIAL_PORT + 3, 0x80);
	outb(SERIAL_PORT + 0, 0x01);
	outb(SERIAL_PORT + 1, 0x00);
	outb(SERIAL_PORT + 3, 0x03);
	outb(SERIAL_PORT + 2, 0xC7);
	outb(SERIAL_PORT + 4, 0x0B);
}

int
serial_idle(void) {
	return (inb(SERIAL_PORT + 5) & 0x20) != 0;
}

void
serial_printc(char ch) {
	init_serial();
	while (!serial_idle());
	outb(SERIAL_PORT, ch);
}
