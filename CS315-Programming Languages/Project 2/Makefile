
# Makefile for CS315_F23_Team16.yacc and CS315_F23_Team16.lex

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g
YACC = yacc
LEX = lex
YFLAGS = -d

# Executable name
EXECUTABLE = parser

# Source files
YACC_FILE = CS315_F23_Team16.yacc
LEX_FILE = CS315_F23_Team16.lex

# Generated C files
YACC_C = y.tab.c
LEX_C = lex.yy.c

# Object files
OBJ = y.tab.o lex.yy.o

# Default target
all: $(EXECUTABLE)

# Rule for yacc
$(YACC_C): $(YACC_FILE)
	$(YACC) $(YFLAGS) $(YACC_FILE)

# Rule for lex
$(LEX_C): $(LEX_FILE) $(YACC_C)
	$(LEX) $(LEX_FILE)

# Rule for object files
y.tab.o: $(YACC_C)
	$(CC) $(CFLAGS) -c $(YACC_C) -o y.tab.o

lex.yy.o: $(LEX_C)
	$(CC) $(CFLAGS) -c $(LEX_C) -o lex.yy.o

# Rule for executable
$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

# Clean up
clean:
	rm -f $(EXECUTABLE) $(LEX_C) $(YACC_C) y.tab.h $(OBJ)

.PHONY: all clean
