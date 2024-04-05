#########################################################################################
BOLD  := $(shell tput bold)
<U> 	:= $(shell tput smul)
</U> 	:= $(shell tput rmul)
RESET := $(shell tput sgr0)

BLACK   := $(shell tput setaf 0)
RED     := $(shell tput setaf 1)
GREEN   := $(shell tput setaf 2)
YELLOW  := $(shell tput setaf 3)
BLUE    := $(shell tput setaf 4)
MAGENTA := $(shell tput setaf 5)
CYAN    := $(shell tput setaf 6)
WHITE   := $(shell tput setaf 7)

TAB := $(shell echo -e "\t")

BD_SYS := "[$(<U>)BUILD$(</U>)]"
#########################################################################################
LANG := cpp
ifeq ($(LANG),cpp)
    CC := g++
    CFLAGS := -std=c++23 -Wall -Wextra 
else ifeq ($(LANG),c)
    CC := gcc
    CFLAGS := -std=c99 -Wall -Wextra -Wno-unused-result -Wall -Wextra -g -lm
endif

#________________________________________________________________________________________
SHOW_CMD ?= @
LDFLAGS  :=
LIBS     := 
OPTI	   ?= -O3
VAL      := valgrind -q --tool=memcheck --track-origins=no --error-exitcode=1 --track-origins=yes

ASM_C   	:= nasm
ASM_FLAGS := -f elf64
SRC_DIR 	:= src
OBJ_DIR 	:= target/debug
BIN_DIR 	:= target

SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.cpp) 
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)))

ASM_SRCS := $(wildcard $(SRC_DIR)/*.asm)
ASM_OBJS := $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.o, $(ASM_SRCS))

TARGET 		 := $(BIN_DIR)/cxx_program
ASM_TARGET := $(BIN_DIR)/asm_program


.PHONY: all clean dirs check build run asm asmr
all: build

#________________________________________________________________________________________
build: dirs check_modification $(TARGET) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(BOLD)$(BLUE)$(BD_SYS) Compiling $(<U>)C$(</U>): \"$<\" to an object files. $(RESET)"
	$(SHOW_CMD)$(CC) $(CFLAGS) $(OPTI) $(LIBS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "$(BOLD)$(BLUE)$(BD_SYS) Comiling $(<U>)C++$(</U>): \"$<\" to an object file. $(RESET)"
	$(SHOW_CMD)$(CC) $(CFLAGS) $(OPTI) $(LIBS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@echo "$(BOLD)$(BLUE)$(BD_SYS) Compiling $(<U>)ASM$(</U>): \"$<\" to an object file. $(RESET)"
	$(SHOW_CMD)$(ASM_C) $(ASM_FLAGS) $< -o $@

$(TARGET): $(OBJS) $(ASM_OBJS)
	@echo "$(BOLD)$(BLUE)$(BD_SYS) Linking with '$(<U>)$(CC)$(</U>)' into an executable ./$(<U>)$(TARGET)$(</U>) $(RESET)"
	$(SHOW_CMD)$(CC) $(CFLAGS) $(OPTI) $(LDFLAGS) $^ -o $@
#________________________________________________________________________________________ 
run: build
	@echo "$(BOLD)$(GREEN)$(BD_SYS) Running the executable. $(RESET)"
	$(SHOW_CMD)./$(TARGET)

asmr: asm
	@echo "$(BOLD)$(GREEN)$(BD_SYS) Running the executable. $(RESET)"
	$(SHOW_CMD)./$(ASM_TARGET)

#________________________________________________________________________________________ 
val: 
	@echo "$(BOLD)$(GREEN)$(BD_SYS) Running the executable with $(RED)$(<U>)Valgrind$(</U>). $(RESET)"
	$(SHOW_CMD)$(VAL) ./$(BIN_DIR)/*_program

gdb: 
	@echo "$(BOLD)$(GREEN)$(BD_SYS) Running the executable with $(RED)$(<U>)GDB$(</U>). $(RESET)"
	$(SHOW_CMD)gdb $(BIN_DIR)/*_program

asm: dirs check_modification $(ASM_TARGET)
	@echo "$(BOLD)$(BLUE)$(BD_SYS) Compiling the $(<U>)ASM$(</U>) object files. $(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	$(SHOW_CMD)$(ASM_C) $(ASM_FLAGS) $< -o $@

$(ASM_TARGET): $(ASM_OBJS)
	$(SHOW_CMD)ld -m elf_x86_64 $< -o $@
#________________________________________________________________________________________ 
clean: 
	@if [ -d "$(BIN_DIR)" ]; then\
		echo -e "$(BOLD)$(GREEN)$(BD_SYS) Removing the '$(<U>)$(BIN_DIR)$(</U>)' directory system. $(RESET)";\
		rm -rf $(OBJ_DIR) $(BIN_DIR);\
	else\
		echo "$(BOLD)$(RED)$(BD_SYS) Error: Directory '$(<U>)$(BIN_DIR)$(</U>)' does not exist.";\
	fi

#[fn defs]_______________________________________________________________________________ 
dirs:
ifeq (,$(wildcard $(OBJ_DIR) $(BIN_DIR)))
	@echo "$(BOLD)$(GREEN)$(BD_SYS) Creating the '$(<U>)target$(</U>)' directory system. $(RESET)"
	$(SHOW_CMD)mkdir -p $(OBJ_DIR) $(BIN_DIR)
	$(SHOW_CMD)mkdir -p $(SRC_DIR)
endif

check: check_modification
check_modification:
	@echo "$(BOLD)$(GREEN)$(BD_SYS) Checking for modifications in '$(<U>)$(SRC_DIR)$(</U>)' directory:$(RESET)"
	@if [ $$(find $(SRC_DIR) -type f -newer $(OBJ_DIR) | wc -l) -gt 0 ]; then\
	    echo "$(BOLD)  Source files have been $(<U>)modified$(</U>).$(RESET)";\
			echo -e " $(shell echo $(foreach word, $(shell find $(SRC_DIR) -type f -newer $(OBJ_DIR)), "  [source] $(word)\n"))";\
	else\
	    echo "$(BOLD)  $(<U>)No changes$(</U>) in source files.";\
	fi

%:
	@echo "$(BOLD)$(RED)$(BD_SYS) Error: Non-valid rule ('$(MAKECMDGOALS)') provided.$(RESET)"

