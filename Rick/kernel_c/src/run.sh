# Shell file to compile code

# assemble boot.s file
as --32 boot.s -o boot.o

# compile kernel.cpp file
g++ -m32 -c kernel.cpp -o kernel.o -std=c++17 -ffreestanding -O1 -Wall -Wextra

g++ -m32 -c utils.cpp -o utils.o -std=c++17 -ffreestanding -O1 -Wall -Wextra

g++ -m32 -c char.cpp -o char.o -std=c++17 -ffreestanding -O1 -Wall -Wextra

# linking all the object files to RICK.bin
ld -m elf_i386 -T linker.ld kernel.o utils.o char.o boot.o -o RICK.bin -nostdlib

# check MyOS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot RICK.bin

# building the iso file
mkdir -p isodir/boot/grub
cp RICK.bin isodir/boot/RICK.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o RICK.iso isodir

# run it in qemu
qemu-system-x86_64 -cdrom RICK.iso
