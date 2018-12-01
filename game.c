#include <stdio.h>
#include <libxml/parser.h>
#include "parsers/object_parser.h"

int main(int argc, char const *argv[]) {
	
	if(parseEntity("objects/skeleton.xml") == NULL) {
		printf("nothing\n" );
	}
	return 0;
}