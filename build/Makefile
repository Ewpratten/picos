# Don't use normal gcc, use the arm cross compiler
CC = ~/Downloads/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-gcc
OBJCOPY = ~/Downloads/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-objcopy

# Set any constants based on the raspberry pi model.  Version 1 has some differences to 2 and 3
ifeq ($(RASPI_MODEL),1)
	CPU = arm1176jzf-s
	DIRECTIVES = -D MODEL_1
	ARCHDIR = hw_rev_1
else
	CPU = cortex-a7
	ARCHDIR = hw_rev_2
endif

CFLAGS= -mcpu=$(CPU) -fpic -ffreestanding $(DIRECTIVES)
# CFLAGS= -fpic -ffreestanding $(DIRECTIVES)
CSRCFLAGS= -O2 -Wall -Wextra
LFLAGS= -ffreestanding -O2 -nostdlib

# Location of the files
KER_SRC = ../src/kernel
KER_HEAD = ../include
COMMON_SRC = ../src/extras
OBJ_DIR = objects
KERSOURCES += $(wildcard $(KER_SRC)/$(ARCHDIR)/*.c)
KERSOURCES += $(wildcard $(KER_SRC)/memory/*.c)
KERSOURCES += $(wildcard $(KER_SRC)/video/*.c)
KERSOURCES += $(wildcard $(KER_SRC)/interrupts/*.c)
KERSOURCES += $(wildcard $(KER_SRC)/io/*.c)
KERSOURCES += $(wildcard $(KER_SRC)/ubasic/*.c)
KERSOURCES += $(wildcard $(KER_SRC)/*.c)
COMMONSOURCES = $(wildcard $(COMMON_SRC)/*.c)
ASMSOURCES += $(wildcard $(KER_SRC)/*.s)
ASMSOURCES += $(wildcard $(KER_SRC)/interrupts/*.s)
OBJECTS = $(patsubst $(KER_SRC)/%.c, $(OBJ_DIR)/%.o, $(KERSOURCES))
OBJECTS += $(patsubst $(COMMON_SRC)/%.c, $(OBJ_DIR)/%.o, $(COMMONSOURCES))
OBJECTS += $(patsubst $(KER_SRC)/%.s, $(OBJ_DIR)/%.o, $(ASMSOURCES))
HEADERS = $(wildcard $(KER_HEAD)/*.h)

IMG_NAME=kernel
FLAGS= -Wno-unused-parameter -Wno-sign-compare -D NO_SDCARD -D EMU_SWITCH

build: $(OBJECTS) $(HEADERS)
	echo $(OBJECTS)
	$(CC) -T linker.ld -o $(IMG_NAME).elf $(LFLAGS) $(OBJECTS)
	$(OBJCOPY) $(IMG_NAME).elf -O binary $(IMG_NAME).img

$(OBJ_DIR)/$(ARCHDIR)/%.o: $(KER_SRC)/$(ARCHDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS) $(FLAGS)

$(OBJ_DIR)/memory/%.o: $(KER_SRC)/memory/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS) $(FLAGS)

$(OBJ_DIR)/video/%.o: $(KER_SRC)/video/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS) $(FLAGS)

$(OBJ_DIR)/interrupts/%.o: $(KER_SRC)/interrupts/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS) $(FLAGS)

$(OBJ_DIR)/io/%.o: $(KER_SRC)/io/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS) $(FLAGS)

$(OBJ_DIR)/ubasic/%.o: $(KER_SRC)/ubasic/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS) $(FLAGS)

$(OBJ_DIR)/%.o: $(KER_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS) $(FLAGS)


$(OBJ_DIR)/%.o: $(KER_SRC)/%.s
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -c $< -o $@

$(OBJ_DIR)/interrupts/%.o: $(KER_SRC)/interrupts/%.s
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -c $< -o $@

$(OBJ_DIR)/%.o: $(COMMON_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS)

clean:
	rm -rf $(OBJ_DIR)
	rm $(IMG_NAME)

run: build
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel kernel.elf