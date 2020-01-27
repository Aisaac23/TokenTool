#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_SIZE 5
#define MAX_INPUT_SIZE 31
#define ONE_M 1024*1024
#define TWENTY 20

void rotate(unsigned int newSize, unsigned char * token);
unsigned long long factorial(unsigned int n);
void tokenPermutations(unsigned int newSize, unsigned char * permutedToken);
unsigned int stringSearch(char * str, char target);
void tokenCombinations(char token[], char inputString[31]);
unsigned char** prepareStorage(unsigned int tokenSize, unsigned int inputSize);
unsigned long long calculateTokens(unsigned int tokenSize, unsigned int inputSize);
int validateArguments(int argc, char * argv[]);
void printToken(unsigned char *token);
void visualizeTokens(unsigned int sizeBlock);

FILE *tokenFile;
unsigned char **strg;
int file;
unsigned long long nTokens;

int main(int argc, char * argv[])
{	

	unsigned char token[11];
	unsigned int tokenSize, inputSize, blockSize;
	if(argc <= 1)
	{
		printf("\nTokenTool ver 1.0 by Aisaac.\n");
		return EXIT_SUCCESS;
	}
	else if( !validateArguments(argc, argv) )
		return EXIT_FAILURE;

	if(file)
		tokenFile = fopen(argv[1], "a+");

	tokenSize = atoi(argv[argc-1]);
	inputSize = strlen(argv[argc-2]);

	strncpy(token, argv[argc-2], tokenSize*sizeof(unsigned char));
	token[tokenSize] = '\0';

	strg = prepareStorage(tokenSize, inputSize);

	tokenCombinations(token, argv[argc-2]);
	
	if(!file)
	{
		if(inputSize > 20)
			printf("More than %llu tokens have been generated. Please enter an amount to visualize them in blocks (1-300): ", calculateTokens(tokenSize, 20));
		else
			printf("%llu tokens have been generated. Please enter an amount to visualize them in blocks (1-300): ", calculateTokens(tokenSize, inputSize));
		scanf("%d", &blockSize);
		fflush(stdin);
		visualizeTokens(blockSize);
	}
	else
		printf("A csv file %s has been created in the same directory as this application.");
	
	if(file)
		fclose(tokenFile);
	else
		free(strg);
	
	return EXIT_SUCCESS;
}

void visualizeTokens(unsigned int sizeBlock)
{
	unsigned long long  c = 0;
	printf("\n");
	while(c < nTokens)
	{
		if(c > 0 && c%sizeBlock == 0)
		{
			printf("\n\n%llu tokens displayed so far, press enter to continue...\n", c);
			getchar();
		}
		printf("%s,", strg[c]);
		c++;
	}
	printf("\n");	
}

void printToken(unsigned char *token)
{
	printf("%s\n", token);
	if(file)
	{
		fprintf(tokenFile, token);
		fprintf(tokenFile, ",");
	}
	else
		strcpy(strg[nTokens++], token);
}

unsigned long long calculateTokens(unsigned int tokenSize, unsigned int inputSize)
{
	return (inputSize <= 20) ? ( factorial(inputSize)/factorial(inputSize-tokenSize) ): (TWENTY*ONE_M);
}

unsigned char** prepareStorage(unsigned int tokenSize, unsigned int inputSize)
{
	unsigned long long ntokens = calculateTokens(tokenSize, inputSize), c = 0;
	unsigned char** storage = (unsigned char**) calloc( ntokens, sizeof(unsigned char*) );
	
	while(c < ntokens)
	{
		storage[c] = (unsigned char*) calloc( tokenSize, sizeof(unsigned char) );
		if (storage[c] == NULL)
			perror("Memory cannot be allocated:");
		c++;
	}
	return storage;
}

unsigned long long factorial(unsigned int n)
{
	return n == 0 ? 1 : ( n*factorial(n-1) );
}

void rotate(unsigned int newSize, unsigned char * token)
{
	int k, size = strlen(token);
    int position = size - newSize;
    char temp = token[position];
	
    for(k=position+1; k<size; k++)      
        token[k-1] = token[k];
    token[k-1] = temp;  
}

void tokenPermutations(unsigned int newSize, unsigned char * permutedToken)
{
	if(newSize == 1)
		return;
	for(int a = 0; a<newSize; a++)
	{
		tokenPermutations(newSize-1, permutedToken);             
        if(newSize==2) 
            printToken(permutedToken); 
        rotate(newSize, permutedToken);		
	}
}

unsigned int stringSearch(char * str, char target)
{
	int pos = 0;
	while( pos < strlen(str))
		if(str[pos] == target)
			return pos;
		else
			pos++;
	return -1;
}

void tokenCombinations(char token[], char inputString[31])
{
	int tokenSize = strlen(token);
	int range = tokenSize-2, repIndex = tokenSize-2, index = tokenSize-1, inputSize = strlen(inputString);
	char permutedToken[11];
	
	while(token[0] != inputString[(inputSize-1) - (tokenSize-1)] )
	{
		strcpy(permutedToken,token);
		//printToken(token);
		tokenPermutations(tokenSize, permutedToken);
		index++;
		if(index == inputSize)
		{
			while(inputSize-range-1 == tokenSize-repIndex-1)
			{
				range = stringSearch(inputString, token[repIndex-1]);
				repIndex--;
			}
			
			range++;
			index = range + (tokenSize -1 -repIndex);
			int plus = 0;
			
			for(int a = repIndex; a<tokenSize; a++)
				token[a] = inputString[range+plus++];
			repIndex = tokenSize-2;
			
			range = stringSearch(inputString, token[repIndex]);
		}
		token[tokenSize-1] = inputString[index];
	}
	strcpy(permutedToken,token);
	tokenPermutations(tokenSize, permutedToken);
}

int validateArguments(int argc, char * argv[])
{
	int tokenLength = atoi(argv[argc-1]);
	file = (argc == 4) ? 1 : 0; 
	
	if(tokenLength > 10 || tokenLength < 3)
		perror("Error: token size should be no less than 3 and no more than 10");
	else if(strlen(argv[argc-2]) > 31 || strlen(argv[argc-2]) < 3 )
		perror("Error: base string should be a string between 3 and 31 characters length");
	else if( argc == 4 )
	{
		if( (tokenFile = fopen(argv[1], "a") )== NULL)
			perror("Error trying to open file: ");
		else
		{
			fclose(tokenFile);
			return 1;
		}
	}
	else
		return 1;
	
	return 0;
}
