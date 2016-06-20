ifeq ($(WARN),1)
ifeq ($(CXX),g++)
WARN_FLAGS = -O3 -g -Wall -Wextra -Wabi -Wctor-dtor-privacy -Wnon-virtual-dtor -Wreorder -Wstrict-null-sentinel -Woverloaded-virtual -Wshadow -Wcast-align -Wpointer-arith -Wwrite-strings -Wundef -Wredundant-decls -Werror # -Weffc++
else ifeq ($(CXX),clang++)
WARN_FLAGS = -O3 -g -Werror
else ifeq ($(CXX),icpc)
WARN_FLAGS = -O3 -ipo -g -Wall -wd981 -wd383 -wd2259 -Werror # -Weffc++
endif
endif

ifeq ($(CPP11),1)
STD_FLAGS = -std=c++0x
endif

BIN = adocker
OBJECTS = adocker.o

all: $(BIN)

install:
	cp adocker /usr/local/bin/adocker

$(BIN): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(WARN_FLAGS) $(STD_FLAGS) $(LINKFLAGS)

%.o: %.cpp
	$(CXX) $(WARN_FLAGS) $(STD_FLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(BIN)
