include config.mk

SRC_DIR=kernel
ARCH_SRC_DIR=$(SRC_DIR)/arch/$(ARCH)

LIBC_DIR=libc
LIBC_TARGET=libc.a
LIBC_SOURCES=$(patsubst %.c, %.o, $(shell find $(LIBC_DIR) | grep "\.c"))

AS_SOURCES=$(patsubst %.s, %.o, $(wildcard $(ARCH_SRC_DIR)/*.s))
C_SOURCES=$(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c)) \
	$(patsubst %.c, %.o, $(wildcard $(ARCH_SRC_DIR)/drivers/*.c)) \
	$(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/mm/*.c))

all: $(TARGET)

clean:
	@echo CLEANING
	@rm -rf $(TARGET) $(TARGET).iso grubimg $(wildcard $(SRC_DIR)/*.o) $(wildcard $(ARCH_SRC_DIR)/*.o) \
		$(wildcard $(ARCH_SRC_DIR)/drivers/*.o) $(wildcard $(SRC_DIR)/mm/*.o)
	@echo DONE

dist: clean
	@mkdir $(TARGET)
	@cp -R kernel/ scripts/ toolchain/ config.mk LICENSE Makefile README.md $(TARGET)
	@tar -cf $(TARGET).tar $(TARGET)
	@rm -rf $(TARGET)
	@gzip $(TARGET).tar
	@echo DIST

$(TARGET): $(LIBC_SOURCES) $(C_SOURCES) $(AS_SOURCES)
	@$(LD) $(LDFLAGS) -o $@ $^
	@echo LD $@

$(LIBC_TARGET): $(LIBC_SOURCES)
	@$(LD) $(LDFLAGS) -static -o $(LIBC_TARGET) $(LIBC_SOURCES)

%.o: %.s
	@$(AS) $(ASFLAGS) -o $@ -c $^
	@echo AS $^

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $^
	@echo CC $^

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
	qemu-system-$(ARCH) -serial stdio $(TARGET).iso

toolchain:
	cd toolchain && ./build-toolchain.sh

.PHONY: all clean dist grub-image run-qemu run-qemu-grub toolchain $(TARGET) $(TARGET).iso
