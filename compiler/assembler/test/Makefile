CC=g++
CFLAGS=--std=c++20 -Wall -Wextra -g


PARSER_FILE = parser
LEXER_FILE = lexer

INCLUDE_PATHS = ../lib

.SILENT:all

all:
	make PARSER
	make LEXER

PARSER:
		$(CC) $(CFLAGS) $(PARSER_FILE).cpp -I$(INCLUDE_PATHS) -o $(PARSER_FILE)

LEXER:
		$(CC) $(CFLAGS) $(LEXER_FILE).cpp -I$(INCLUDE_PATHS) -o $(LEXER_FILE)

