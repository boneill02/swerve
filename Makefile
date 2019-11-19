include config.mk

SRC_DIR=kernel
ARCH_SRC_DIR=$(SRC_DIR)/arch/$(ARCH)

AS_SOURCES=$(patsubst %.s, %.o, $(wildcard $(ARCH_SRC_DIR)/*.s))
C_SOURCES=$(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c)) \
	$(patsubst %.c, %.o, $(wildcard $(ARCH_SRC_DIR)/drivers/*.c)) \
	$(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/mm/*.c))

AS=as
CC=gcc
LD=$(CC)
ASFLAGS=-c -w -32
CPPFLAGS = -DARCH="\"$(ARCH)\"" -DVERSION="\"$(VERSION)\"" -DDEBUG
CFLAGS=-c -g -w -O2 -ffreestanding -fno-pie -std=c89 -pedantic $(CPPFLAGS) -I$(SRC_DIR)/drivers -m32
LDFLAGS=-ffreestanding -fno-stack-protector -fPIC -nostdlib -T$(ARCH_SRC_DIR)/linker.ld -m32
TARGET=$(ARCH)-swerve-$(VERSION)

all: $(TARGET)

clean:
	@echo cleaning
	@rm -rf $(TARGET) $(TARGET).iso grubimg $(wildcard $(SRC_DIR)/*.o) $(wildcard $(ARCH_SRC_DIR)/*.o) \
		$(wildcard $(ARCH_SRC_DIR)/drivers/*.o) $(wildcard $(SRC_DIR)/mm/*.o)

dist: clean
	mkdir $(TARGET)
	cp -R kernel/ scripts/ toolchain/ config.mk LICENSE Makefile README.md $(TARGET)
	tar -cf $(TARGET).tar $(TARGET)
	rm -rf $(TARGET)
	gzip $(TARGET).tar

$(TARGET): $(C_SOURCES) $(AS_SOURCES)
	@$(LD) $^ -o $@ $(LDFLAGS)
	@echo LD $@

%.o: %.s
	@$(AS) $(ASFLAGS) -o $@ $^
	@echo AS $^

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
	@echo CC $^

$(TARGET).iso: $(TARGET)
	mkdir -p grubimg/boot/grub
	cp -f $(TARGET) grubimg/boot/swerve
	cp -f etc/grub.cfg.default grubimg/boot/grub/grub.cfg
	sudo grub-mkrescue -o $(TARGET).iso grubimg
	sudo chown $(USER) $(TARGET).iso
	rm -rf grubimg

grub-image: $(TARGET).iso

run-qemu: $(TARGET)
	qemu-system-$(ARCH) -serial stdio -kernel $(TARGET)

run-qemu-grub: $(TARGET).iso
	qemu-system-$(ARCH) -serial stdio $(TARGET).iso

toolchain:
	cd toolchain && ./build-toolchain.sh

.PHONY: all clean dist grub-image run-qemu run-qemu-grub toolchain $(TARGET) $(TARGET).iso
