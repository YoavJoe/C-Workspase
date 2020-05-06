/*
*******************
file: viruslist.c
*******************
*/

#include "../include/viruslist.h"


void insert(link** head, virus* data) {
	link* new = (link*)calloc(2, sizeof(link));
	link* current = *head;
	new->v = data;

	if(*head == NULL) {
		*head = new;
	    return;
	}

    while(current->next != NULL)
    	current = current->next;

    current->next = new;
}


link* list_append(link* virus_list, virus* data) {

	virus* new = make_new_virus(data->length, data->name, data->signature);

	insert(&virus_list, new);

	return virus_list;
}

virus* make_new_virus(unsigned short length, char* name, char* signature) {
	virus* new_virus = (virus*)calloc(3, sizeof(virus));
	new_virus->length = length;
	strcpy(new_virus->name, name);
	strcpy(new_virus->signature, signature);

	return new_virus;
}

link* make_list(FILE* signatures) {
	link* head = NULL;
	virus* new_virus = (virus*)calloc(3, sizeof(virus));
	char virusSize[2] = "";
	unsigned short size = 0;

	while(!feof(signatures)) {

		fread(virusSize, 2, 1, signatures);
		size = virusSize[0] * 256 + virusSize[1];

		/* The first 16 bytes will store in name, the rest will store in signature*/
		fread(&(new_virus->name), size - 2, 1, signatures);
		/*IN ONE FUNCTION*/
		/* if(!fread(&(current->name), 16, 1, fp)) break;*/
		/* if(!fread(&(current->signature), (size - 18), 1, fp)) break; */

		new_virus->length = size - 18;

		head = list_append(head, new_virus);
	}

	free(new_virus);
	
	return head;
}

void detect_virus(char *buffer, link *virus_list, unsigned int size) {
	/* for each virus sign, check if in file*/
	int i, length;
	char* name, *signature;
	link *currentLink = NULL;

	for(i = 0; i < size; i++) { /* for each viurs */
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
	link* temp = NULL;

	while(lst != NULL) {
		temp = lst;
		lst = lst->next;
		free(temp->v);
		free(temp);
	}
}

void list_print(link* virus_list) {
	link* current = virus_list;
	int i = 1;
	while(current->next != NULL) {
		printf("-------%d-------\n", i);
		printf("The virus name: %s\n", current->v->name);
		printf("The size of the virus signature: %d\n", current->v->length);
		current = current->next;
		i++;
	}
}
