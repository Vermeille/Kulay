CXX=clang++
CXXFLAGS=-Wall -Wextra -ggdb3 -std=c++14

BISON_GEN=parser.cpp
FLEX_GEN=lexer.cpp
SRC=instr.cpp $(BISON_GEN) $(FLEX_GEN)
OBJS=$(SRC:.cpp=.o)

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OUTPUT_OPTION) $^

$(BISON_GEN): grammar.yy
	bison -d --debug $^ $(OUTPUT_OPTION)

$(FLEX_GEN): lexer.ll
	flex $(OUTPUT_OPTION) $^

clean:
	rm -f $(OBJS) all $(BISON_GEN) $(BISON_GEN:.cpp=.hpp) $(FLEX_GEN)
