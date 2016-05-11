SHELL         := /bin/bash

CXX           = g++ -std=c++11
OPTFLAG       = -O1
CXXFLAGS      = -std=c++11 -Wall
INCLUDES      = -I$(shell pwd)/include
INCLUDES     += -I/usr/include/bullet
INCLUDES     += -I./src
STATIC_FLAGS  = -L$(shell pwd)/lib
STATIC_LIBS   = -lSOIL
DYNAMIC_FLAGS = -Wl,-rpath $(shell pwd)/lib
DYNAMIC_LIBS  = -lassimp
DYNAMIC_LIBS += -lglfw3 -lpthread -lGLEW -lGL -lXrandr -lXi -lX11 -ldl -lXcursor -lXxf86vm -lXinerama
DYNAMIC_LIBS += -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lSDL -lSDL_mixer -lCEGUIBase-0  -lCEGUIOpenGLRenderer-0

SRCDIR        = src
OBJDIR        = objs
BINDIR        = bin
RELEASE_DIR   = release
DEBUG_DIR     = debug

PROD          = $(BINDIR)/$(RELEASE_DIR)/main
DEBUG_PROD    = $(BINDIR)/$(DEBUG_DIR)/main

PROFILER      = valgrind

HDRS         := $(shell find $(SRCDIR) -name '*.hpp')
SRCS         := $(shell find $(SRCDIR) -name '*.cpp')
OBJS         := $(subst $(SRCDIR), $(OBJDIR)/$(RELEASE_DIR), $(SRCS:%.cpp=%.o))
DEBUG_OBJS   := $(subst $(SRCDIR), $(OBJDIR)/$(DEBUG_DIR), $(SRCS:%.cpp=%.o))

all: $(PROD)
	@echo 'Compilation finished (release).'

debug_all: $(DEBUG_PROD)
	@echo 'Compilation finished (debug).'

$(OBJS): $(OBJDIR)/$(RELEASE_DIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.hpp
	@mkdir -p $(@D)
	@echo -e [CXX] '\t' $@
	@$(CXX) $(OPTFLAG) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

$(DEBUG_OBJS): $(OBJDIR)/$(DEBUG_DIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.hpp
	@mkdir -p $(@D)
	@echo -e [CXX] '\t' $@
	@$(CXX) $(OPTFLAG) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

$(PROD): $(OBJS)
	@mkdir -p $(BINDIR)/$(RELEASE_DIR)
	@echo -e [CXX] '\t' $@
	@$(CXX) -o $@ $(LDFLAGS) $^ $(STATIC_FLAGS) $(STATIC_LIBS) $(DYNAMIC_FLAGS) $(DYNAMIC_LIBS)

$(DEBUG_PROD): $(DEBUG_OBJS)
	@mkdir -p $(BINDIR)/$(DEBUG_DIR)
	@echo -e [CXX] '\t' $@
	@$(CXX) -o $@ $(LDFLAGS) $^ $(STATIC_FLAGS) $(STATIC_LIBS) $(DYNAMIC_FLAGS) $(DYNAMIC_LIBS)

run: all
	@echo Running $(PROD).
	@$(PROD)

test: CXXFLAGS += -DDEBUG -g
test: debug_all
	@echo Running $(PROFILER) $(DEBUG_PROD).
	@$(PROFILER) $(DEBUG_PROD)

clean:
	rm -f $(PROD)
	rm -f $(DEBUG_PROD)
	rm -rf $(OBJDIR)/$(RELEASE_DIR)/
	rm -rf $(OBJDIR)/$(DEBUG_DIR)/
	@echo Clean done.

docs: Doxyfile
	doxygen Doxyfile

Doxyfile:
	doxygen -g

