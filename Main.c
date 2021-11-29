#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#include "Scripts/input_output_functions.h"
#include "Scripts/main_devotion.h"
#include "Scripts/rising_vowel.h"


int main(int argc, char ** argv)
{
    setlocale(LC_CTYPE, "ru_RU.UTF-8");
    wchar_t *MainArray;
    get_main_Array(argv, &MainArray);
    if( errno )
    {
        perror("Не удалось открыть файл\n");
        exit(1);
    }

    // Main part 

    wchar_t * ResultArray; // Here we will have our result array

    // Lets have different words from our text to get their rizing vowel and devide into parts

    wchar_t word[30]; // Container for our word
    int vowelWord; // Container for our vowel of word

    // We will seek for ' ' to know that it is an end of the word

    for(int i = 0; MainArray[i]; i++)
    {
        if(MainArray[i] != L' ')
        {
            wcscat(word, MainArray[i]); // add symbol to the word
        }
        else
        {
            upperVowel(word, vowelWord);
        }
    }



    getOutputFile(argv, ResultArray);
}