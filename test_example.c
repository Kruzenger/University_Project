#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "input_output_functions.h"
#include <locale.h>
#include <wchar.h>
#include <wctype.h>


int main(int argc, char ** argv)
{
    setlocale(LC_CTYPE, "ru_RU.UTF-8");
    wchar_t *main_array;

    get_main_Array(argv, &main_array);
    //int count = wcslen(array);
    if( errno )
    {
        perror("input.dat не удалось открыть\n");
        exit(1);
    }
    getOutputFile(argv, main_array);
}