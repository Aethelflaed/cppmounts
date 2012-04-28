include Makefile.conf

srcdir := src
bindir := bin
libdir := lib
objdir := obj
staticobjdir := $(objdir)/static
sharedobjdir := $(objdir)/shared
incdir := include

srcsdir := $(srcdir)
srcsdir += $(addprefix $(srcdir)/, $(modules))
staticobjsdir := $(staticobjdir)
staticobjsdir += $(addprefix $(staticobjdir)/, $(modules))
sharedobjsdir := $(sharedobjdir)
sharedobjsdir += $(addprefix $(sharedobjdir)/, $(modules))
objsdir := $(objdir)
objsdir += $(addprefix $(objdir)/, $(modules))

srcs := $(foreach sdir, $(srcsdir), $(wildcard $(sdir)/*.cpp))
staticobjs := $(patsubst $(srcdir)/%.cpp, $(staticobjdir)/%.o, $(foreach sdir, $(srcsdir), $(wildcard $(sdir)/*.cpp)))
sharedobjs := $(patsubst $(srcdir)/%.cpp, $(sharedobjdir)/%.o, $(foreach sdir, $(srcsdir), $(wildcard $(sdir)/*.cpp)))

localdirs :=\
	$(staticobjsdir)\
	$(sharedobjsdir)\
	$(bindir)\
	$(libdir)\
	$(incdir)

vpath %.cpp $(srcsdir)

define make-static-objs-goal
$1/%.o: %.cpp
	$(CPP) -c $$< -o $$@ $(CPPSTATICFLAGS) $(INCLUDES)
endef
define make-shared-objs-goal
$1/%.o: %.cpp
	$(CPP) -c $$< -o $$@ $(CPPSHAREDFLAGS) $(INCLUDES)
endef

shared=$(bindir)/lib$(program_name).so
static=$(bindir)/lib$(program_name).a

all: $(localdirs) $(shared) $(static)

clean:
	$(RM) -r $(objdir)
	$(RM) -r $(bindir)

$(shared): $(sharedobjs)
	$(LD) $(LDFLAGS) $(LIBS) $^ -o $@

$(static): $(staticobjs)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

$(localdirs):
	mkdir -p $@

$(foreach odir, $(staticobjsdir), $(eval $(call make-static-objs-goal, $(odir))))
$(foreach odir, $(sharedobjsdir), $(eval $(call make-shared-objs-goal, $(odir))))

