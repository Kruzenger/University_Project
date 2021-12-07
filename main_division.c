#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#include "./main_division.h"

wchar_t * division(wchar_t * Word, int * VowelWord)
{
    int len = wcslen(Word);
    wchar_t * NewWord;
    NewWord = (wchar_t *)calloc(1000, sizeof(wchar_t));
    int letterInNewWord = 0;
    for (int i = 0; i < len; i++)
    {
        *(NewWord + letterInNewWord) = *(Word + i);
        letterInNewWord++;

        if(*(Word + i + 1) != L'\0')
        {
            NewWord[letterInNewWord] = L'\0';
        }
        if (*(VowelWord + i) == 2) // found letter 2
        {
            for (int j = i + 1; j < len; j++)
            {
                if ((*(VowelWord + i + 1) != 2 || *(VowelWord + i + 2) == 1) && i + 1 < len)
                {
                    if(*(VowelWord + j) == 2)
                    {
                        if((*(VowelWord + i + 1) == 1 || *(VowelWord + i + 1) == 3) && 
                            (*(VowelWord + i + 2) == 1 || *(VowelWord + i + 2) == 3) && 
                            (*(VowelWord + i + 3) == 1 || *(VowelWord + i + 3) == 3)) // check for "Native rule"
                        {
                            *(NewWord + letterInNewWord) = *(Word + i + 1);
                            letterInNewWord++;
                            i++;

                            *(NewWord + letterInNewWord) = *(Word + i + 1);
                            letterInNewWord++;
                            i++;


                            if(*(VowelWord + i + 1) == 3)
                            {
                                *(NewWord + letterInNewWord) = *(Word + i + 1);
                                letterInNewWord++;
                                i++;
                            }

                            if(*(Word + i) == L'-')
                            {
                                *(NewWord + letterInNewWord - 1) = L'\\';
                                *(NewWord + letterInNewWord) = L'-';
                                letterInNewWord++;   
                            }
                            else
                            {
                                *(NewWord + letterInNewWord) = L'\\';
                                letterInNewWord++;
                                *(NewWord + letterInNewWord) = L'-';
                                letterInNewWord++;       
                            }                 
                        }
                        else if((*(VowelWord + i + 1) == 1 || *(VowelWord + i + 1) == 3) && 
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

                            if(*(Word + i) == L'-')
                            {
                                *(NewWord + letterInNewWord - 1) = L'\\';
                                *(NewWord + letterInNewWord) = L'-';
                                letterInNewWord++;   
                            }
                            else
                            {
                                *(NewWord + letterInNewWord) = L'\\';
                                letterInNewWord++;
                                *(NewWord + letterInNewWord) = L'-';
                                letterInNewWord++;       
                            }                        
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
                                if(*(Word + i) == L'-')
                                {
                                    *(NewWord + letterInNewWord - 1) = L'\\';
                                    *(NewWord + letterInNewWord) = L'-';
                                    letterInNewWord++;   
                                }
                                else
                                {
                                    *(NewWord + letterInNewWord) = L'\\';
                                    letterInNewWord++;
                                    *(NewWord + letterInNewWord) = L'-';
                                    letterInNewWord++;       
                                } 
                            }
                            else
                            {

                            }
                        }
                        j = 10000;
                    }
                }
            }
        }
    }
    wcscat(NewWord, L" ");
    return NewWord;
}
