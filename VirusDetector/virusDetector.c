#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char const *argv[])
{
	FILE* infected = fopen(argv[1], "rb+");
	FILE* signatures = fopen(argv[2], "rb+");
	char* virusBuffer = (char*)calloc(sizeof(char), 10000); /* allocate and init with zero */
	link* virusList = make_list(signatures); /* create the list of signatures - TODO YOAV */
	int infectedFileSize = fread(virusBuffer, sizeof(char), 10000, infected); /* store the infected file in buffer */
	detect_virus(virusBuffer, virusList, infectedFileSize, howToPrint); /* assume that the file is smaller than the buffer */


	fclose(infected);
	fclose(signature);

	return 0;
}

list* make_list(FILE* signature) {
	link* lst = NULL;

	lst = (link*)calloc()
}

void detect_virus(char *buffer, link *virus_list, unsigned int size, int howToPrint) {
	// for each virus sign, check if in file

	for(i=0; i<size; i++) { /* for each viurs */
		link *currentLink = virus_list;
		while(1) { /* iterate over the buffer byte-by-byte  */
			length = currentLink->v->length;
			name = currentLink->v->name;
			signature = currentLink->v->signature;


			if(memcmp(signature, buffer+i, length) == 0)
			{
				printf("The starting byte location in the suspected file: %d\n",i);
				printf("The virus name: %s\n",name);
				printf("The size of the virus signature: %d\n", length);
				printf("\n") ;
			}
			if(currentLink->next == NULL)
				break ;
			else 
				currentLink = currentLink->next;
	}

}


// ./main <filename>
