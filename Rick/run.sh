# Shell file to compile code

# assemble boot.s file
as --32 boot.s -o boot.o

# compile kernel.c file
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# compile vga.c file
gcc -m32 -c vga.c -o vga.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# compile bitmap.c file
gcc -m32 -c bitmap.c -o bitmap.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# linking all the object files to RICK_OS.bin
ld -m elf_i386 -T linker.ld kernel.o vga.o bitmap.o boot.o -o RICK_OS.bin -nostdlib

# check RICK_OS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot RICK_OS.bin

# building the iso file
mkdir -p isodir/boot/grub
cp RICK_OS.bin isodir/boot/RICK_OS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o RICK_OS.iso isodir

# run it in qemu
qemu-system-x86_64 -cdrom RICK_OS.iso
