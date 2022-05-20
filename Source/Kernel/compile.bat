del /q bin\kernel.o

clang -ffreestanding -target x86_64 -m64 -Wall -c kernel.c -o bin/kernel.o

copy /y bin\kernel.o ..\Boot\bin\kernel.o

