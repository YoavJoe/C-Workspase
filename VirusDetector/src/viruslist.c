/*
*******************
file: viruslist.c
*******************
*/

#include "../include/viruslist.h"


link* list_append(link* virus_list, virus* data) {

	link* new_link = make_new_link(data);

	if(virus_list == NULL)
		return new_link;
	
	virus_list->next = new_link;

	return new_link;
}

link* make_new_link(virus* new_virus) {
	link* new_link = (link*)malloc(sizeof(link));
	new_link->v = new_virus;
	new_link->next = NULL;

	return new_link;
}

link* make_list(FILE* signatures) {
	link* head = NULL; /* linked list start */
	link* last = NULL;

	virus* new_virus = NULL;
	char virusSize[2] = "";
	unsigned short size = 0;

	while(!feof(signatures)) {

		strcpy(virusSize, "");

		fread(virusSize, 2, 1, signatures);
		size = virusSize[0] * 256 + virusSize[1];

		new_virus = (virus*)malloc(size); /*>>>memory<<<*/

		/* The first 16 bytes will store in name, the rest will store in signature*/
		fread(&(new_virus->name), size - 2, 1, signatures);
		/*IN ONE FUNCTION*/
		/*fread(&(new_virus->name), 16, 1, signatures);*/
		/*fread(new_virus->signature, (size - 18), 1, signatures); */

		new_virus->length = size - 18;

		if (head == NULL) {
			head = list_append(head, new_virus);
			last = head;
		}
		else
			last = list_append(last, new_virus);

	}

	return head;
}

void detect_virus(char *buffer, link *virus_list, unsigned int size) {
	/* for each virus sign, check if in file*/
	int i, length;
	char* name, *signature;
	link* currentLink = NULL;

	for(i = 0; i < size; i++) { /* for each virus */
		currentLink = virus_list;
		while(1) { /* iterate over the buffer byte-by-byte  */

			length = currentLink->v->length;
			name = currentLink->v->name;
			signature = currentLink->v->signature;

			if(memcmp(signature, buffer + i, length) == 0)
			{
				printf("The starting byte location in the suspected file: %d\n", i);
				printf("The virus name: %s\n", name);
				printf("The size of the virus signature: %d\n", length);
				printf("\n");
			}
			if(currentLink->next == NULL)
				break;
			else 
				currentLink = currentLink->next;
		}
	}
}


void list_free(link* lst) {
	link* linktemp = NULL;
	virus* virustemp = NULL;
	int i = 1;

	while(lst->next != NULL) {
		linktemp = lst;
		virustemp = linktemp->v;
		lst = lst->next;
		free(virustemp);
		free(linktemp);
		i++;
	}
}

/*prints length bytes from memory location buffer, in hex format*/
void print_hex(char* buffer, int length) {
	int i;
	for (i = 0; i < length; i++)
		printf("%hhX ", buffer[i]); /*hh stands for unsigned char*/
	
}

void list_print(link* virus_list) {
	link* current = virus_list;
	int i = 1;
	while(current->next != NULL) {
		printf("\n-------%d-------\n", i);
		printf("The virus name: %s\n", current->v->name);
		printf("The size of the virus: %d\n", current->v->length);
		printf("The virus signature:\n");
		print_hex(current->v->signature, current->v->length);
		current = current->next;
		i++;
	}
}
