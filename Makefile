SRCDIR = src
BUILDDIR = build
INCLUDEDIR = include

CFLAGS=-ffreestanding					\
	   -fno-pic							\
	   -fno-stack-protector				\
	   -fno-exceptions					\
	   -I./${INCLUDEDIR}				\
	   -I./${INCLUDEDIR}/cpu 			\
	   -m32 							\
       -c

ASMFLAGS = --32 -c
LDFLAGS = -T link.ld -m elf_i386

C_SOURCES := $(wildcard $(SRCDIR)/kernel/*.c) \
			 $(wildcard $(SRCDIR)/drivers/*.c) \
			 $(wildcard $(SRCDIR)/cpu/i386/*.c)

ASM_SOURCES := $(wildcard $(SRCDIR)/kernel/*.s) \
			   $(wildcard $(SRCDIR)/cpu/i386/*.s)

C_OBJECTS := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(C_SOURCES))
ASM_OBJECTS := $(patsubst $(SRCDIR)/%.s, $(BUILDDIR)/%.o, $(ASM_SOURCES))

.PHONY: all clean test

all: kernel.elf

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	gcc $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.s
	@mkdir -p $(dir $@)
	as $(ASMFLAGS) $< -o $@

kernel.elf: $(C_OBJECTS) $(ASM_OBJECTS)
	ld $(LDFLAGS) $^ -o $@

test: all
	qemu-system-i386.exe -kernel kernel.elf

clean:
	rm -rf $(BUILDDIR)/* kernel.elf