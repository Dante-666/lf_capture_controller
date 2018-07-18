CC := g++

SRCDIR := src
BUILDDIR := build
TARGET := thesis

SRCEXT := cc
SOURCES := $(shell find  $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -std=gnu++14 -fPIC
INC := -Iinc -I/usr/include/irrlicht -I/usr/local/include -I/usr/local/include/cegui-0

LIB := $(shell pkg-config --libs opencv)
LIB += -lpthread
LIB += -lfreenect
LIB += -lIrrlicht
LIB += -lCEGUIIrrlichtRenderer-0
LIB += -lCEGUIBase-0

$(TARGET): $(OBJECTS) | subsystem
	@echo " Linking..."
	@echo " $(CC) $^ $(LIBDIR) $(LIB) -o $(TARGET) "; $(CC) $^ $(LIBDIR) $(LIB) -o $(TARGET) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

subsystem:
	$(MAKE) -C controller

clean:
	@echo " Cleaning subsystem..."; $(MAKE) -C controller clean
	@echo " Cleaning...";
	@echo " $(RM) -r build/*.o"; $(RM) -r build/*.o
tester:
	@echo " Testing..."

ticket:
	@echo " Spikes..."

.PHONY: clean
