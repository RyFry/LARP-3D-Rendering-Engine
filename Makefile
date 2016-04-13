
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

PROD          = $(BINDIR)/main

HDRS          = $(wildcard $(SRCDIR)/*.hpp)
SRCS          = $(wildcard $(SRCDIR)/*.cpp)
OBJS          = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

all: $(PROD)
	@echo Compilation finished.

thing: a.cpp
	$(CXX) -o $@ $^

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	@echo [CXX] '\t' $@
	@$(CXX) $(OPTFLAG) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

$(PROD): $(OBJS)
	@mkdir -p $(BINDIR)
	@echo [CXX] '\t' $@
	@$(CXX) -o $@ $(LDFLAGS) $^ $(STATIC_FLAGS) $(STATIC_LIBS) $(DYNAMIC_FLAGS) $(DYNAMIC_LIBS)

run: all
	$(PROD)

clean:
	@rm -f $(PROD)
	@rm -f $(OBJDIR)/*.o
	@echo Clean done.

