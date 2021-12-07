#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./rising_vowel.h"

glasl gll = {L'ё', L'у', L'е', L'ы', L'а', L'о', L'э', L'я', L'и', L'ю'};
glasu glu = {L'Ё', L'У', L'Е', L'Ы', L'А', L'О', L'Э', L'Я', L'И', L'Ю', L'Й', L'Ц', L'К', L'Н', L'Г', L'Ш', L'Щ', L'З', L'Х', L'Ъ', L'Ф', L'В', L'П', L'Р', L'Л', L'Д', L'Ж', L'Ч', L'С', L'М', L'Т', L'Ь', L'Б'};
// wchar_t ost[46] = {L'й', L'ц', L'к', L'н', L'г', L'ш', L'щ', L'з', L'х', L'ъ', L'ф', L'в', L'п', L'р', L'л', L'д', L'ж', L'ч', L'с', L'м', L'т', L'ь', L'б', L'Й', L'Ц', L'К', L'Н', L'Г', L'Ш', L'Щ', L'З', L'Х', L'Ъ', L'Ф', L'В', L'П', L'Р', L'Л', L'Д', L'Ж', L'Ч', L'С', L'М', L'Т', L'Ь', L'Б'};
znaki zn = {L',',L';',L':',L'.', L'!',L'?',L'"',L'"',L'{',L'}',L'—',L'[',L']',L'(',L')',L'/',L'\\' ,L'@',L'#',L'^',L'*', L'<',L'>',L'~',L'$',L'%',L'+',L'='};
int * upperVowel(wchar_t * Word)
{
    bool cranch = false;
    bool obr = false;
    long len = wcslen(Word);
    int * vowel = (int*)calloc(1024, sizeof(int));
    for (int i = 0 ; i < len; i++)
    {   
        cranch = false;
        for (int k = 0 ; k < 28 ; k++)
        {
            if (Word[i] == zn[k])
            {
                vowel[i]= 4;
                k = 28;
                cranch = true;
            }
        }

        if(!cranch)
        {
            for (int j = 0 ; j < 43 ; j++) 
            {
                if (j < 10 && Word[i] == gll[j])
                {
                    vowel[i] = 2;
                    j = 44;
                }
                else if(Word[i] == glu[j - 10] && j >= 10 && j < 20)
                {
                    if(i == 0)
                    {
                        vowel[i] = 2;
                        j = 44;
                    }
                    else
                    {
                        obr = true;
                        i = len + 1;
                        j = 44;
                    }
                }  
                else if(*(Word + i) == glu[j - 10] && j >= 20)
                {
                    if(i == 0)
                    {
                        vowel[i] = 1;
                        j = 44;
                    }
                    else
                    {
                        obr = true;
                        i = len + 1;
                        j = 44;
                    }    
                }                  
                else
                {
                    if(Word[i] == L'ъ' || Word[i] == L'ь')
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
    }

    if(obr)
    {
        for (int i = 0 ; i < len; i++)
        {   
            vowel[i] = 1;
        }
    }

    vowel[len + 1] = 0;
    vowel[len + 2] = 0;

    return vowel;
}
