CXX        = g++ -std=c++11
OPTFLAG    = -O1
CXXFLAGS   = -pedantic -std=c++11 -Wall
LDFLAGS    = -L./lib -I./include
LIBS       = -lglfw3 -lpthread -lGLEW -lGLU -lGL -lrt -lXrandr \
             -lXxf86vm -lXi -lXinerama -lX11 -ldl -lXcursor
PROD       = main

HDRS       = $(shell ls *.h)
SRCS       = $(shell ls *.cpp)
OBJS       = $(patsubst %.cpp, %.o, $(SRCS))

all: $(PROD)

$(OBJS): %.o: %.cpp
	mkdir -p objs
	$(CXX) -c $(OPTFLAG) $(CXXFLAGS) $< -o objs/$@

$(PROD): $(OBJS)
	mkdir -p bin
	$(CXX) -o bin/$(PROD) $(LDFLAGS) objs/$^ $(LIBS)

run: $(PROD)
	bin/$(PROD)

clean:
	rm -f bin/$(PROD)
	rm -f objs/*.o
