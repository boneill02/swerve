include config.mk

SRC_DIR=kernel
ARCH_SRC_DIR=$(SRC_DIR)/arch/$(ARCH)

AS_SOURCES=$(patsubst %.s, %.o, $(wildcard $(ARCH_SRC_DIR)/*.s))
C_SOURCES=$(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c)) \
	$(patsubst %.c, %.o, $(wildcard $(ARCH_SRC_DIR)/drivers/*.c)) \
	$(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/mm/*.c))

AS=$(ARCH_PREFIX)-as
CC=$(ARCH_PREFIX)-gcc
LD=$(CC)
ASFLAGS=-c -w
CPPFLAGS = -DARCH="\"$(ARCH)\"" -DVERSION="\"$(VERSION)\"" -DDEBUG="$(DEBUG)"
CFLAGS=-c -g -w -O2 -ffreestanding -std=c89 -pedantic $(CPPFLAGS) -I$(SRC_DIR)/drivers
LDFLAGS=-ffreestanding -fno-stack-protector -fPIC -nostdlib -T$(ARCH_SRC_DIR)/linker.ld
TARGET=$(ARCH)-swerve-$(VERSION)

all: $(TARGET)

clean:
	@echo cleaning
	@rm -rf $(TARGET) $(TARGET).img $(wildcard $(SRC_DIR)/*.o) $(wildcard $(ARCH_SRC_DIR)/*.o) \
		$(wildcard $(ARCH_SRC_DIR)/drivers/*.o)

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

$(TARGET).img: $(TARGET)
	sudo IMAGE=$(TARGET) ./scripts/mkgrubimg.sh
	sudo chown $(USER) $(TARGET).img

grub-image: $(TARGET).img

run-qemu: $(TARGET)
	qemu-system-$(ARCH) -serial stdio -kernel $(TARGET)

run-qemu-grub: $(TARGET).img
	qemu-system-$(ARCH) -serial stdio $(TARGET).img

toolchain:
	cd toolchain && ./build-toolchain.sh

.PHONY: all clean dist grub-image run-qemu run-qemu-grub toolchain $(TARGET) $(TARGET).img
