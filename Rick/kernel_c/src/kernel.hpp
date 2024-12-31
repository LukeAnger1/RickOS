#ifndef KERNEL_H
#define KERNEL_H

#include "types.hpp"


#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

uint16* vga_buffer;

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};


#include "keyboard.hpp"


#endif
