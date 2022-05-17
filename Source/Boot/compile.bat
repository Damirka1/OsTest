del /q "bin/boot.bin"
del /q "bin/boot.elf"
del /q "bin/boot.o"

..\..\Compiler\yasm-1.3.0-win64.exe -p gas -f elf64 -o bin/boot.o boot.s

..\..\Compiler\yasm-1.3.0-win64.exe -p gas -f elf64 -o bin/bmain.o bmain.s

ld.lld -T"link.ld"

llvm-objcopy -O binary bin/boot.elf bin/boot.bin

copy /y bin\boot.bin ..\..\Output\bin\boot.bin

pause
