CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
TARGET   := pullweight

# All .cpp files in src/, src/validators/, plus main.cpp
SRCS := $(wildcard src/*.cpp) $(wildcard src/validators/*.cpp) main.cpp
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	-cmd /C "del /Q /F $(subst /,\,$(OBJS)) $(TARGET).exe 2>nul"
else
	rm -f $(OBJS) $(TARGET)
endif

.PHONY: all clean
