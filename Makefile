PROGRAM_NAME = codility
CXX = g++
RM := rm -f
CXXFLAGS = -std=c++17 -g3 -pthread -gdwarf-4 -DLinux -fPIC -Wno-deprecated -pipe
STRICT_FLAGS = -Wall -Werror -Wextra -Wpedantic -Wvla -Wnull-dereference -Wswitch-enum 

# tell me where to find boost
BOOST_INC = /usr/local/include/boost
BOOST_LIB = /usr/local/lib

# "compiler=..." will override CXX
ifeq "clang" "$(compiler)"
    CXX = /opt/clang-latest/bin/clang++
else ifeq "gcc" "$(compiler)"
    CXX = g++
else ifneq "" "$(compiler)"
    $(error unknown compiler $(compiler))
endif

# default to debug
# can override with config=(anything).  e.g. make -j2 config=release -f Makefile
config := debug

ifeq "debug" "$(config)"
    CXXFLAGS += -O0
else
    CXXFLAGS += -DNDEBUG -O3
endif

CXXFLAGS += -I $(BOOST_INC) $(STRICT_FLAGS)

LIBRARY_DIRECTORIES = -L$(BOOST_LIB)
LIBRARY_COMMON = -ldl -lrt

link_parameters = \
    $(LIBRARY_DIRECTORIES) \
    $(LIBRARY_COMMON)

OBJS = main.o base.neg.two.o binarygap.o oddoccurrences.o cyclicrotation.o

$(PROGRAM_NAME): $(OBJS) 
	@echo " "
	@echo "Building $@..."
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(link_parameters)


main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

base.neg.two.o: base.neg.two.cpp
	$(CXX) -c $(CXXFLAGS) base.neg.two.cpp

binarygap.o: binarygap.cpp
	$(CXX) -c $(CXXFLAGS) binarygap.cpp

oddoccurrences.o: oddoccurrences.cpp
	$(CXX) -c $(CXXFLAGS) oddoccurrences.cpp

cyclicrotation.o: cyclicrotation.cpp
	$(CXX) -c $(CXXFLAGS) cyclicrotation.cpp


clean:
	@-$(RM) $(OBJS) 2>&1 >/dev/null
	@-$(RM) $(PROGRAM_NAME)
