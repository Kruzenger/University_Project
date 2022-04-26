#include <stdio.h>

#ifndef ALGORITHM_PATTERNS_H_
#define ALGORITHM_PATTERNS_H_

#include "./MainStructs.h"
#include "./SchemerActions.h"

void AddPerson(Person * friendPerson, Person ** personsPassed);

bool IsInPersonPassed(Person * friendPerson, Person ** personsPassed);

FriendPerson ** FindChainOfFriendsToUs(Person * headPerson, Person * lord, bool slaves, Tree tree); // Finds chain of friends to us +++

// Some functions for findChainOfFriends function

FriendPerson * RecursiveFindOfChain(Person * headPerson, Person * lord, Person ** personsPassed, bool slaves, Tree tree); // Recursive +++

OperationLine * SufferTroughChain(FriendPerson * Chain);

void FreeChains(FriendPerson ** chains);

#endif


