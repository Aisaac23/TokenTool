#ifndef COMBPERM_H_
#define COMBPERM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void charPermutations(unsigned int newRange, char *permuted, void (*customPrint)( char *token ));
void intPermutations(unsigned int newRange, int *permuted, void (*printNumbers)( int *token, const int arraySize), const int arraySize);
void floatPermutations(unsigned int newRange, float *permuted, void (*printFloats)( float *token, const int arraySize), const int arraySize);
void stringPermutations(unsigned int newRange, char **permuted, void (*printStrings)(char **token, const int arraySize), const int arraySize);
void combinations(char inputString[], const int GROUP_SIZE, void (*actionWithToken)(char* token) );

#endif
