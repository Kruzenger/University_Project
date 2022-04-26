#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./ConspiracyAlgorithm.h"

void TheConspiracyAlgorithm(Tree tree, char **argv)
{
    if(tree.King->Lord != NULL)
    {
        ShowAnswer(NULL, NULL, NULL, NULL, argv);
        goto Exit;
    }

    FriendPerson ** SlaveChains = FindChainOfFriendsToUs(tree.King, tree.Schemer, true, tree);
    OperationLine * operations = NULL; 
    OperationLine * freeOperations = NULL; 

    Person ** personsPassed = (Person **)calloc(tree.n, sizeof(Person));

    if(SlaveChains[0])
    {
        operations = SufferTroughChain(SlaveChains[0]);
    }
    else
    {
        operations = RecursiveConspiracyTrying(tree.King, tree, personsPassed);
    }

    if(operations != NULL)
    {
        ShowAnswer(NULL, NULL, operations, NULL, argv);
        goto Exit;
    }
    else if(tree.Schemer->Lord)
    {
        freeOperations = TryToGetFree(tree);
    }

    if(tree.Schemer->Lord)
    {
        ShowAnswer(NULL, NULL, NULL, NULL, argv);
        goto Exit;
    }
    else
    {
        HugeConspiracy(tree, freeOperations, argv);
    }

    Exit:

    if(freeOperations != NULL)
        free(freeOperations);

    if(operations != NULL)    
        free(operations);

    free(personsPassed);
    FreeChains(SlaveChains);
}

void ShowAnswer(OperationLine * operations0, OperationLine * operations1, OperationLine * operations2, OperationLine * operations3, char **argv)
{
    FILE * output = fopen(argv[2], "w");

    if(operations0 == NULL && operations1 == NULL && operations2 == NULL && operations3 == NULL)
    {
        fprintf(output, "NO");
        goto Exit;
    }

    if(operations0)
        for(int i = 0; operations0[i].person1 != 0; i++)
            fprintf(output, "%c %i\n", operations0[i].operation, operations0[i].person1);

    if(operations1)
        fprintf(output, "%c %i\n", operations1->operation, operations1->person1);
        
    if(operations2)
        for(int i = 0; operations2[i].person1 != 0; i++)
            fprintf(output, "%c %i\n", operations2[i].operation, operations2[i].person1);

    if(operations3)
        for(int i = 0; operations3[i].person1 != 0; i++)
            fprintf(output, "%c %i\n", operations3[i].operation, operations3[i].person1);   

    Exit:

    fclose(output);
}

OperationLine * TryToGetFree(Tree tree)
{
    FriendPerson ** FriendChains = FindChainOfFriendsToUs(tree.Schemer->Lord, tree.Schemer->Lord, false, tree);
    OperationLine * operations = NULL;

    FriendPerson * Chain = FriendChains[0];
    int counter = 0;

    if(Chain)
    {
        int num = 0;
        for(int i = 0; Chain->next; i++)
        {
            num++;
            Chain = Chain->next;
        }

        operations = (OperationLine *)calloc(num * 2, sizeof(OperationLine));


        if(Chain->person != tree.Schemer)
        {
            Chain = Chain->previous;
        }

        if(Chain->person == tree.Schemer)
            Chain = Chain->previous;

        for(int i = 0; Chain; i++)
        {
            if(!CheckIfFriends(tree.Schemer, Chain->person))
            {
                operations[counter].operation = '=';
                operations[counter].person1 = Chain->person->name;

                MakeFriends(tree.Schemer, Chain->person);

                if(Chain->person == tree.Schemer->Lord)
                {
                    StopBeingSlave(tree.Schemer);
                }
                
                counter++;
            }
        
            if(Chain->next && Chain->next->person != tree.Schemer)
            {
                operations[counter].operation = 'x';
                operations[counter].person1 = Chain->next->person->name;
                FallOut(tree.Schemer, Chain->next->person);

                counter++;
            } 

            if(tree.Schemer->Lord == NULL)
            {
                operations[counter].operation = 'x';
                operations[counter].person1 = Chain->person->name;
                FallOut(tree.Schemer, Chain->person);
                counter++;
            }

            Chain = Chain->previous;   
        }
    }

    FreeChains(FriendChains);

    return operations;
}

void HugeConspiracy(Tree tree, OperationLine * freeOperations, char **argv)
{
    Person ** Lords = FindNewLords(tree);
    FriendPerson ** SlaveChains = NULL;
    OperationLine * operations = NULL;
    OperationLine * slaveOperations = NULL;
    OperationLine firstOperation;

    Person ** personsPassed = (Person **)calloc(tree.n, sizeof(Person));

    int counter = 0;

    while(Lords[counter])
    {
        if(tree.Schemer->Lord)
            StopBeingSlave(tree.Schemer);

        firstOperation.operation = 's';
        firstOperation.person1 = Lords[counter]->name;
        BecomeASlave(tree.Schemer, Lords[counter]);

        operations = RecursiveConspiracyTrying(tree.King, tree, personsPassed);

        if(operations)
        {
            SlaveChains = FindChainOfFriendsToUs(tree.King, tree.Schemer, true, tree);
            if(SlaveChains[0])
                slaveOperations = SufferTroughChain(SlaveChains[0]);
            
            ShowAnswer(freeOperations, &firstOperation, operations, slaveOperations, argv);
            goto Exit;
        }

        counter++;
    }

    ShowAnswer(NULL, NULL, NULL, NULL, argv);

    Exit:

    if(SlaveChains != NULL)
        FreeChains(SlaveChains);

    if(slaveOperations != NULL)
        free(slaveOperations);
    
    if(operations != NULL)
        free(operations);

    if(Lords[0] != NULL)    
        free(Lords);

    if(personsPassed != NULL)
        free(personsPassed);
}

Person ** FindNewLords(Tree tree)
{
    Person ** Lords = calloc(tree.n, sizeof(Person));
    Person ** PersonsPassed = calloc(tree.n, sizeof(Person));

    RecursiveFind(Lords, PersonsPassed, tree.King);

    free(PersonsPassed);
    return Lords;
}

void RecursiveFind(Person ** Lords, Person ** PersonsPassed, Person * headPerson)
{
    AddPerson(headPerson, PersonsPassed);

    if(headPerson->Lord != NULL && !IsInPersonPassed(headPerson->Lord, Lords))
        AddPerson(headPerson->Lord, Lords);

    for(int i = 0; headPerson->FriendsList.Friends[i]; i++)
        if(!IsInPersonPassed(headPerson->FriendsList.Friends[i], PersonsPassed))
            RecursiveFind(Lords, PersonsPassed, headPerson->FriendsList.Friends[i]);
}

// OperationLine * ConspiracyTrying(Person * headPerson, Tree tree)
// {
//     OperationLine * operations;
//     Person ** personsPassed = calloc(tree.n, sizeof(Person));


//     return operations;
// }

OperationLine * RecursiveConspiracyTrying(Person * headPerson, Tree tree, Person ** personsPassed)
{
    OperationLine * operations = NULL;
    int counter = 0;

    AddPerson(headPerson, personsPassed);

    FriendPerson ** FriendChains = FindChainOfFriendsToUs(headPerson, tree.Schemer->Lord, false, tree);

    for(int i = 0; headPerson->FriendsList.Friends[i]; i++)
        if(CheckFriendLimit(headPerson->FriendsList.Friends[i], tree.k) && !CheckIfFriends(headPerson->FriendsList.Friends[i], tree.Schemer))
            goto RecursiveCall;

    if(FriendChains[0] == NULL)
        goto RecursiveCall;

    if(CheckFriendLimit(headPerson, tree.k))
    {
        for(int i = 0; FriendChains[i] || headPerson->FriendsList.Friends[i]; i++)
        {
            FriendPerson * personeee = FriendChains[i];
            if(FriendChains[i] == NULL || headPerson->FriendsList.Friends[i] == NULL)
            {
                goto RecursiveCall;
            }
        }

        int friendPos;

        for(int i = 0; headPerson->FriendsList.Friends[i]; i++)
        {
            if(tree.Schemer->Lord == headPerson->FriendsList.Friends[i]->Lord)
            {
                friendPos = i;
                goto FindOperations;
            }

            for(int j = 0; headPerson->FriendsList.Friends[j]; j++)
                if(CheckIfFriends(headPerson->FriendsList.Friends[i], headPerson->FriendsList.Friends[j]))
                {
                    friendPos = i; 
                    goto FindOperations;
                }
        }

        goto RecursiveCall;

        FindOperations:
        
        operations = (OperationLine *)calloc(1000, sizeof(OperationLine));

        for(int i = 0; FriendChains[i]; i++)
        {
            if(i != friendPos)
            {
                for(int j = 0; FriendChains[i]->next; j++)
                {
                    FriendChains[i] = FriendChains[i]->next;
                }

                if(FriendChains[i]->person == tree.Schemer)
                    FriendChains[i] = FriendChains[i]->previous;
            
                for(int k = 0; FriendChains[i]->previous; k++)
                {
                    MakeFriends(tree.Schemer, FriendChains[i]->person);
                    operations[counter].operation = '=';
                    operations[counter].person1 = FriendChains[i]->person->name;

                    counter++;

                    if(FriendChains[i]->next && FriendChains[i]->next->person != tree.Schemer)
                    {
                        operations[counter].operation = 'x';
                        operations[counter].person1 = FriendChains[i]->next->person->name;
                        FallOut(tree.Schemer, FriendChains[i]->next->person);

                        counter++;
                    }

                    if(FriendChains[i]->previous)
                        FriendChains[i] = FriendChains[i]->previous;
                }
            }
        }
        
        MakeFriends(tree.Schemer, headPerson->FriendsList.Friends[friendPos]);
        operations[counter].operation = '=';
        operations[counter].person1 = headPerson->FriendsList.Friends[friendPos]->name;

        counter++;

        MakeSlave(tree.Schemer, headPerson);
        operations[counter].operation = '#';
        operations[counter].person1 = headPerson->name;

        counter++;
    }
    else
    {
        operations = (OperationLine *)calloc(1000, sizeof(OperationLine));

        for(int i = 0; FriendChains[0]->next; i++)
        {
            FriendChains[0] = FriendChains[0]->next;
        }

        if(FriendChains[0]->person == tree.Schemer)
            FriendChains[0] = FriendChains[0]->previous;
        
        for(int i = 0; FriendChains[0]->previous; i++)
        {
            if(!CheckIfFriends(tree.Schemer, FriendChains[0]->person))
            {
                MakeFriends(tree.Schemer, FriendChains[0]->person);
                operations[counter].operation = '=';
                operations[counter].person1 = FriendChains[0]->person->name;

                counter++;
            }


            if(FriendChains[0]->next && FriendChains[0]->next->person != tree.Schemer)
            {
                operations[counter].operation = 'x';
                operations[counter].person1 = FriendChains[0]->next->person->name;
                FallOut(tree.Schemer, FriendChains[0]->next->person);

                counter++;
            }

            if(FriendChains[0]->previous)
                FriendChains[0] = FriendChains[0]->previous;
        }

        if(!CheckIfFriends(tree.Schemer, FriendChains[0]->person))
        {
            MakeFriends(tree.Schemer, FriendChains[0]->person);
            operations[counter].operation = '=';
            operations[counter].person1 = FriendChains[0]->person->name;

            counter++;
        }

        operations[counter].operation = 'x';
        operations[counter].person1 = FriendChains[0]->next->person->name;
        FallOut(tree.Schemer, FriendChains[0]->next->person);

        counter++;

        for(int i = 0; tree.Schemer->FriendsList.Friends[i]; i++)
            if(tree.Schemer->FriendsList.Friends[i] != headPerson)
            {
                operations[counter].operation = 'x';
                operations[counter].person1 = tree.Schemer->FriendsList.Friends[i]->name;
                FallOut(tree.Schemer, tree.Schemer->FriendsList.Friends[i]);

                counter++;
            }

        for(int i = 0; headPerson->FriendsList.Friends[i]; i++)
        {
            if(headPerson->FriendsList.Friends[i] != tree.Schemer)
            {
                MakeFriends(tree.Schemer, headPerson->FriendsList.Friends[i]);
                operations[counter].operation = '=';
                operations[counter].person1 = headPerson->FriendsList.Friends[i]->name;
                
                counter++;
            }
        }

        operations[counter].operation = 'x';
        operations[counter].person1 = headPerson->name;
        FallOut(tree.Schemer, headPerson);

        counter++;

        MakeSlave(tree.Schemer, headPerson);
        operations[counter].operation = '#';
        operations[counter].person1 = headPerson->name;

        counter++;
    }


    RecursiveCall:

    for(int i = 0; headPerson->FriendsList.Friends[i]; i++)
        if(operations == NULL && !IsInPersonPassed(headPerson->FriendsList.Friends[i], personsPassed))
            operations = RecursiveConspiracyTrying(headPerson->FriendsList.Friends[i], tree, personsPassed);

    FreeChains(FriendChains);
    return operations;
}