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
INC := -I include #-I $(OGREDIR) -I $(OGREDIR)/Overlay -I $(OISDIR)
#INC := $(INC) -I $(OGREBULLETDIR)/Collisions/include -I $(OGREBULLETDIR)/Dynamics/include -I $(BULLETDIR)
#LIBDIR := -L/usr/local/lib/OgreBullet
#LIB := -lOgreMain -lBulletDynamics -lConvexDecomposition -lBulletSoftBody -lLinearMath -lOgreOverlay
#LIB := $(LIB) -lOIS-1.3.0 -lboost_system -lX11 -lXt -lXaw -lpthread -ldl -lboost_thread -lfreeimage -lzzip
#LIB := $(LIB) -lz -lfreetype -lrt -lxcb -lSM -lICE -lXext -lXmu -lXpm -lbz2 -lpng16 -lharfbuzz -lXau
#LIB := $(LIB) -lXdmcp -luuid -lglib-2.0 -lgraphite2 -lpcre -lOgreBulletCollisions -lOgreBulletDynamics

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ $(LIBDIR) $(LIB) -o $(TARGET) "; $(CC) $(LIBDIR) $(LIB) $^ -o $(TARGET) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

tester:
	@echo " Testing..."

ticket:
	@echo " Spikes..."

.PHONY: clean
