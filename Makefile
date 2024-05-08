CC := g++
CFLAGS := -std=c++23 -Wall -Wextra
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
PROGRAM = iotdecoder

all:
	$(CC) $(SRC_FILES) $(CFLAGS) -o$(PROGRAM)

clean:
	rm $(PROGRAM)
