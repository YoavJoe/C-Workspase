/*
*******************
file: main.c
*******************
*/

#include "../include/viruslist.h"

int main(int argc, char** argv)
{
	int infectedFileSize;
	char* virusBuffer;
	link* viruslist = NULL;
	FILE* infected = NULL;
	FILE* signatures = NULL;

	infected = fopen(argv[1], "r+b");
	signatures = fopen(argv[2], "r+b");

	if(infected == NULL || signatures == NULL) {
		fprintf(stderr, "Can't open your files\n");
		return EXIT_FAILURE;
	}

	viruslist = make_list(signatures); /* create the list of signatures*/

	/* allocate and init with zero */
	virusBuffer = (char*)calloc(sizeof(char), 10000);

	/* store the infected file in buffer */
	infectedFileSize = fread(virusBuffer, sizeof(char), 10000, infected);

	detect_virus(virusBuffer , viruslist, infectedFileSize); /*assume that the file is smaller than the buffer */

	/*fclose(infected);
	fclose(signatures);*/

	list_print(viruslist);

	list_free(viruslist);

	free(virusBuffer);
	
	return EXIT_SUCCESS;
}

/* ./main <filename>*/
