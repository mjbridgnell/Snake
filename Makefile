CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lcurses

TARGET = snake

SRCS = main.cpp game.cpp snake.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)