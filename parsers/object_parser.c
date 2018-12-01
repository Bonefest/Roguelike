#include <libxml/parser.h>
#include <stdlib.h>
#include "object_parser.h"

struct View readViewTag(xmlNodePtr node) {
	printf("%s\n",xmlGetProp(node,"model"));
}

struct Entity* parseEntity(char* fileName) {
	
	xmlDocPtr document = xmlParseFile(fileName);

	if(document == NULL)
		return NULL;

	xmlNodePtr xentity = xmlDocGetRootElement(document);

	if(xentity->xmlChildrenNode == NULL) return NULL;
	else {
		struct Entity* entity = (struct Entity*) calloc(1,sizeof(struct Entity));
		xentity = xentity->xmlChildrenNode;
		while(xentity != NULL) {
			if(!xmlStrcmp(xentity->name,(const xmlChar*)"view")) {
				readViewTag(xentity);
			}
			xentity=xentity->next;
		}
	}

	//printf("%s\n",cur->name);
	xmlFreeDoc(document);
	return NULL;
}