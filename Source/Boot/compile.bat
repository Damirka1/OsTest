del "bin/"

..\..\Compiler\yasm-1.3.0-win64.exe -p gas -f elf64 -o bin/boot.o boot.s

..\..\Compiler\yasm-1.3.0-win64.exe -p gas -f elf64 -o bin/bmain.o bmain.s

ld.lld -T"link.ld"

llvm-objcopy -O binary bin/boot.elf bin/boot.bin

pause
