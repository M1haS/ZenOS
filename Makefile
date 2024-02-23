SOURCES = build/init.o	\
		  build/main.o

CFLAGS = -ffreestanding -fno-pic -fno-stack-protector -fno-exceptions -m32 -c
ASMFLAGS = --32 -c
LDFLAGS = -T link.ld -m elf_i386

all: kernel.elf

build/%.o: src/%.s
	as ${ASMFLAGS} $< -o $@

build/%.o: src/%.c
	gcc ${CFLAGS} $< -o $@

kernel.elf: $(SOURCES)
	ld ${LDFLAGS} ${SOURCES} -o $@

test: all
	qemu-system-i386.exe -kernel kernel.elf

clean:
	rm -rf build/*		\
		   kernel.elf