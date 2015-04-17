
extern void main();
extern void exit();

extern int *__bss_start;
extern int *_end;

void _start() {
    char *i;
    for (i = __bss_start; i < _end; i++) {
        *i = 0;
    }
    main();
    exit();
}
