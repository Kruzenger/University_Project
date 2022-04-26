#include <stdio.h>
#include <stdlib.h>

#ifndef A_H_INCLUDED // идентификатор ещё не определён
#define A_H_INCLUDED // определяем

typedef struct operationLine_st
{
    char operation;
    int person1;
    int person2;
}OperationLine;



typedef struct friends_st
{
    struct person_st ** Friends;
    struct person_st ** LastFriend;
    
}Friends;

typedef struct slaves_st
{
    struct person_st ** Slaves;
    struct person_st ** LastSlave;
}Slaves;

typedef struct person_st
{
    int name;
    
    struct person_st * Lord;
    
    Friends FriendsList;
    Slaves SlavesList;
}Person;



typedef struct tree_st
{
    int n;
    int k;
    Person * King;
    Person * Schemer;
}Tree;

typedef struct friendPerson_st
{
    Person * person;
    struct friendPerson_st * previous;
    struct friendPerson_st * next;
}FriendPerson;

#endif