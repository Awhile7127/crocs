CC=g++
CFLAGS=-I.
FILES=src/*.cpp
OUTPUT=crocs

$(OUTPUT):
	$(CC) $(CFLAGS) $(FILES) -o $(OUTPUT)
