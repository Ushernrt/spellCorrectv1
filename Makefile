TARGETPATH:=./Bin
TARGET:=./Bin/offline.exe
SRCOFFLINE:=./srcOffline/*.cc

CXX:=g++

FLAGS:= -std=c++11

$(TARGET) : $(SRCOFFLINE)
	$(CXX) $^ -o $@ $(FLAGS)

clean:
	rm -rf TARGET 
