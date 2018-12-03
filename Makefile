CC=gcc

XML_PATH=-I/usr/include/libxml2
XML_LIBS=-lxml2
CFLAGS=-Wall $(XML_PATH)

test: game.c
	$(CC) $(CFLAGS) game.c parsers/object_parser.c -o game $(XML_LIBS)