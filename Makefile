#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need GLFW (http://www.glfw.org):
# Linux:
#   apt-get install libglfw-dev
# Mac OS X:
#   brew install glfw
# MSYS2:
#   pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw
#

#CXX = g++
#CXX = clang++

TARGET = main.cpp
EXE = main

IMGUI_DIR = ./libs/imgui
IMPLOT_DIR = ./libs/implot
PARSE_DIR = ./parse

SOURCES = $(wildcard ./src/*.cpp)
HEADERS = $(wildcard ./src/*.hpp) $(wildcard ./src/*.h)
OBJECTS = $(addprefix ./bin/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))

LINUX_GL_LIBS = -lGL
UNAME_S := $(shell uname -s)

CXXFLAGS = -std=c++20 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(IMPLOT_DIR)
CXXFLAGS += -g -Wall -Wformat
LIBS = $(PARSE_DIR)/bin/*.o $(IMGUI_DIR)/bin/*.o $(IMPLOT_DIR)/bin/*.o


##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += -L/usr/local/lib -L/opt/local/lib -L/opt/homebrew/lib
	#LIBS += -lglfw3
	LIBS += -lglfw

	CXXFLAGS += -I/usr/local/include -I/opt/local/include -I/opt/homebrew/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif



##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

./bin/%.o : ./src/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXE): $(TARGET) $(OBJECTS) 
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)
	./$(EXE)

clean:
	rm -f $(EXE) $(OBJS)
