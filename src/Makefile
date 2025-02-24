CXX = c++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror
INCLUDES = -I ../include
TARGETS = test_cpppack test_cppunpack

.PHONY: all
all: $(TARGETS)
	for target in $(TARGETS); do ./$$target && echo test $$target passed; done

test_cpppack.cpp.o: test_cpppack.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<
test_cppunpack.cpp.o: test_cppunpack.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

test_cpppack: test_cpppack.cpp.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $<
test_cppunpack: test_cppunpack.cpp.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGETS)
	rm -f *.o
