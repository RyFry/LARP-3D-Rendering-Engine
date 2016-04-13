
CXX        = g++ -std=c++11
OPTFLAG    = -O1
CXXFLAGS   = -pedantic -std=c++11 -Wall
INCLUDES   = -I$(shell pwd)/include
LDFLAGS    = -L$(shell pwd)/lib -Wl,-rpath $(shell pwd)/lib
LIBS       = -lassimp -lglfw3 -lpthread -lGLEW -lGL -lXrandr -lXi -lX11 -ldl -lXcursor -lXxf86vm -lXinerama

SRCDIR     = src
OBJDIR     = objs
BINDIR     = bin

PROD       = $(BINDIR)/main

HDRS       = $(wildcard $(SRCDIR)/*.hpp)
SRCS       = $(wildcard $(SRCDIR)/*.cpp)
OBJS       = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

all: $(PROD)
	@echo Compilation finished.

thing: a.cpp
	$(CXX) -o $@ $^

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	@echo -e [CXX] '\t' $@
	@$(CXX) $(OPTFLAG) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

$(PROD): $(OBJS)
	@mkdir -p $(BINDIR)
	@echo -e [CXX] '\t' $@
	@$(CXX) -o $@ $(LDFLAGS) $^ $(LIBS)

run: all
	$(PROD)

clean:
	@rm -f $(PROD)
	@rm -f $(OBJDIR)/*.o
	@echo Clean done.
