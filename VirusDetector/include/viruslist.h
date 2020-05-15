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

link* make_new_link(virus* new_virus);
link* list_append(link* virus_list, virus* data);
void list_print(link* virus_list);
void list_free(link* virus_list);

link* make_list(FILE* signatures);
void detect_virus(char *buffer, link *virus_list, unsigned int size);
void print_hex(char* buffer, int length);

#endif