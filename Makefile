.DEFAULT_GOAL := all
# Query the default target.
ifeq ($(.DEFAULT_GOAL),)
  $(warning no default target is set)
endif

RPI_VERSION ?= 4

BOOTMNT ?= /media/boot

ARMGNU = aarch64-none-linux-gnu-
ifdef ARMGNU
	GCC ?= $(ARMGNU)gcc
#   Don't include libc, no Startup files, freeStanding (No depend on Full OS), only general-purpose registers (No FP)
	CFLAGS ?= -DRPI_VERSION=$(RPI_VERSION) -nostdlib -nostartfiles -ffreestanding -mgeneral-regs-only
endif

CFLAGS += -Wall	-Iinclude

ASMFLAGS = -Iinclude

BUILD_DIR = build
SRC_DIR = src

all : kernel8.img

clean:
	$(RM) -rf $(BUILD_DIR) *.elf *.img

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
# Generate dependency files, no link, $< file under compilation, $@ output file 
	$(GCC) $(CFLAGS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(GCC) $(CFLAGS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
S_FILES = $(wildcard $(SRC_DIR)/*.S)
# Variable expansion and patterns generates the names of o-files based on c files with pattern *_c.o
O_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
O_FILES += $(S_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(O_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel8.img: $(SRC_DIR)/linker.ld $(O_FILES)
	@echo "Building for RPI $(value RPI_VERSION)"
	@echo "Deploy to $(value BOOTMNT)"
	@echo ""
	$(ARMGNU)ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(O_FILES)
	$(ARMGNU)objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
ifeq ($(RPI_VERSION), 4)
	rsync -av kernel8.img $(BOOTMNT)/kernel8-rpi4.img
else
	rsync -av kernel8.img $(BOOTMNT)/kernel8.img
endif
	rsync -av config.txt $(BOOTMNT)/config.txt
