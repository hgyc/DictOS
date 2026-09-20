#!/bin/sh
set -e
yasm -p gas -f bin -o bootsect.tmp bootsect.asm
dd bs=31744 skip=1 if=bootsect.tmp of=bootsect.bin 2>/dev/null
rm -f bootsect.tmp
gcc -m32 -O0 -ffreestanding -fno-pie -fno-pic -fno-stack-protector \
    -fno-asynchronous-unwind-tables -fcf-protection=none -fno-toplevel-reorder \
    -c kernel.c -o kernel.o
ld --oformat binary -Ttext 0x10000 --entry=kmain -m elf_i386 -o kernel.bin kernel.o
rm -f kernel.o
dd if=/dev/zero of=boot.img bs=512 count=2880 2>/dev/null
dd if=bootsect.bin of=boot.img conv=notrunc 2>/dev/null
dd if=/dev/zero of=kernel.img bs=512 count=2880 2>/dev/null
dd if=kernel.bin of=kernel.img conv=notrunc 2>/dev/null
SIZE=$(stat -c%s kernel.bin)
SECT=$(( (SIZE + 511) / 512 ))
echo "kernel.bin: $SIZE bytes, $SECT sectors (bootloader reads 64)"
if [ "$SECT" -gt 64 ]; then
    echo "WARNING: kernel is larger than 64 sectors, increase the constant in bootsect.asm" >&2
fi
