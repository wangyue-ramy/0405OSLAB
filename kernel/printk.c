#include "include/x86.h"
#include "include/stdarg.h"
#include "include/stdio.h"
#include "include/serial.h"
/*
 * You may refer to lib/printfmt.c
 * to implement the printk() and vprintk().
 * You can also implement a simplier version
 * by yourself.
 */

/*static void
putch(int ch, int *cnt){
	;
	*
	 * Call the output function(such as putchar(ch)) to display character 'ch'.
	 *

}
*/
#define STRING_MAX_LENGTH 256

void reverse(char *str, int start, int end) {
	char tmp;
	int half = (start + end) / 2;
	while (start <= half) {
		tmp = str[start];
		str[start] = str[end - start];
		str[end - start] = tmp;
		start += 1;
	}
}

int num2str(int num, int base, char *str) {
	int len = 0;
	if (num < 0) {
		str[len++] = '-';
		num = -num;
	}
	while (num > 0) {
		str[len++] = (num % base) + '0';
		num /= base;
	}
	if (str[0] == '-')
		reverse(str, 1, len - 1);
	else
		reverse(str, 0, len - 1);
	return len;
}


void vprintk(const char *fmt,va_list ap){
	int i = 0, len = 0, tmp;
	char result[STRING_MAX_LENGTH], ch, *str;
	while (fmt[i] != '\0') {
		if (fmt[i] == '%') {
			switch (fmt[++i]) {
				case 'd': {
					tmp = va_arg(ap, int);
					len += num2str(tmp, 10, result + len);
					break;
				}
				case 'x': {
					tmp = va_arg(ap, int);
					result[len++] = '0';
					result[len++] = 'x';
					len += num2str(tmp, 16, result + len);
					break;
				}
				case 's': {
					str = va_arg(ap, char *);
					while (*str != '\0') { result[len++] = *str++; }
					break;
				}
				case 'c': {
					ch = (char)va_arg(ap, int);
					result[len++] = ch;
					break;
				}
				default: {
					result[len++] = fmt[i - 1];
					result[len++] = fmt[i];
				}
			}
			i++;
		} else {
			result[len++] = fmt[i++];
		}
	}
	result[len] = '\0';
	for (i = 0; i < len; i++)
		serial_printc(result[i]);
}



void printk(const char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	vprintk(fmt, ap);
	va_end(ap);
}
