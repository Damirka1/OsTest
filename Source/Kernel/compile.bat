del /q bin/kernel.o

clang -target x86_64 -ffreestanding -m64 -Ofast -c kernel.c -o bin/kernel.o

copy /y bin\kernel.o ..\Boot\bin\kernel.o

