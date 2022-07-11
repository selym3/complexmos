
SOURCES = Parser.cpp Token.cpp Operator.cpp Bracket.cpp Tree.cpp Function.cpp Variable.cpp Constant.cpp
HEADERS = Parser.hpp Token.hpp Operator.hpp Bracket.hpp Tree.hpp Function.hpp Variable.hpp Constant.hpp Number.hpp

OBJECTS = $(addprefix ./bin/, $(addsuffix .o, $(basename $(SOURCES))))

TARGET = parser_test.cpp
EXE = test.o

CXXFLAGS = -std=c++20
CXXFLAGS += -g -Wall -Wformat

./bin/%.o:%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(TARGET): $(SOURCES) $(HEADERS)
# 	$(CXX) $()

$(EXE): $(TARGET) $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $^ -o $@

all: $(OBJECTS)
	@echo Built parse library

clean:
	rm *.o 
