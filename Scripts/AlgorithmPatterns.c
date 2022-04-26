#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./AlgorithmPatterns.h"

void AddPerson(Person * friendPerson, Person ** personsPassed)
{
    int i = 0;
    for(i = 0; personsPassed[i]; i++);

    personsPassed[i] = friendPerson;
}

bool IsInPersonPassed(Person * friendPerson, Person ** personsPassed)
{
    for(int i = 0; personsPassed[i]; i++)
        if(personsPassed[i] == friendPerson)
            return true;

    return false;
}

FriendPerson ** FindChainOfFriendsToUs(Person * headPerson, Person * lord, bool slaves, Tree tree)
{
    FriendPerson ** Chains;
    Chains = (FriendPerson **)calloc(tree.n, sizeof(FriendPerson *));
    int counter = 0;

    Person ** personsPassed;

    for (int i = 0; headPerson->FriendsList.Friends[i]; i++)
    {
        personsPassed = calloc(tree.n, sizeof(Person*));
        personsPassed[0] = headPerson;

        Chains[counter] = RecursiveFindOfChain(headPerson->FriendsList.Friends[i], lord, personsPassed, slaves, tree);
        if(Chains[counter] != NULL)
        {
            FriendPerson * friendPerson = (FriendPerson *)calloc(1, sizeof(FriendPerson));
            friendPerson->person = headPerson;
            friendPerson->next = Chains[counter];
            Chains[counter]->previous = friendPerson;

            if(slaves)
            {
                for(int i = 0; Chains[counter]->next; i++)
                {
                    Chains[counter] = Chains[counter]->next;
                }
            }
            else
            {
                Chains[counter] = Chains[counter]->previous;
            }
            counter++;
        }

        free(personsPassed);
    }
    return Chains;
}

FriendPerson * RecursiveFindOfChain(Person * headPerson, Person * lord, Person ** personsPassed, bool slaves, Tree tree)
{
    if((headPerson->Lord == lord && lord != NULL) || (headPerson == tree.Schemer && !slaves))
    {
        FriendPerson * friendPerson = (FriendPerson *)calloc(1, sizeof(FriendPerson));
        friendPerson->person = headPerson;
        return friendPerson;
    }

    if((slaves && headPerson->Lord == lord && lord != NULL) || (!slaves && CheckFriendLimit(headPerson, tree.k) && !CheckIfFriends(headPerson, tree.Schemer)))
        return NULL;

    AddPerson(headPerson, personsPassed);

    for(int i = 0; headPerson->FriendsList.Friends[i]; i++)
    {
        if(!IsInPersonPassed(headPerson->FriendsList.Friends[i], personsPassed))
        {
            FriendPerson * friendPersonNext = RecursiveFindOfChain(headPerson->FriendsList.Friends[i], lord, personsPassed, slaves, tree);
            if(friendPersonNext != NULL)
            {
                FriendPerson * friendPerson = (FriendPerson *)calloc(1, sizeof(FriendPerson));
                friendPerson->person = headPerson;
                friendPerson->next = friendPersonNext;
                friendPersonNext->previous = friendPerson;
                return friendPerson;
            }
        }
    }

    return NULL;
}

OperationLine * SufferTroughChain(FriendPerson * Chain)
{
    int num = 0;

    while(Chain->previous != NULL)
    {
        MakeSlave(Chain->person->Lord, Chain->previous->person);
        Chain = Chain->previous;
        num++;
    }

    OperationLine * operations =  (OperationLine *)calloc(num + 1, sizeof(OperationLine));

    operations[num].person1 = 0; 

    while(Chain->next != NULL)
    {
        operations[num - 1].operation = '>';
        operations[num - 1].person1 = Chain->person->name;
        Chain = Chain->next;
        num--;
    }
    
    return operations;
}

void FreeChains(FriendPerson ** Chains)
{
    for(int i = 0; Chains[i] != NULL; i++)
    {
        while(Chains[i]->next)
            Chains[i] = Chains[i]->next;

        while(Chains[i]->previous != NULL)
        {
            free(Chains[i]->next);
            Chains[i] = Chains[i]->previous;
        }
        free(Chains[i]->next);
        free(Chains[i]);
    }
    free(Chains);
}

