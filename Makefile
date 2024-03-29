include config.mk

SRC_DIR=kernel
ARCH_SRC_DIR=$(SRC_DIR)/arch/$(ARCH)

AS_SOURCES=$(patsubst %.s, %.o, $(wildcard $(ARCH_SRC_DIR)/*.s))
C_SOURCES=$(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c)) \
	$(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/drivers/*.c)) \
	$(patsubst %.c, %.o, $(wildcard $(ARCH_SRC_DIR)/drivers/*.c)) \

all: $(TARGET)

clean:
	@echo CLEANING
	@rm -rf $(TARGET) $(C_SOURCES:.c=.o) $(AS_SOURCES:.s=.o)
	@echo DONE

dist: clean
	@mkdir $(TARGET)
	@cp -R kernel/ scripts/ toolchain/ config.mk LICENSE Makefile README.md $(TARGET)
	@tar -cf $(TARGET).tar $(TARGET)
	@rm -rf $(TARGET)
	@gzip $(TARGET).tar
	@echo DIST

$(TARGET): $(C_SOURCES) $(AS_SOURCES)
	@$(LD) -static $(LDFLAGS) -o $@ $^ -lc
	@echo LD $@

%.o: %.s
	@$(AS) $(ASFLAGS) -o $@ -c $^
	@echo AS $@

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $^
	@echo CC $@

$(TARGET).iso: $(TARGET)
	@mkdir -p grubimg/boot/grub
	@cp -f $(TARGET) grubimg/boot/swerve
	@cp -f etc/grub.cfg.default grubimg/boot/grub/grub.cfg
	@sudo grub-mkrescue -o $(TARGET).iso grubimg
	@sudo chown $(USER) $(TARGET).iso
	@rm -rf grubimg
	@echo MKGRUBCFG

grub-image: $(TARGET).iso

run-qemu: $(TARGET)
	qemu-system-$(ARCH) -serial stdio -kernel $(TARGET)

run-qemu-grub: $(TARGET).iso
	qemu-system-$(ARCH) -m 128 -smp 1 -vga std -serial stdio $(TARGET).iso

toolchain:
	cd toolchain && ./build-toolchain.sh

.PHONY: all clean dist grub-image run-qemu run-qemu-grub toolchain $(TARGET) $(TARGET).iso
