#include "include/x86.h"
#include "include/video.h"

#define PORT_PIC_MASTER 0x20
#define PORT_PIC_SLAVE  0xA0
#define IRQ_OFFSET 		0x20
#define IRQ_SLAVE       2

/* 初始化8259中断控制器：
 * 硬件中断IRQ从32号开始，自动发送EOI */
void
init_intr(void) {
	
	outb(PORT_PIC_MASTER + 1, 0xf7);
	outb(PORT_PIC_SLAVE + 1, 0xff);

	outb(PORT_PIC_MASTER, 0x11);

	outb(PORT_PIC_MASTER + 1, IRQ_OFFSET);

	outb(PORT_PIC_MASTER + 1, 1 << IRQ_SLAVE);

	outb(PORT_PIC_MASTER + 1, 0x2);

	outb(PORT_PIC_SLAVE, 0x11);
	outb(PORT_PIC_SLAVE + 1, IRQ_OFFSET + 8);
	outb(PORT_PIC_SLAVE + 1, IRQ_SLAVE);

	outb(PORT_PIC_SLAVE + 1, 0x01);


	outb(PORT_PIC_MASTER, 0x68);
	outb(PORT_PIC_MASTER, 0x0a);

	outb(PORT_PIC_SLAVE, 0x68);
	outb(PORT_PIC_SLAVE, 0x0a);


}
