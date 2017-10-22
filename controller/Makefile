CC := avr-gcc

# Microcontroller instruction set architecture
MCU := atmega328p

# Optimization level, can be [0, 1, 2, 3, s]. 0 turns off optimization.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT := s

SRCDIR := src
BUILDDIR := ../build

SRCEXT := c
CFLAGS := -O$(OPT) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
		  -Wall -Wstrict-prototypes -mmcu=$(MCU) -D__TWEAK__ 

all: $(BUILDDIR)/controller.hex $(BUILDDIR)/controller.eep $(BUILDDIR)/controller.lss \
	 $(BUILDDIR)/controller.sym $(BUILDDIR)/controller.elf $(BUILDDIR)/controller.o  

$(BUILDDIR)/%.hex: $(BUILDDIR)/%.elf
	@echo
	@echo " Generating final output for FLASH..."
	@echo " avr-objcopy -O ihex -R .eeprom $< $@";\
	avr-objcopy -O ihex -R .eeprom $< $@ 2> /dev/null

$(BUILDDIR)/%.eep: $(BUILDDIR)/%.elf
	@echo
	@echo " Generating final output for EEPROM..."
	@echo " avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@";\
	avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ 2> /dev/null

$(BUILDDIR)/%.lss: $(BUILDDIR)/%.elf
	@echo
	@echo " Creating extended listing file from elf output..."
	@echo " avr-objdump -h -S $< > $@"; avr-objdump -h -S $< > $@

$(BUILDDIR)/%.sym: $(BUILDDIR)/%.elf
	@echo
	@echo " Generating symbol table from elf output..."
	@echo " avr-nm -n $< > $@"; avr-nm -n $< > $@

$(BUILDDIR)/%.elf: $(BUILDDIR)/%.o
	@echo
	@echo " Linking..."
	@echo " $(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)"; $(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
	@echo " "; avr-size -C --mcu=$(MCU) $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo " Compiling..."
	@echo " $(CC) $(CFLAGS) -c $< -o $@"; $(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR)/master.* $(BUILDDIR)/slave.* "; $(RM) -r $(BUILDDIR)/master.* $(BUILDDIR)/slave.*

tester:
	@echo " Testing..."

ticket:
	@echo " Spikes..."

.PHONY: all clean
