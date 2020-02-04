#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "combperm.h"

void printToken(char *token);
void permute(char *token);
int menu(char *argv[]);

FILE *tokenFile = NULL;
int save = false;


int main(int argc, char * argv[])
{	

	char *token;
	unsigned int tokenLength;
	
	if( menu(argv) != -1)
	{
		if(save)
		{
			printf("Saving your tokens in: %s ...\n", argv[2]);
			tokenFile = fopen(argv[2], "a");
			if(tokenFile == NULL)
			{
				printf("It seems that the name of the file is invalid or the file cannot be oppened.\n");
				return EXIT_FAILURE;
			}
		}
		else
			tokenFile = stdout;

		tokenLength = atoi(argv[argc-1]);
		
		token = calloc( tokenLength, sizeof(char) );
		strncpy(token, argv[argc-2], tokenLength*sizeof(char));
		token[tokenLength] = '\0';

		combinations(argv[argc-2], tokenLength, permute);
		printf("\n");
		if(save)
			fclose(tokenFile);
		return EXIT_SUCCESS;
	}	
	
	printf("There are arguments missing or with the wrong format.");
	return EXIT_FAILURE;
}

int menu(char *argv[])
{
	char opc[1];
	opc[0] = argv[1][1];
	
	if(argv[1][0] != '-')
		return -1;

	switch(opc[0])
	{
		case 'p':
			save = false;
		break;

		case 's':
			save = true;
		break;
		
		default:
			printf("Invalid option.");
			return -1;
	};
	return 1;
}

void printToken(char *token)
{
	static unsigned long count=1;
	fprintf(tokenFile, token);
	fprintf(tokenFile, ",");
	if(count%100==0)
	{
		fprintf(tokenFile, "\n");
		if(!save)
		{
			printf("\n%lu tokens printed so far, press any key to continue...", count);
			getchar();
		}
	}
	count++;
}

void permute(char *token)
{
	unsigned const int len = strlen(token);
	char tempCopy[len];
	strcpy(tempCopy, token);
	charPermutations(len, tempCopy, printToken);
}


