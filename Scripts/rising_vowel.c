#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#include "./rising_vowel.h"

glas gl = {L'ё', L'у', L'е', L'ы', L'а', L'о', L'э', L'я', L'и', L'ю', L'Ё', L'У', L'Е', L'Ы', L'А', L'О', L'Э', L'Я', L'И', L'Ю'};
// wchar_t ost[46] = {L'й', L'ц', L'к', L'н', L'г', L'ш', L'щ', L'з', L'х', L'ъ', L'ф', L'в', L'п', L'р', L'л', L'д', L'ж', L'ч', L'с', L'м', L'т', L'ь', L'б', L'Й', L'Ц', L'К', L'Н', L'Г', L'Ш', L'Щ', L'З', L'Х', L'Ъ', L'Ф', L'В', L'П', L'Р', L'Л', L'Д', L'Ж', L'Ч', L'С', L'М', L'Т', L'Ь', L'Б'};

int * upperVowel(wchar_t * word)
{
    long len = wcslen(word);
    int * vowel = (int*)calloc(len, sizeof(int));
    for (int i = 0 ; i < len; i++)
    {
        for (int j = 0 ; j < 20 ; j++) 
        {
            if (word[i] == gl[j])
            {
                vowel[i] = 2;
                j = 20;
            }
            else
            {
                if(word[i] == L'ъ' || word[i] == L'ь')
                {
                    vowel[i] = 3;
                }
                else
                {
                    vowel[i] = 1;   
                }
            }
        }
    }
    return vowel;
}
