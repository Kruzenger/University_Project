#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

void division(wchar_t ** Word, int * VowelWord)
{
    int len = wcslen((*Word));
    wchar_t newWord[30];

    int letterInNewWord = 0;

    for (int i = 0; (*Word)[i]; i++)
    {
        newWord[letterInNewWord] =  (*Word)[i];
        letterInNewWord++;

        if (VowelWord[i] == 3) // found letter 3
        {
            for (int j = i; (*Word)[i]; j++)
            {
                if (VowelWord[i] == 3)
                {
                    if((VowelWord[i + 1] == 1 || VowelWord[i + 1] == 2) && 
                        (VowelWord[i + 2] == 1 || VowelWord[i + 2] == 2)) // check for "Native rule"
                    {
                        newWord[letterInNewWord] =  (*Word)[i];
                        letterInNewWord++;
                        i++;
                        newWord[letterInNewWord] = L'-';
                        letterInNewWord++;                        
                    }
                    else
                    {
                        newWord[letterInNewWord] = L'-';
                        letterInNewWord++;
                    }
                }
            }
        }  
    }
    
    (*Word) = newWord;
}