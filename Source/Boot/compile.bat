del /q bin\boot.bin
del /q bin\boot.elf
del /q bin\boot.o

..\..\Compiler\yasm-1.3.0-win64.exe -p gas -f elf64 -o bin/boot.o boot.s

..\..\Compiler\yasm-1.3.0-win64.exe -p gas -f elf64 -o bin/bmain.o bmain.s

..\..\Compiler\yasm-1.3.0-win64.exe -f elf64 -o bin/include_binaries.o include_binaries.s

ld.lld -T"linkboot.ld" -N
ld.lld -T"link.ld" -N

llvm-objcopy -O binary bin/boot.elf bin/boot.o
llvm-objcopy -O binary bin/kernel.elf bin/kernel.bin

copy /B bin\boot.o + bin\kernel.bin bin\boot.bin

copy /y bin\boot.bin ..\..\Output\bin\boot.bin

pause
