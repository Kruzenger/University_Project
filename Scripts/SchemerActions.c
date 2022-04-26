#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./SchemerActions.h"

Person * CheckIfPersonASlave(Person * person)
{
    return person->Lord;
}

bool CheckIfPersonASlave_Bool(Person * person)
{
    return person->Lord;
}

bool CheckIfFriends(Person * firstPerson, Person * SecondPerson)
{
    for (int i = 0; firstPerson->FriendsList.Friends[i] != *(firstPerson->FriendsList.LastFriend); i++)
        if(firstPerson->FriendsList.Friends[i] == SecondPerson)
            return true;

    return false;
}

bool CheckFriendLimit(Person * person, int limit) {
    int i = 0;
    for (i = 0; person->FriendsList.Friends[i] != *(person->FriendsList.LastFriend); i++);
    return (i == limit);
} // Check is there friend limit

bool CheckIfHasGeneralLord(Person * firstPerson, Person * anotherPerson) {
    return (firstPerson->Lord == anotherPerson->Lord);
} // checks if persons has general lord +++

bool CanMakeFriends(Person * Schemer, Person * person, int k) {
    if (CheckIfFriends(Schemer, person)) return false;
    if (!CheckFriendLimit(person, k) && !CheckFriendLimit(Schemer, k) && CheckIfHasGeneralLord(Schemer, person)) {
        return true;
    }
    int i = 0;
    for (i = 0; person->FriendsList.Friends[i] != *(person->FriendsList.LastFriend); i++) {
        if (CheckIfFriends(Schemer, person->FriendsList.Friends[i])) return true;
    }
    return false;
} // checks if you can become friends with a person

void MakeFriends(Person * Schemer, Person * person) {
    *(Schemer->FriendsList.LastFriend) = person;
    Schemer->FriendsList.LastFriend ++;
    *(person->FriendsList.LastFriend) = Schemer;
    person->FriendsList.LastFriend ++;
} // makes friends with a person


void FallOut(Person * Schemer, Person * person) 
{
    for (int i = 0; Schemer->FriendsList.Friends[i]; i++) 
    {
        if (Schemer->FriendsList.Friends[i] == person) 
        {
            Schemer->FriendsList.Friends[i] = NULL;
            Schemer->FriendsList.LastFriend--;
            for(int j = i; &(Schemer->FriendsList.Friends[j]) != Schemer->FriendsList.LastFriend; j++)
            {
                Schemer->FriendsList.Friends[j] = Schemer->FriendsList.Friends[j + 1];
            }
            *(Schemer->FriendsList.LastFriend) = NULL;
        }
    }

    for (int i = 0; person->FriendsList.Friends[i]; i++) 
    {
        if (person->FriendsList.Friends[i] == Schemer) 
        {
            person->FriendsList.Friends[i] = NULL;
            person->FriendsList.LastFriend--;
            for(int j = i; &(person->FriendsList.Friends[j]) != person->FriendsList.LastFriend; j++)
            {
                person->FriendsList.Friends[j] = person->FriendsList.Friends[j + 1];
            }
            *(person->FriendsList.LastFriend) = NULL;
        }
    }
} // fall out with a person

void BecomeASlave(Person * Schemer, Person * person) {
    Schemer->Lord = person;
    *(person->SlavesList.LastSlave) = Schemer;
    person->SlavesList.LastSlave ++;
} // mahes you a slave of a person

bool CanForceToBeASlave(Person * Schemer, Person * person) {
    int sign = 0;
    for (int i = 0; person->FriendsList.Friends[i] != *(person->FriendsList.LastFriend); i++) {
        if (CheckIfPersonASlave(person->FriendsList.Friends[i]) == Schemer) {
            sign++;
        }
    }
    return(sign && !(CheckIfPersonASlave(person)));
} // checks if you can force a person to become a slave

bool CanMakeConspiracy(Person * Schemer, Person * person) {
    int sign = 0;
    int i = 0;
    for (i = 0; person->FriendsList.Friends[i] != *(person->FriendsList.LastFriend); i++) {
        if (CheckIfFriends(person->FriendsList.Friends[i], Schemer)) {
            sign ++;
        }
    }
    return(sign/i);
} // checks if you can make conspiracy of a person

void StopBeingSlave(Person *Schemer) {
    Person * Person_lord = Schemer->Lord;
    Schemer->Lord = NULL;
    for (int i = 0; Person_lord->SlavesList.Slaves[i] != *(Person_lord->SlavesList.LastSlave); i++) {
        if (Person_lord->SlavesList.Slaves[i] == Schemer) {
            Person_lord->SlavesList.Slaves[i] = NULL;
            Person_lord->SlavesList.LastSlave--;
        }
    }
}

void MakeSlave(Person * Schemer, Person * person) {
    person->Lord = Schemer;
    *(Schemer->SlavesList.LastSlave) = person;
    Schemer->SlavesList.LastSlave ++;
} // makes someone our slave
