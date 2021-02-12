/******************************************************************************

Hashing the nucleotides (using only words of size 10) gives us 4^10
Hashing the DNA word of length 10 gives us a maximum value of: TTTTTTTTTT
which calculates to 1,048,575.
We will need an integer array of this size to store every possible unique word.


TODO:
    Add calculated hashed words to the wordArray
    Figure out how to keep track of locations in the "second" array.
        
*******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


long hashWord(char s[]);
int getWord(char c);
bool isValidDNA(char c);
char *deHash(int n);

int *wordArray[1048575];



FILE *fp;

int main(int argc, char *argv[])
{
    
    if(argc != 2){
	printf("ERROR! Please provide name of file!");
	return 0;
	}

	
    char buff[255];
    
    
    fp = fopen(argv[1], "r");
    char currentChar = '0';//initialize currentChar to non-null value
    int currentIndex = 0; //keep track of location in file
    
    while(currentChar != EOF){
        
        currentChar = fgetc(fp);
        
        if(isValidDNA(currentChar)){
                
            currentIndex = ftell(fp);
            switch(getWord(currentChar))
            {
            	case 0:
            		
            	break;
            	
            	case 1:
            		fseek(fp, currentIndex+1, SEEK_SET);
            	break;
            	
            	case 2:
            		fseek(fp, -9, SEEK_CUR);
            	break;
            	
            }
            
            currentIndex = ftell(fp);
            
        }
        
    }

    for(int i = 0; i < 1048575; i++)
    {
        int max = 0;
        if(wordArray[i] != NULL)
        {
            printf("Word: %s    Locations: ",deHash(i));

            int k = 0;
            while(wordArray[i][k] != 0)
            {
                
                printf("%d  ", wordArray[i][k]);
                
                k++;
            }
            printf("\n");
        }
    }

    
    return 0;
}

bool isValidDNA(char c)
{
    if(c == 'A' || c == 'a' || c == 'C' || c == 'c'
        || c == 'G' || c == 'g' || c == 'T' || c == 't'){
            return true;
        }
    return false;
}

int getWord(char c)
{
    char tempWord[10];
    long hashNum = 0;
    int fileIndex = ftell(fp);
    tempWord[0] = c;
    
    for(int i = 1; i < 10;)
    {
        tempWord[i] = fgetc(fp);
        if(tempWord[i] == EOF)
        {
            printf("REACHED END OF FILE!!!");
            fclose(fp);
            return 0;
        }else if(isValidDNA(tempWord[i]))
        {
            i++;
        } else if(!isspace(tempWord[i]))
        {
            //printf("NOT A WORD: %s\n", tempWord);
            return 1;
        }
        
    }
    
    hashNum = hashWord(tempWord);
    
    
    int *p_array;
    if(wordArray[hashNum] == NULL)
    {
		
		p_array = (int*)malloc(50*sizeof(int));	
	    p_array[0] = fileIndex;
	    wordArray[hashNum] = p_array;
	} else 
	{
		//int locationArraySize = sizeof(wordArray[hashNum]);
        int j = 0;

		while(wordArray[hashNum][j] != 0)
		{
            
			j++;
		}
        //printf("CHECK: %d\n", wordArray[hashNum][30]);
        int rem = j % 10;
        int quot = j / 10;
        if(rem >= 11) //If location array is almost full, realloc more memory
            {
                printf("J: %d \n", j);
                int *tmp_ptr = (int*)realloc(wordArray[hashNum], sizeof(int)*(j + rem + 10));


                if(tmp_ptr == NULL)
                {
                    printf("realloc Failed!!!\n");

                }
                else
                {
                    printf("Reallocated mem!\n");
                    for(int temp_j = j; temp_j < (j + rem + 10); temp_j++) //initialize new mem to 0s
                    {
                        tmp_ptr[temp_j] = 0;
                    }

                    wordArray[hashNum] = tmp_ptr;
                }
            
            }
        //printf("adding %d to location array index %d\n", fileIndex, j);
		wordArray[hashNum][j] = fileIndex;
			
	}
    
    return 2;
}

char* deHash(int n)
{
    static char nuc[10] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A'};
    int rem;
    int  step = 0;
    char letter;

    while(n != 0)
    {
        rem = n % 4;
        switch(rem)
        {
            case 0:
            letter = 'A';
            break;

            case 1:
            letter = 'C';
            break;

            case 2:
            letter = 'G';
            break;

            case 3:
            letter = 'T';
            break;
        }
        n = n / 4;
        nuc[9-step] = letter;
        step++;
    }

    return nuc;
}

long hashWord(char s[])
{
    
    long hashNumber = 0;
    for(int i = 0; i < 10; i++)
    {
        //printf("Letter: %c\n",s[i]);
        switch(s[i])
        {
            case 'A':
            case 'a':
                hashNumber += (0*pow(4, 9-i));
                break;
            case 'C':
            case 'c':
                hashNumber += (1*pow(4, 9-i));
                break;
            case 'G':
            case 'g':
                hashNumber += (2*pow(4, 9-i));
                break;
            case 'T':
            case 't':
                hashNumber += (3*pow(4, 9-i));
                break;
        }
    }
}




