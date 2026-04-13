CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRCS     = dfa_matching not_so_naive karp_rabin tuned_boyer_moore galil_giancarlo
BINS     = $(SRCS)
TEST_BIN = test_all

.PHONY: all clean test

all: $(BINS) $(TEST_BIN)

$(BINS): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TEST_BIN): test_all.cpp $(addsuffix .cpp, $(SRCS))
	$(CXX) $(CXXFLAGS) -o $@ test_all.cpp

clean:
	rm -f $(BINS) $(TEST_BIN)

test: $(TEST_BIN)
	./$(TEST_BIN)
