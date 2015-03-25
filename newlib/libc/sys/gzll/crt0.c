
extern void main();

void _start() {
	main();
	__asm__("l.ori r11, r0, 0x0; l.sys 0" : : : "memory");
}
