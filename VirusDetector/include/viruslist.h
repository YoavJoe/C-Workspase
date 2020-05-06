/*
*******************
file: viruslist.h
*******************
*/
#ifndef _VIRUSLIST_H
#define _VIRUSLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_LEN 10

typedef struct virus virus;
typedef struct link link;

struct virus {
	unsigned short length;
	char name[16];
	char signature[];
};

struct link {
	virus *v;
	link *next;
};

virus* make_new_virus(unsigned short length, char* name, char* signature);
link* list_append(link* virus_list, virus* data);
void list_print(link* virus_list);
void list_free(link* virus_list);

link* make_list(FILE* signatures);
void detect_virus(char *buffer, link *virus_list, unsigned int size)

#endif