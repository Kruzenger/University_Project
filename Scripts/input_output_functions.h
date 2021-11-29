#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

int fsize(FILE *fp)
{
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp,prev,SEEK_SET);
    return sz;
}

int get_fsize(char ** argv)
{
    FILE *input;
    input = fopen(argv[1], "r");
    int file_size;
    file_size = fsize(input);
    return file_size;
    fclose(input);
}

void printer(wchar_t * array, int n)
{
    int count = 0;
    for (int i = 0; i < n - 1; i ++)
    {
        wprintf(L"%ls", array + count);
        count += wcslen(array);
    }
}

int Number_Of_Words(FILE * input)
{
    int symbol;
    int count = 0;
    if (input != NULL)
    {
        do 
        {
            symbol = fgetc(input);
            if (symbol == L' ' || symbol == L'\n') count++;

        } 
        while (symbol != WEOF);
    }
    count ++;
    fclose(input);
    return count;
}

void get_main_Array(char ** argv, wchar_t ** main_array)
{
    setlocale(LC_CTYPE, "ru_RU.UTF-8");

    int fileSize = 0;
    int sizeNow = 0;
    int sizeThen = 0;

    wchar_t * array;
    wchar_t saveSymbol;

    FILE * input;

    input = fopen(argv[1], "r");
    fileSize = fsize(input);
    array = (wchar_t *)malloc(fileSize * 25);

    input = fopen(argv[1], "r");
    do
    {
        sizeThen = sizeNow;
        fgetws(array + sizeNow, fileSize, input);
        sizeNow = wcslen(array);
        saveSymbol = *(array + sizeNow - 1);
        *(array + sizeNow - 1) = ' ';
    }
    while (sizeNow > sizeThen);
    *(array + sizeNow - 1) = saveSymbol;
    
    *main_array = array;
    fclose(input);
}

void getOutputFile(char ** argv, wchar_t * Output_Array)
{
    FILE * outPutFile;
    outPutFile = fopen(argv[2], "w");

    fputws(Output_Array, outPutFile);

    fclose(outPutFile);
}
