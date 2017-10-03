CC := avr-gcc

# Microcontroller instruction set architecture
MCU := atmega328p

# Optimization level, can be [0, 1, 2, 3, s]. 0 turns off optimization.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT := s

SRCDIR := src
BUILDDIR := ../build

SRCEXT := c
SOURCES := $(shell find  $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
ELFS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.elf))
CFLAGS := -O$(OPT) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
		  -Wall -Wstrict-prototypes -mmcu=$(MCU) -D__TWEAK__ 

TARGETS :=  

#all: $(BUILDDIR)/$(TARGET).elf $(BUILDDIR)/$(TARGET).hex $(BUILDDIR)/$(TARGET).eep \
   	 $(BUILDDIR)/$(TARGET).lss $(BUILDDIR)/$(TARGET).sym

all: $(BUILDDIR)/%.elf $(BUILDDIR)/%.hex $(BUILDDIR)/%.eep \
   	 $(BUILDDIR)/%.lss $(BUILDDIR)/%.sym

$(BUILDDIR)/%.hex: $(BUILDDIR)/%.elf
	@echo
	@echo " Generating final output for FLASH..."
	@echo " avr-objcopy -O ihex -R .eeprom $< $@"
	avr-objcopy -O ihex -R .eeprom $< $@

$(BUILDDIR)/%.eep: $(BUILDDIR)/%.elf
	@echo
	@echo " Generating final output for EEPROM..."
	@echo " avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex $< $@"
	avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

$(BUILDDIR)/%.lss: $(BUILDDIR)/%.elf
	@echo
	@echo " Creating extended listing file from elf output..."
	@echo " avr-objdump -h -S $< > $@"; avr-objdump -h -S $< > $@

$(BUILDDIR)/%.sym: $(BUILDDIR)/%.elf
	@echo
	@echo " Generating symbol table from elf output..."
	@echo " avr-nm -n $< > $@"; avr-nm -n $< > $@

$(BUILDDIR)/%.elf: $(OBJECTS)
	@echo
	@echo " Linking..."
	@echo " $(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)"; $(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo " Compiling..."
	@echo " $(CC) $(CFLAGS) -c $< -o $@"; $(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

tester:
	@echo " Testing..."

ticket:
	@echo " Spikes..."

.PHONY: all clean
