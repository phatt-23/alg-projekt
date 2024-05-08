CC := g++
CFLAGS := -std=c++23 -Wall -Wextra
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
PROGRAM = iotdecoder

all:
	@echo "Compiling and creating doxy documentation..."
	@$(CC) $(SRC_FILES) $(CFLAGS) -o $(PROGRAM)
	@doxygen Doxyfile

clean:
	@echo "Removing the executable and doxy documentation..."
	@rm $(PROGRAM)
	@rm -r doxy

