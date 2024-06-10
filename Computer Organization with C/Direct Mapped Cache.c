/*
    Name Surname: Emin Salih Açıkgöz
    Student ID: 22050111032
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define M 256
#define B 8
#define S 4
#define E 2

typedef struct{
    bool validity;
    unsigned char tag;
    int block[B];
}line;

typedef struct{
    line lines[E];
}set;

set myCache[S];

int lookforCache(unsigned char memIndex, unsigned char* memory)
{
	unsigned char memTag = (unsigned char)memIndex >> 5;
	short setIndex = (short)(memIndex & 0b00011000) >> 3;
	short blockOffset = (short)memIndex & 0b00000111;
	bool isL0Valid = myCache[setIndex].lines[0].validity;
	bool isL1Valid = myCache[setIndex].lines[1].validity;

	if ((myCache[setIndex].lines[0].tag == memTag && isL0Valid)
		|| (myCache[setIndex].lines[1].tag == memTag && isL1Valid)
		) {
		return 1;
	}
	else {
		int lineIndex = !isL0Valid ? 0 : (!isL1Valid ? 1 : (memIndex % 2 == 0 ? 0 : 1));
		for (int i = 0; i < B; i++) {
			if (i < blockOffset) {
				myCache[setIndex].lines[lineIndex].block[i] = memory[memIndex - (blockOffset - i)];
			}
			else {
				myCache[setIndex].lines[lineIndex].block[i] = memory[memIndex + (i - blockOffset)];
			}
		}
		myCache[setIndex].lines[lineIndex].tag = memTag;
		myCache[setIndex].lines[lineIndex].validity = true;
	}
	return 0;
}

void initializeData(int data[M]) 
{
    for (int i=0; i<M; i++) {
        data[i] = 512 + (rand() % M);
    }
}

void printArray(unsigned char data[M]){
    for (int i=0; i<M; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void initializeRandomSequence(unsigned char data[M]) 
{
    for (int i=0; i<M; i++) {
        data[i] = rand() % M;
    }
}

void printCache(){
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<S; i++){
        printf("Set %d -->", i);
        for(int l=0; l < E; l++){
            printf(" Line %d: ", (l+1));
            printf("v: %d - ", myCache[i].lines[l].validity);
            printf("tag: %d - block: ", myCache[i].lines[l].tag);
            for(int j = 0; j < B; j++){
                printf("%d ", myCache[i].lines[l].block[j]);
            }
            printf("|");
        }
        printf("\n"); 
    }
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

}

void freeCache(){
    for(int i=0;i<S; i++){
        for(int l=0; l < E; l++){
            myCache[i].lines[l].validity=0;
        }
    }
}

int main()
{
    int seed = time(0);
    unsigned char data[M];  

    srand(seed);
    initializeRandomSequence(data);

    printf("Cache at the begining\n");
    printCache();

    // You can test your code by changing following lines after you complete lookforCache function
    // Your code will be tested with a different main function.

    int res = lookforCache(9, data);
    if(res == 1)
        printf("Cache Hit For 9\n");
    else
        printf("Cache Miss For 9\n");
    printCache();


    res = lookforCache(12, data);
    if(res == 1)
        printf("Cache Hit For 12\n");
    else
        printf("Cache Miss For 12\n");
    printCache();

    res = lookforCache(33, data);
    if(res == 1)
        printf("Cache Hit For 33\n");
    else
        printf("Cache Miss For 33\n");
    printCache();

    return 0;
}
