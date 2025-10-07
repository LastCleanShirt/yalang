CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

TARGET = bin/yalang

SRCS = main.cpp Lexer.cpp Parser.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
