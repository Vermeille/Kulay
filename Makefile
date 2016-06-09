CXX=clang++
CXXFLAGS=-Wall -Wextra -ggdb3

BISON_GEN=parser.cpp
FLEX_GEN=lexer.cpp
SRC=$(BISON_GEN) $(FLEX_GEN)
OBJS=$(SRC:.cpp=.o)

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OUTPUT_OPTION) $^

$(BISON_GEN): grammar.yy
	bison -d $^ $(OUTPUT_OPTION)

$(FLEX_GEN): lexer.ll
	flex $(OUTPUT_OPTION) $^

clean:
	rm -f $(OBJS) all $(BISON_GEN) $(BISON_GEN:.cpp=.hpp) $(FLEX_GEN)
