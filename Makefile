# Compiler
CXX = g++

# Flags
CXXFLAGS = -Wall -g -O3

# Target file name
TARGET = main.out

# Source Files
SRCS = main.cpp src/printStandard.cpp src/player.cpp src/utils.cpp src/map.cpp src/rayCast.cpp src/game.cpp

# Linker Stuff
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lGL

# Object Files
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET) run

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
