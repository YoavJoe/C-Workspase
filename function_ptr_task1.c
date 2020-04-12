#include<stdio.h>
#include<stdlib.h>

int i;

int plus_one(int n){
	return n + 1;
}

/*Gets an integer n, and returns the absolute value of n*/
int myabs(int n){
	return (n < 0) ? n * -1 : n;
}

/*Prints the value of n follwed by new line, and returns n unchaned*/
int iprt(int n){
	printf("%d\n", n);
	return n;
}

/*Prints the character of ASCII value n followed by a new line, and returns n unchaned.*/
/*If n is not between 0x20 and 0x7E, print a dot char insted*/
int cprt(int n){
	(n > 0x20 && n < 0x7E)? printf("%c\n", n): printf(".\n");
	return n;
}

/*Ignores n, reads a line from stdin, and returns a number given in that line*/
int my_get(int n){
	printf("Enter a number:\n");
	return getchar();
}

int* map(int* array, int arrayLength, int (*f) (int)){
	int* mappedArray = (int*)(malloc(arrayLength * sizeof(int)));

	for(i = 0; i < arrayLength; i++)
		mappedArray[i] = f(array[i]);

	return mappedArray;
}

/*Get an integer n, and ends the program using n as the return value*/
int quit(int n) {
	if(n == 0)
	{
		printf("successfuly processed\n");
		exit(0);
	}
 
	printf("unsuccessfuly processed\n");
	exit(0);
}

struct fun_desc {
	char* name;
	int (*fun)(int);
};

void task2() {
	int len = 4;
	int arr1[] = {5, -2, 7, 8};
	int* arr2 = map(arr1, len, my_get);
	int* arr3 = map(arr2, len, iprt);
	int* arr4 = map(arr3, len, abs);
	int* arr5 = map(arr4, len, plus_one);
	int* arr6 = map(arr5, len, cprt);

	free(arr2);
	free(arr3);
	free(arr4);
	free(arr5);
	free(arr6);
}

void manu()
{
	int select, i;
	int* iarray;
	struct fun_desc array[] = {
		{"Plus One", plus_one}, {"Abs", myabs},
		{"Print Integer", iprt}, {"Print Character", cprt},
		{"Get number", my_get}, {"Quit", quit}, {NULL, NULL}};

	printf("Menu\n");

	do
	{
		printf("Please choose a function:\n");
		for(i = 0; i < 6; i++)
			printf("%d) %s\n", i, array[i].name);

		scanf("%d", &select);
		if(select < 0 || select > 6)
		{
			printf("Not within bounds!!\n");
			exit(0);
		}

		printf("Option: %d\n", select);
		printf("within bounds!!\n");
		iarray = map(iarray, 4, array[select].fun);
		printf("DONE.\n");

	}while(1);

}

int main()
{
	manu();
	return 0;
}