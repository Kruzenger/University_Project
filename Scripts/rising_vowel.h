#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

// Arrays with all chars of one type 

int whatTypeOfChar()
{
	// return 1, 2, 3 according to the type
	// Гласные - 3, 
    // Сонорные - 2, 
    // Остальные - 1
	return 0;
}

void upperVowel(wchar_t * word, int ** vowelWord)
{
	// transform words into numbers: 
	// Example:
	// "Яблоко" --> "321313"
	int vowel[6] = {3, 2, 1, 3, 1, 3};

	*(vowelWord) = vowel;

	// Need to change vowelWord, not return!!!
}