CXX=g++

COMPRESS_CODE=compress.cpp
COMPRESS_CODE_OUT=compress.exe
DECOMPRESS_CODE=decompress.cpp
DECOMPRESS_CODE_OUT=decompress.exe

all:
	$(compress)
	$(decompress)

compress:
	$(CXX) $(COMPRESS_CODE) -o $(COMPRESS_CODE_OUT)
	./$(COMPRESS_CODE_OUT)

decompress:
	$(CXX) $(DECOMPRESS_CODE) -o $(DECOMPRESS_CODE_OUT)
	./$(DECOMPRESS_CODE_OUT)

clean:
	del *.exe