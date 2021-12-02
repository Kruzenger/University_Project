#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

// Arrays with all chars of one type 

int whatTypeOfChar()
{
	// return 1, 2 according to the type
	// Гласные - 2, 
    // Остальные - 1
	return 0;
}

int * upperVowel(wchar_t * word)
{
	// transform words into numbers: 
	// Example:
	// "Яблоко" --> "211212"
	int * vowel = (int*)calloc(6, sizeof(int));
	
	vowel[0] = 2;
	vowel[1] = 1;
	vowel[2] = 1;
	vowel[3] = 2;
	vowel[4] = 1;
	vowel[5] = 2;

	return vowel;
}