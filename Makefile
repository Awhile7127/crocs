CC=g++
CFLAGS=-I. -ljsoncpp
FILES=src/*.cpp
OUTPUT=crocs

$(OUTPUT):
	$(CC) $(CFLAGS) $(FILES) -o $(OUTPUT)
