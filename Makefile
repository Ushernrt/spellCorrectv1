SOURCES:=$(wildcard ./src/*.cc)
OBJS:=$(patsubst %.cc, %.o, $(SOURCES))
LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -std=c++11

EXE:=./Bin/server.exe

$(EXE) : $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS) $(LIBS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)


