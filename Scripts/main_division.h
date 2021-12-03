#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

wchar_t * division(wchar_t * Word, int * VowelWord)
{
    int len = wcslen(VowelWord);

    wchar_t * NewWord;
    NewWord = (wchar_t *)malloc(100 * sizeof(wchar_t));

    int letterInNewWord = 0;
    for (int i = 0; *(Word + i) != L'\0'; i++)
    {
        *(NewWord + letterInNewWord) = *(Word + i);
        letterInNewWord++;
        if (*(VowelWord + i) == 2) // found letter 2
        {
            // wprintf(L"%i", i);
            for (int j = i + 1; *(Word + j) != L'\0'; j++)
            {
                if ((*(VowelWord + i + 1) != 2 || *(VowelWord + i + 1) == 1) && i + 1 < len)
                {
                    if(*(VowelWord + j) == 2)
                    {
                        if((*(VowelWord + i + 1) == 1 || *(VowelWord + i + 1) == 3) && 
                            (*(VowelWord + i + 2) == 1 || *(VowelWord + i + 2) == 3)) // check for "Native rule"
                        {
                            *(NewWord + letterInNewWord) = *(Word + i + 1);
                            letterInNewWord++;
                            i++;

                            if(*(VowelWord + i + 1) == 3)
                            {
                                *(NewWord + letterInNewWord) = *(Word + i + 1);
                                letterInNewWord++;
                                i++;
                            }

                            *(NewWord + letterInNewWord) = L'/';
                            letterInNewWord++;
                            *(NewWord + letterInNewWord) = L'-';
                            letterInNewWord++;                        
                        }
                        else
                        {
                            if(*(VowelWord + i + 1) == 3)
                            {
                                *(NewWord + letterInNewWord) = *(Word + i + 1);
                                letterInNewWord++;
                                i++;
                            }

                            if(i != 0)
                            {
                                *(NewWord + letterInNewWord) = L'/';
                                letterInNewWord++;
                                *(NewWord + letterInNewWord) = L'-';
                                letterInNewWord++;
                            }
                            else
                            {

                            }
                        }
                        j = len + 1;
                    }
                }
            }
        }
    }
    wcscat(NewWord, L" ");
    return NewWord;
}
