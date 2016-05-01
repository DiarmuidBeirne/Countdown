// Countdown Final 1.0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
/* DECLARE FUNCTIONS */

FILE *openFile(char *fileName, char *mode);
void closeFile(FILE *fptr);
void  printInstructions();
void generateLetters();

void fillDict();

void alpha(); //function to sort letters[] alphabetically 
void countdown();
void checkNextWord(int i);
void checkNextLetter(int j, int i, int k);
void updateArray(int i, int j); // function to remove already used letters from the letters array
void recordWord(int i);
void findLargestWord();
void timer();



/* DECLARE FUNCTIONS */

/* GLOBAL VARIABLES*/

char letters[9]; // reference for program stays constant
char letters2[9]; // dynmaic array. loses letters every time there found. resets to letters at start of search
char dict[80000][20];
int wordcount;	
int wordsFound[10]; //stores the number of words found
char solutions[1000][10];
int y = 0; // number of solutions
char longestWord[9];

/* GLOBAL VARIABLES*/


/* MAIN */
int main()
{
	printInstructions();
	generateLetters(); //generates nine random letters
	fillDict();
	alpha();
	countdown();
	printf("... and your time starts now\n");
	//timer();
	
	
	
	findLargestWord();
	
	printf("Longest Possible Word is %s\n\n", longestWord);
	return 0;
}

/* MAIN */

/*FUNCTIONS*/


FILE * openFile(char *fileName, char *mode)
{

	FILE *fptr = fopen(fileName, mode);

	if (fptr == NULL)
	{
		printf("Error opening file ! \n");
	}

	return fptr;
}

void closeFile(FILE *fptr)
{
	fclose(fptr);
}

void  printInstructions()
{
	printf("....Countdown....\n");
	printf("Choose either Vowel or Consonants\n");
	printf("You get 9 letters\n");
}

void generateLetters()
{
	char vowels[5] = { 'a', 'e', 'i', 'o', 'u' };
	char consonants[21] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
	int i, j;

	char selection; // INPUT CHARACTER EITHER C OR V
	int r;
	int t = 0;

	for (i = 0; i < 9; i++)
	{

		do
		{

			t = 0;
			printf("Enter V for Vowel or C for Consonant:");
			scanf("\n%c", &selection);

			if (selection == 'V' || selection == 'v')
			{
				srand(time(NULL));
				r = rand() % 5; // random number between 0 and 4
				letters[i] = vowels[r];
			}
			else if (selection == 'C' || selection == 'c')
			{

				srand(time(NULL));
				r = rand() % 21; // random number between 0 and 20.
				letters[i] = consonants[r];
			}
			else
			{
				printf("Enter Either V or C\n");
				t = 1;
			}
		} while (t == 1); //PROMPTS USER AGAIN FOR INPUT IF INPUT IS NOT C OR V
		fflush;
		printf("\nYOUR LETTERS\n");
		for (j = 0; j <= i; j++)
		{
			printf("%c ", letters[j]); // PRINTS THE FIRST i LETTERS OF THE SELCTION
		}
		printf("\n");

	}




}

void alpha()
{
	char temp;
	int i, j;
	int n = strlen(letters);

	for (i = 0; i<n - 1; i++)
	{
		for (j = i + 1; j<n; j++)
		{
			if (letters[i] > letters[j])
			{
				temp = letters[i];
				letters[i] = letters[j];
				letters[j] = temp;
			}
		}
	}
}

void fillDict()
{
	FILE *fp;
	fp = openFile("words.txt", "r");
	int i = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s", dict[i]);
		i++;
	}
	wordcount = i;
	
}


void countdown()
{

	int i;  // words incrementer
			/*int j; // letters incrementer
			int k; // words incrementer for letters in word
			int x = -1; // number letter program has found*/

	for (i = 0; i < 9; i++) //initizles all words found to 0
	{
		wordsFound[i] = 0;
	}
	i = 0;
	for (i = 0; i < wordcount; i++)
	{
		strcpy(letters2, letters);
		checkNextWord(i);
	}

}

void checkNextWord(int i)
{
	int j = 0; //letter incrementr
	int k = 0; //letter incrementr for word being searched

	for (j = 0; j < 9; j++)
	{


		if (letters2[j] == dict[i][k])
		{
			checkNextLetter(j, i, k);
			return;
			
		}

		
	}


}

void checkNextLetter(int j, int i, int k)
{
	k++;
	int c = 0;


	updateArray(j + 1, k - 1); //when letter found remove that letter from the array

	if (dict[i][k] == '\0')
	{
		wordsFound[k]++;
		if (k > 2)recordWord(i);
		return;
	}


	for (j = 0; j < 9 - k; j++) {
		if (letters2[j] == dict[i][k])
		{
			checkNextLetter(j, i, k);
		}


	}





}


void updateArray(int j, int x)
{
	int c = 0;
	int size = 9 - x;
	for (c = j - 1; c < size - 1; c++) {
		letters2[c] = letters2[c + 1];
	}
	int i;
	
}

void recordWord(int i)
{
	strcpy(solutions[y], dict[i]);
	y++;

}

void findLargestWord()
{
	
	strcpy(longestWord, solutions[0]);
	int i;
	for (i = 0; i < y; i++)
	{
		int j = strlen(solutions[i]);
		int size = strlen(longestWord);

		if (j > size)
		{
			strcpy(longestWord, solutions[i]);
			size = strlen(longestWord);
		}

	}
	
}

void timer()
{
	int time = 5000;
	int i;
	for (i = 6; i > 0; i--)
	{
		printf("%d seconds remaining ...\n", i * 5);
		clock_t goal = time + clock();
		while (goal > clock());
	}
	printf("...Times up!!\n");
}


/*FUNCTIONS*/