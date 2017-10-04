CC := g++

SRCDIR := src
BUILDDIR := build
#OGREDIR := /usr/include/OGRE
#OISDIR := /usr/include/OIS
#BULLETDIR := /usr/include/bullet
#OGREBULLETDIR := ~/Workspace/Git/ogrebullet
TARGET := thesis

SRCEXT := cc
SOURCES := $(shell find  $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -std=gnu++14 -fPIC
INC := -Iinc -I/usr/local/include -I/usr/local/include/cegui-0
#LIBDIR := -L/usr/local/lib/OgreBullet

LIB := $(shell pkg-config --libs opencv)
LIB := $(LIB) -lpthread
LIB := $(LIB) -lfreenect
LIB := $(LIB) -lIrrlicht

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
