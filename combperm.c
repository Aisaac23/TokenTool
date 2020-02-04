#include "combperm.h"

/*Uses a pointer to a function to print all posible permutations of a given string with all different characters. "customPrint" is a pointer to a function with the porpuse of allowing you to customize the output format and even the destination...
*/

void charPermutations(unsigned int newRange, char *permuted, void (*customPrint)( char *token ));
void intPermutations(unsigned int newRange, int *permuted, void (*printNumbers)( int *token, const int arraySize), const int arraySize);
void floatPermutations(unsigned int newRange, float *permuted, void (*printFloats)( float *token, const int arraySize), const int arraySize);
void stringPermutations(unsigned int newRange, char **permuted, void (*printStrings)(char **token, const int arraySize), const int arraySize);
void combinations(char inputString[], const int GROUP_SIZE, void (*actionWithToken)(char* token) );

void charPermutations(unsigned int newRange, char *permuted, void (*customPrint)( char *token) )
{
	if(newRange == 1)
		return;
	for(int a = 0; a<newRange; a++)
	{
		charPermutations(newRange-1, permuted, customPrint);             
        	if(newRange==2)
            		customPrint(permuted); 
        	//rotate: depending in the value of newRange we rotate like abcde -> abced or abcde -> abdec
		int k, size = strlen(permuted);
		int position = size - newRange;
		char temp = permuted[position];

		for(k=position+1; k<size; k++)      
			permuted[k-1] = permuted[k];
		permuted[k-1] = temp; 
		//end of rotate 	
	}
}

void intPermutations(unsigned int newRange, int *permuted, void (*printNumbers)( int *token, const int arraySize) , const int arraySize)
{
	if(newRange == 1)
		return;
	for(int a = 0; a<newRange; a++)
	{
		intPermutations(newRange-1, permuted, printNumbers, arraySize);             
        	if(newRange==2)
            		printNumbers(permuted, arraySize); 
        	//rotate: depending in the value of newRange we rotate like abcde -> abced or abcde -> abdec
		int k, size = arraySize;
		int position = size - newRange;
		int temp = permuted[position];

		for(k=position+1; k<size; k++)      
			permuted[k-1] = permuted[k];
		permuted[k-1] = temp; 
		//end of rotate 	
	}
}

void floatPermutations(unsigned int newRange, float *permuted, void (*printFloats)( float *token, const int arraySize), const int arraySize)
{
	if(newRange == 1)
		return;
	for(int a = 0; a<newRange; a++)
	{
		floatPermutations(newRange-1, permuted, printFloats, arraySize);             
        	if(newRange==2)
            		printFloats(permuted, arraySize); 
        	//rotate: depending in the value of newRange we rotate like abcde -> abced or abcde -> abdec
		int k, size = arraySize;
		int position = size - newRange;
		float temp = permuted[position];

		for(k=position+1; k<size; k++)      
			permuted[k-1] = permuted[k];
		permuted[k-1] = temp; 
		//end of rotate 	
	}
}


void stringPermutations(unsigned int newRange, char **permuted, void (*printStrings)(char **token, const int arraySize), const int arraySize)
{
	if(newRange == 1)
		return;
	for(int a = 0; a<newRange; a++)
	{
		stringPermutations(newRange-1, permuted, printStrings, arraySize);             
        	if(newRange==2)
            		printStrings(permuted, arraySize); 
        	//rotate: depending in the value of newRange we rotate like abcde -> abced or abcde -> abdec
		int k, size = arraySize, len;
		int position = size - newRange;
		//float temp = permuted[position];
		char *temp;
		len = strlen(permuted[position]);
		temp = calloc( len+1, sizeof(char) );
		strcpy(temp, permuted[position]);
		temp[len] = '\0';		

		for(k=position+1; k<size; k++)
			strcpy(permuted[k-1], permuted[k]);
		strcpy(permuted[k-1], temp);
		//end of rotate 	
	}
}

void combinations(char inputString[], const int GROUP_SIZE, void (*actionWithToken)(char* token) )
{
	const int MAX_LENGTH = 95, SKIP_LAST_CHAR = 2;
	unsigned int range, nextTokenBeginAt, index, inputSize;
	char token[GROUP_SIZE+1], newPosition[MAX_LENGTH], *position;
	
	range = nextTokenBeginAt = GROUP_SIZE-SKIP_LAST_CHAR; 
	index = GROUP_SIZE-1; 
	inputSize = strlen(inputString);
	
	strncpy(token, inputString, GROUP_SIZE);
	token[GROUP_SIZE] = '\0';
	/*When the token at it's first position reaches the last posible character of the input string the while loop will end, 
	for example: ABCDEFGH, token[0] == 'E' for a token size of 4*/
	while(token[0] != inputString[(inputSize-1) - (GROUP_SIZE-1)] )
	{
		actionWithToken(token);
		index++; // you'll move through the next chars until you reach the end of the string. ABCD -> ABCE -> ABCF -> ABCG...
		if(index == inputSize)// you've reached the end of the string for any of the groups. ABCH or BFGH
		{
			while(inputSize-range-1 == GROUP_SIZE-nextTokenBeginAt-1) // to go from AFGH to BCDE
			{//example: AFGH will have 4 iterations till we have nextTokenBeginAt == 0, and we'll replace A in the next lines of code
				//
				position = strchr(inputString, token[nextTokenBeginAt-1]);
				sprintf(newPosition, "%ld", position-inputString);
				range = atoi(newPosition);
				//
				nextTokenBeginAt--;// this will decrease until we get the next position to be replaced.
				
			}
			
			range++;// range represents the range of chars after the ones in the token to replace the last char. ABCD, range {EFGH}
			index = range + (GROUP_SIZE -1 -nextTokenBeginAt);
			
			int step = 0;/*this loop creates a brand new token using the the new value for range, ABCD becomes ACDE
			but when -nextTokenBeginAt- is 0 that means we've all the combinations with one char and we'll move to the next one.
			for example: AFGH becomes BCDE*/
			for(int a = nextTokenBeginAt; a<GROUP_SIZE; a++)
				token[a] = inputString[range+step++];
			nextTokenBeginAt = GROUP_SIZE-SKIP_LAST_CHAR;// the one before the last char of token
			
			//
			position = strchr(inputString, token[nextTokenBeginAt]);
			sprintf(newPosition, "%ld", position-inputString );
			range = atoi(newPosition); // we get the new value of range with the position
			//
		}
		token[GROUP_SIZE-1] = inputString[index]; //The last char of token will be replaced for a char that is not in the group.
	}

	actionWithToken(token);
	
}
