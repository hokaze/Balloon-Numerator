CXX      = g++
CXXFLAGS = -Wall -O3
LDFLAGS  =

TARGET = main
SRCS   =  balloonist.cpp  baseObject.cpp  enemy.cpp  gfx.cpp  level.cpp  main.cpp  numberBalloon.cpp  platform.cpp  spiky.cpp  textDisplay.cpp  timer.cpp
OBJS   = $(SRCS:.cpp=.o)
DEPS   = $(SRCS:.cpp=.depends)


.PHONY: clean all

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)

.cc.o:
		$(CXX) $(CXXFLAGS) -c $< -o $@

%.depends: %.cpp
		$(CXX) -M $(CXXFLAGS) $< > $@

clean:
		rm -f $(OBJS) $(DEPS) $(TARGET)

-include $(DEPS)