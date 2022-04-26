#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./Tree.h"
#include <errno.h>

int fsize(FILE *fp)
{
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp,prev,SEEK_SET);
    return sz;
}

int get_fsize(FILE *input)
{
    int file_size;
    file_size = fsize(input);
    return file_size;
}

int CountLines(FILE *input) 
{
    int fsize = get_fsize(input);
    char *string = calloc(1, fsize + 1);
    fread(string, fsize, 1, input);
    fseek(input, 0, SEEK_SET);
    int count = 0;
    for (int i = 0; i < fsize; i ++) {
        if (string[i] == '\n') count++;
    }
    free(string);
    return count - 1;
}

void ReadNumbers (FILE *input, Tree *tree) 
{
    fscanf(input, "%d", &tree->n);
    fscanf(input, "%d", &tree->k);
}

void FileWorker(Tree *tree, OperationLine **operationLines, char **argv) 
{
    FILE *input;
    input = fopen(argv[1], "r");
    if (errno) {
        perror(argv[1]);
    }
    int n = CountLines(input);
    ReadNumbers(input, tree);
    *operationLines = RelationsRead(input, n);
    fclose(input);
}

OperationLine * RelationsRead(FILE *input, int n)
{
    OperationLine * operationLine = (OperationLine *)calloc(n + 1, sizeof(OperationLine));
    char buffer[1];
    for(int i = 0; i < n; i++)
    {
        fscanf(input, "%s", &buffer[0]);
        operationLine[i].operation = buffer[0];
        fscanf(input, "%d", &operationLine[i].person1);
        fscanf(input, "%d", &operationLine[i].person2);
    }
    return operationLine;
}

Person * PersonsCreate(Tree *tree)
{
    Person * p = (Person *)calloc(tree->n, sizeof(Person));
    for (int i = 0; i < tree->n; i++) 
    {
        p[i].name = i + 1;
        p[i].FriendsList.Friends = (Person **)calloc(tree->k + 1, sizeof(Person *));
        p[i].SlavesList.Slaves = (Person **)calloc(tree->n, sizeof(Person *));
        p[i].FriendsList.LastFriend = p[i].FriendsList.Friends;
        p[i].SlavesList.LastSlave = p[i].SlavesList.Slaves;
    }
    return p;
}// Создаёт персон

void TreeCreate(Tree *tree, Person ** personss, OperationLine *operationLines)
{
    Person * persons = PersonsCreate(tree);
    *personss = persons;
    tree->King = &(persons[0]);
    tree->Schemer = &(persons[tree->n - 1]);
    
    for (int i = 0; operationLines[i].operation; i++) 
    {
        if(operationLines[i].operation == '=')
        {
            *(persons[operationLines[i].person1 - 1].FriendsList.LastFriend) = &persons[operationLines[i].person2 - 1];
            persons[operationLines[i].person1 - 1].FriendsList.LastFriend++;           
            *(persons[operationLines[i].person2 - 1].FriendsList.LastFriend) = &persons[operationLines[i].person1 - 1];
            persons[operationLines[i].person2 - 1].FriendsList.LastFriend++;
        }
        if (operationLines[i].operation == '>')
        {
            *(persons[operationLines[i].person1 - 1].SlavesList.LastSlave) = &persons[operationLines[i].person2 - 1];
            persons[operationLines[i].person1 - 1].SlavesList.LastSlave++;
            persons[operationLines[i].person2 - 1].Lord = &persons[operationLines[i].person1 - 1];
        }
    }
}

void FreeTree(Person ** Persons, int n)
{
    for(int i = 0; i < n; i++)
    {
        free((*Persons)[i].FriendsList.Friends);
        free((*Persons)[i].SlavesList.Slaves);
    }
    free(*Persons);
}