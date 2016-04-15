SHELL         := /bin/bash

CXX           = g++ -std=c++11
OPTFLAG       = -O1
CXXFLAGS      = -std=c++11 -Wall
INCLUDES      = -I$(shell pwd)/include
STATIC_FLAGS  = -L$(shell pwd)/lib
STATIC_LIBS   = -lSOIL
DYNAMIC_FLAGS = -Wl,-rpath $(shell pwd)/lib
DYNAMIC_LIBS  = -lassimp -lglfw3 -lpthread -lGLEW -lGL -lXrandr -lXi -lX11 -ldl -lXcursor -lXxf86vm -lXinerama

SRCDIR        = src
OBJDIR        = objs
BINDIR        = bin
RELEASE_DIR   = release
DEBUG_DIR     = debug

PROD          = $(BINDIR)/$(RELEASE_DIR)/main
DEBUG_PROD    = $(BINDIR)/$(DEBUG_DIR)/main

PROFILER      = valgrind

HDRS          = $(wildcard $(SRCDIR)/*.hpp)
SRCS          = $(wildcard $(SRCDIR)/*.cpp)
OBJS          = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/$(RELEASE_DIR)/%.o, $(SRCS))
DEBUG_OBJS    = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/$(DEBUG_DIR)/%.o, $(SRCS))

all: $(PROD)
	@echo 'Compilation finished (release).'

debug_all: $(DEBUG_PROD)
	@echo 'Compilation finished (debug).'

$(OBJS): $(OBJDIR)/$(RELEASE_DIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(RELEASE_DIR)
	@echo [CXX] '\t' $@
	@$(CXX) $(OPTFLAG) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

$(DEBUG_OBJS): $(OBJDIR)/$(DEBUG_DIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(DEBUG_DIR)
	@echo [CXX] '\t' $@
	@$(CXX) $(OPTFLAG) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

$(PROD): $(OBJS)
	@mkdir -p $(BINDIR)/$(RELEASE_DIR)
	@echo [CXX] '\t' $@
	@$(CXX) -o $@ $(LDFLAGS) $^ $(STATIC_FLAGS) $(STATIC_LIBS) $(DYNAMIC_FLAGS) $(DYNAMIC_LIBS)

$(DEBUG_PROD): $(DEBUG_OBJS)
	@mkdir -p $(BINDIR)/$(DEBUG_DIR)
	@echo [CXX] '\t' $@
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
	rm -f $(OBJDIR)/$(RELEASE_DIR)/*.o
	rm -f $(OBJDIR)/$(DEBUG_DIR)/*.o
	@echo Clean done.

