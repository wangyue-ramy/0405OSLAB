#include "include/x86.h"
#include "include/assert.h"
#include "include/timer.h"

/* 8253输入频率为1.193182MHz */
#define TIMER_PORT 0x40
#define PORT_CMD 0x43
#define PIT_FREQUENCE 1193182
#define HZ 1


union CmdByte {
	struct {
		uint8_t present_mode:	1;
		uint8_t operate_mode:	3;
		uint8_t access_mode:	2;
		uint8_t channel:		2;
	};
	uint8_t val;
};

union CmdByte mode = {
	.present_mode	= 0,
	.operate_mode	= 2,
	.access_mode	= 3,
	.channel		= 0,
};
void init_timer(void) {
	int counter = PIT_FREQUENCE / HZ;
	outb(PORT_CMD, mode.val);
	outb(TIMER_PORT, counter & 0xFF);
	outb(TIMER_PORT, (counter >> 8) & 0xFF);
}
