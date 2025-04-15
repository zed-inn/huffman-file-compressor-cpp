CXX=g++

MAIN_CODE=main.cpp
MAIN_CODE_OUT=huffman.exe

all:
	$(main)

main:
	$(CXX) $(MAIN_CODE) -o $(MAIN_CODE_OUT)

clean:
	del *.exe