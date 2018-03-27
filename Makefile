SOURCES:=$(wildcard ./src/*.cc)
SOURCESCLIENT:=./srcClient/client.c
OBJS:=$(patsubst %.cc, %.o, $(SOURCES))
LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -std=c++11

EXE:=./Bin/server.exe
EXECLIENT:=./Bin/client.server

$(EXE) : $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS) $(LIBS)
	gcc -o	$(EXECLIENT) $(SOURCESCLIENT) 


$(EXECLIENT) : $(SOURCESCLIENT)
	gcc -o $@ $^

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)


