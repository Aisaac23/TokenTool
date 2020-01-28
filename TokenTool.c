#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void rotate(unsigned int newLength, char * token);
void tokenPermutations(unsigned int newLength, char * permutedToken);
void tokenCombinations(char token[], char inputString[31]);
void printToken(char *token);

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
			tokenFile = fopen(argv[2], "a");
		
		tokenLength = atoi(argv[argc-1]);
		
		token = calloc( tokenLength, sizeof(char) );
		strncpy(token, argv[argc-2], tokenLength*sizeof(char));
		token[tokenLength] = '\0';

		tokenCombinations(token, argv[argc-2]);
		
		if(save)
			fclose(tokenFile);
		return EXIT_SUCCESS;
	}	

	return EXIT_FAILURE;
}

int menu(char *argv[])
{
	char opc[1];
	opc[0] = argv[1][1];
	
	if(argv[1][0])
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
	static unsigned long count;
	if(save)
	{
		fprintf(tokenFile, token);
		fprintf(tokenFile, ",");
		if(count > 0 && count%100==0)
		{
			count = 1;
			fprintf(tokenFile, "\n");
		}
		count++;
	}
	else
		printf("%s,", token);
}

void rotate(unsigned int newLength, char * token)
{
	int k, size = strlen(token);
    	int position = size - newLength;
	char temp = token[position];

	for(k=position+1; k<size; k++)      
	token[k-1] = token[k];
	token[k-1] = temp;  
}

void tokenPermutations(unsigned int newLength, char * permutedToken)
{
	if(newLength == 1)
		return;
	for(int a = 0; a<newLength; a++)
	{
		tokenPermutations(newLength-1, permutedToken);             
        if(newLength==2) 
            printToken(permutedToken); 
        rotate(newLength, permutedToken);		
	}
}

void tokenCombinations(char *token, char *inputString)
{
	int tokenLength = strlen(token);
	int range = tokenLength-2, nextTokenBeginAt = tokenLength-2, index = tokenLength-1, inputLength = strlen(inputString);
	char *permutedToken = calloc( tokenLength+1, sizeof(char) ), *position, newPosition[inputLength];
	
	while(token[0] != inputString[(inputLength-1) - (tokenLength-1)] )
	{
		strcpy(permutedToken,token);
		permutedToken[tokenLength] = '\0';
		//printToken(token);
		tokenPermutations(tokenLength, permutedToken);

		index++;
		if(index == inputLength)
		{
			while(inputLength-range-1 == tokenLength-nextTokenBeginAt-1)
			{
				position = strchr(inputString, token[nextTokenBeginAt-1]);
				sprintf(newPosition, "%ld", position-inputString);
				range = atoi(newPosition);
				nextTokenBeginAt--;
			}
			
			range++;
			index = range + (tokenLength -1 -nextTokenBeginAt);
			int plus = 0;
			
			for(int a = nextTokenBeginAt; a<tokenLength; a++)
				token[a] = inputString[range+plus++];
			nextTokenBeginAt = tokenLength-2;
			
			position = strchr(inputString, token[nextTokenBeginAt]);
			sprintf(newPosition, "%ld", position-inputString );
			range = atoi(newPosition); // we get the new value of range with the position
		}
		token[tokenLength-1] = inputString[index];
	}
	strcpy(permutedToken,token);
	tokenPermutations(tokenLength, permutedToken);
}
