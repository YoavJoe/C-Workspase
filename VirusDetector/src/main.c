/*
*******************
file: main.c
*******************
*/

#include "../include/viruslist.h"

int main(int argc, char *argv[])
{
	FILE* infected = NULL;
	FILE* signatures = NULL;
	int infectedFileSize;
	char* virusBuffer;
	link* viruslist = NULL;

	/*if (argc == 1) {
		printf("Error: there is no files to process!!\n");
		return EXIT_FAILURE;
	}*/

	infected = fopen(argv[1], "r+b");
	signatures = fopen(argv[2], "r+b");

	viruslist = make_list(signatures); /* create the list of signatures*/

	/*list_print(viruslist);*/

	/* allocate and init with zero */
	virusBuffer = (char*)calloc(sizeof(char), 10000);

	/* store the infected file in buffer */
	infectedFileSize = fread(&virusBuffer, sizeof(char), 10000, infected);
	printf("%d\n", infectedFileSize);

	detect_virus(virusBuffer , viruslist, infectedFileSize); /* assume that the file is smaller than the buffer */

	list_free(viruslist);

	fclose(infected);
	fclose(signatures);

	return EXIT_SUCCESS;
}

/* ./main <filename>*/
