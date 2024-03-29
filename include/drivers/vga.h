#ifndef __VGA_DRIVER_H_
#define __VGA_DRIVER_H_

#include <stdint.h>

#define VGA_COLOR_BLACK      0
#define VGA_COLOR_BLUE       1
#define VGA_COLOR_GREEN      2
#define VGA_COLOR_CYAN       3
#define VGA_COLOR_RED        4
#define VGA_COLOR_MAGENTA    5
#define VGA_COLOR_BROWN      6
#define VGA_COLOR_LIGHTGREY  7
#define VGA_COLOR_DARKGREY   8
#define VGA_COLOR_LIGHTBLUE  9
#define VGA_COLOR_LIGHTGREEN 10
#define VGA_COLOR_LIGHTCYAN  11
#define VGA_COLOR_LIGHTRED   12
#define VGA_COLOR_LIGHTMAG   13
#define VGA_COLOR_LIGHTBROWN 14
#define VGA_COLOR_WHITE      15

#define VGA_CRT_IC  0x3d4   // vga index register port
#define VGA_CRT_DC  0x3d5   // vga data register port

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    char ch: 8;
    char fc: 4; // foreground color
    char bc: 4; // background color
} vga_char_t;

void vga_init();
void kclear();

void kputchar(char ch);
void kputs(char *str);

void    vga_setcolor(char f_color, char b_color);
point_t vga_getcur();
void    vga_setcur(int x, int y);

void kprintf(const char *fmt, ...);

#endif // __VGA_DRIVER_H_