#include "drivers/vga.h"
#include "i386/ports.h"
#include "kernel/utils.h"

vga_char_t *vga_mem;       /* vga[25][80] at 0xb8000 */
vga_char_t  color;         /* use vag_char structure to store color */

point_t cur;

static void move_cur()
{
	uint16_t tmp;

	tmp = cur.y * 80 + cur.x;

	/* cursor high port to vga index register */
	outb(VGA_CRT_IC, 0xe);
	outb(VGA_CRT_DC, tmp >> 8);
	/* cursor low port to vga index register */
	outb(VGA_CRT_IC, 0xf);
	outb(VGA_CRT_DC, tmp);
}

static void scroll()
{
	uint16_t blank = color.ch | ( (color.bc << 4) | color.fc) << 8;

	if (cur.y >= 25) {
		memcpy(vga_mem, vga_mem + 80, 80 * 24 * 2);
		memsetw((uint16_t *) vga_mem + 80 * 24, blank, 80);
		cur.y--;
	}
}

void kclear()
{
	int	x, y;
	vga_char_t blank = {' ', VGA_COLOR_LIGHTGREY, VGA_COLOR_BLACK};

	for (y = 0; y < 25; ++y) {
		for (x = 0; x < 80; ++x)
			vga_mem[y * 80 + x] = blank;
	}

	cur.x = cur.y = 0;
	move_cur();
}

void vga_init()
{
	cur.x = 0;
	cur.y = 5;
	move_cur();
	vga_mem	 = (vga_char_t *) 0xb8000;
	color.ch = ' ';
	color.fc = VGA_COLOR_LIGHTGREY;
	color.bc = VGA_COLOR_BLACK;
}

void kputchar(char ch)
{
	switch (ch) {
		case '\r':
			cur.x = 0; 
			break;
		case '\n': 
			cur.y = cur.y + 1;
			cur.x = 0;
			break;
		case '\b':
			cur.y -= (cur.x == 0) ? 1 : 0;
			cur.x = (cur.x + 80 - 1) % 80;
			vga_mem[cur.y * 80 + cur.x].ch = ' ';
			vga_mem[cur.y * 80 + cur.x].fc = color.fc;
			vga_mem[cur.y * 80 + cur.x].bc = color.bc;
			break;
		case '\t': 
			do
				kputchar(' ');
			while (cur.x % 4 != 0);
			break;
		default: {
			vga_mem[cur.y * 80 + cur.x].ch = ch;
			vga_mem[cur.y * 80 + cur.x].fc = color.fc;
			vga_mem[cur.y * 80 + cur.x].bc = color.bc;
			cur.y += (cur.x + 1) / 80;
			cur.x = (cur.x + 1) % 80;
		}
	}
	scroll(); /* you should scroll before updata the cursor, or error */
	move_cur();
}

void kputs(char *str)
{
	for (; *str != '\0'; ++str)
		kputchar(*str);
}

void vga_setcolor(char fc, char bc)
{
	if (fc < 0 || fc > 16 || bc < 0 || bc > 16)
		return;

	color.fc = fc;
	color.bc = bc;
}

point_t vga_getcur() {
	return cur;
}

void vga_setcur(int x, int y)
{
	if (x < 0 || x >= 80 || y < 0 || y >= 25)
		return;

	cur.x = x;
	cur.y = y;
}

void kprintf(const char *fmt, ...)
{
    char **arg = (char **)&fmt;
    int c;
    char buf[32];

    arg++;

    memset(buf, 0, sizeof(buf));
    while ((c = *fmt++) != 0) {
        if (c != '%')
            kputchar(c);
        else {
            char *p, *p2;
            int pad0 = 0, pad = 0;

            c = *fmt++;
            if (c == '0') {
                pad0 = 1;
                c = *fmt++;
            }

            if (c >= '0' && c <= '9') {
                pad = c - '0';
                c = *fmt++;
            }

            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                    itoa(buf, c, *((int *)arg++));
                    p = buf;
                    goto string;
                    break;

                case 's':
                    p = *arg++;
                    if (!p)
                        p = "(null)";

                string:
                    for (p2 = p; *p2; p2++)
                        ;
                    for (; p2 < p + pad; p2++)
                        kputchar(pad0 ? '0' : ' ');
                    while (*p)
                        kputchar(*p++);
                    break;

                default:
                    kputchar(*((int *)arg++));
                    break;
            }
        }
    }
}