del /q bin\kernel.o

wsl %WSLENV%/x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -Wall -c kernel.c -o bin/kernel.o

copy /y bin\kernel.o ..\Boot\bin\kernel.o

