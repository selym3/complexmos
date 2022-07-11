SOURCES = Parser.cpp Token.cpp Operator.cpp Bracket.cpp Tree.cpp Function.cpp Variable.cpp Constant.cpp
HEADERS = Parser.hpp Token.hpp Operator.hpp Bracket.hpp Tree.hpp Function.hpp Variable.hpp Constant.hpp Number.hpp

OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

TARGET = parser_test.cpp
EXE = test

CXXFLAGS = -std=c++20
CXXFLAGS += -g -Wall -Wformat

%.o:%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(TARGET): $(SOURCES) $(HEADERS)
# 	$(CXX) $()

$(EXE): $(TARGET) $(OBJECTS) # $(HEADERS)
	$(CXX) $(CXXFLAGS) $^ -o $@

all: $(EXE)
	./$(EXE)

clean:
	rm *.o 
