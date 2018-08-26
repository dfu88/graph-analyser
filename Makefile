CXXFLAGS =	-O2 -Wall -fmessage-length=0 -Wno-unused-result

CXX = g++ -std=c++11

OBJS = main.o SetOfStrings.o StringRelation.o SetControl.o SetUI.o

SRCS = main.cpp SetOfStrings.cpp StringRelation.cpp SetControl.cpp SetUI.cpp

TARGET = calculator.o


all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

debug:
	$(CXX) -D_DEBUG -o $(TARGET) $(SRCS)
	
clean:
	rm -f $(OBJS) $(TARGET)

