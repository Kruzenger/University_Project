#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#include "Scripts/input_output_functions.h"
#include "Scripts/main_division.h"
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

    wchar_t * Word;
    Word = (wchar_t *)calloc(30, sizeof(wchar_t)); // Container for our word
    int * VowelWord; // Container for our vowel of word

    // We will seek for ' ' to know that it is an end of the word

    int letterInWord = 0;
    for(int i = 0; MainArray[i]; i++)
    {
        if(MainArray[i] != L' ')
        {
            Word[letterInWord] = MainArray[i];
            letterInWord++;
        }
        else
        {
            upperVowel(Word, &VowelWord); // returns vowel word in vowelWord;
            division(&Word, VowelWord); // devides vord into parts, according to vowelWord and returns devided word in word
            /*
                To devide word we will use "Правило Русского Языка: Восходящая гласность"
                Than meens we will devide letters into 3 groups: 
                Гласные - 3, 
                Сонорные - 2, 
                Остальные - 1
                Than we will devide that way 123-23-123, but we will devide more human-readable with help of "Native rules":
                2 goes to next part of word
                if there are 2 letters of 1 or 2 we will devide them that way 21-02
            */
            *(Word) = L'\0'; // make it empty for next word 
            letterInWord = 0;
        }
    }



    getOutputFile(argv, ResultArray);
}