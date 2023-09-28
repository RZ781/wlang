CC=g++
CFLAGS=-Wall -Wextra -Wpedantic -Werror 
OBJECT_FILES=obj/main.o obj/lexer.o obj/nodes.o obj/type.o obj/parser.o obj/ir.o obj/irgen.o

wlang: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) -o wlang
obj/%.o: src/%.cpp include/*
	$(CC) $(CFLAGS) -I include -c $< -o $@
