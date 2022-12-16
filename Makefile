# Set project directory one level above of Makefile directory. $(CURDIR) is a GNU make variable containing the path to the current working directory
PROJDIR := $(realpath $(CURDIR))
SOURCEDIR := $(PROJDIR)/src
BUILDDIR := $(PROJDIR)/build

MAIN := $(PROJDIR)/src/main.cpp

# Name of the final executable
APP = MyJsonLib

# Decide whether the commands will be shwon or not
VERBOSE = TRUE

# Create the list of directories
DIRS = MyJsonLib

SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))

# Generate the GCC includes parameters by adding -I before each source folder
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))

# Add this list to VPATH, the place make will look for the source files
VPATH = $(SOURCEDIRS)

# Create a list of *.cpp sources in DIRS
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.cpp))
SOURCES += $(MAIN)

# Define objects for all sources
OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:.cpp=.o))

# Name the compiler
CC = g++
LDFLAGS :=
CXXFLAGS := -W -Wall -std=c++11

# OS specific part
RM = rm -rf 
RMDIR = rm -rf 
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null
SEP=/

# Remove space after separator
PSEP = $(strip $(SEP))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
	HIDE =  
else
	HIDE = @
endif

# Define the function that will generate each rule
define generateRules
$(1)/%.o: %.cpp
	$(HIDE)echo Building $$@
	$(HIDE)$(CC) $(CXXFLAGS) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<)
endef

.PHONY: all clean directories 

all: directories $(APP)

$(APP): $(OBJS)
	$(HIDE)echo Linking $@
	$(HIDE)$(CC) $(OBJS) -o $(APP) $(LDFLAGS)

# Generate rules
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

$(BUILDDIR)/main.o: $(SOURCEDIR)/main.cpp
	$(HIDE)echo Building $$@
	$(HIDE)$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $(INCLUDES) -o $@ $<

directories: 
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)

re: clean \
	all

# Remove all objects, dependencies and executable files generated during the build
clean:
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(BUILDDIR)/main.o
	$(HIDE)$(RM) $(APP) $(ERRIGNORE)
	@echo Cleaning done ! 