del /q bin\boot.bin
del /q bin\boot.elf
del /q bin\boot.o

wsl %WSLENV%/x86_64-elf-as -o bin/boot.o boot.s

wsl %WSLENV%/x86_64-elf-as -o bin/bmain.o bmain.s

wsl %WSLENV%/x86_64-elf-as -o bin/include_binaries.o include_binaries.s

wsl %WSLENV%/x86_64-elf-ld -T"linkboot.ld" -N
wsl %WSLENV%/x86_64-elf-ld -T"link.ld" -N

wsl %WSLENV%/x86_64-elf-objcopy -O binary bin/boot.elf bin/boot.o
wsl %WSLENV%/x86_64-elf-objcopy -O binary bin/kernel.elf bin/kernel.bin

copy /B bin\boot.o + bin\kernel.bin bin\boot.bin

copy /y bin\boot.bin ..\..\Output\bin\boot.bin

pause
