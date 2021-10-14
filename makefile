


assembly: boot.s
	as -o boot.o boot.s

link:
	ld -Tlink.ld

run:
	qemu-system-x86_64 boot.bin

build: assembly link

all: assembly link run

dump:
	objdump -b binary -m i386:x86-64 -h -D boot.bin

