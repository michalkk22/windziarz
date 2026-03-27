CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Icommon -Ilibs
LDFLAGS = -lrt

# executables
TARGETS = bin/person bin/manager bin/elevator

# source directories
COMMON_SRC := $(shell find common -name "*.cpp")
PERSON_SRC := $(shell find person -name "*.cpp")
MANAGER_SRC := $(shell find manager -name "*.cpp")
ELEVATOR_SRC := $(shell find elevator -name "*.cpp")

# object files
OBJ_COMMON := $(COMMON_SRC:.cpp=.o)
OBJ_PERSON := $(PERSON_SRC:.cpp=.o)
OBJ_MANAGER := $(MANAGER_SRC:.cpp=.o)
OBJ_ELEVATOR := $(ELEVATOR_SRC:.cpp=.o)

.PHONY: all clean bin

# default target
all: bin $(TARGETS)

# linking
bin/person: $(OBJ_COMMON) $(OBJ_PERSON)
	$(CXX) $^ -o $@ $(LDFLAGS)

bin/manager: $(OBJ_COMMON) $(OBJ_MANAGER)
	$(CXX) $^ -o $@ $(LDFLAGS)

bin/elevator: $(OBJ_COMMON) $(OBJ_ELEVATOR)
	$(CXX) $^ -o $@ $(LDFLAGS)

# compile rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# cleanup
clean:
	rm -f $(TARGETS)
	find . -name "*.o" -delete