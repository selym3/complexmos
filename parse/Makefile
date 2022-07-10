SOURCES = Parser.cpp Token.cpp Operator.cpp Bracket.cpp
HEADERS = Parser.hpp Token.hpp Operator.hpp Bracket.hpp Number.hpp

OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

TARGET = parser_test.cpp
EXE = test

CXXFLAGS = -std=c++20
CXXFLAGS += -g -Wall -Wformat

%.o:%.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(TARGET): $(SOURCES) $(HEADERS)
# 	$(CXX) $()

$(EXE): $(TARGET) $(OBJECTS) # $(HEADERS)
	$(CXX) $(CXXFLAGS) $^ -o $@

all: $(EXE)
	./$(EXE)
