#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef SCHEMER_ACTIONS_H_
#define SCHEMER_ACTIONS_H_

#include "./MainStructs.h"

Person * CheckIfPersonASlave(Person * person); // checks if person has a lord +++

bool CheckIfPersonASlave_Bool(Person * person);

bool CheckIfFriends(Person * firstPerson, Person * SecondPerson); // checks if persons are friends +++

bool CheckFriendLimit(Person * person, int limit); // Check is there friend limit

bool CheckIfHasGeneralLord(Person * firstPerson, Person * anotherPerson); // checks if persons has general lord +++

bool CanMakeFriends(Person * Schemer, Person * person, int k); // checks if you can become friends with a person

bool CanBecomeASlave(Person * Schemer, Person * person); // checks if you have a Lord

bool CanForceToBeASlave(Person * Schemer, Person * person); // checks if you can force a person to become a slave

bool CanMakeConspiracy(Person * Schemer, Person * person); // checks if you can make conspiracy of a person

void MakeFriends(Person * Schemer, Person * person); // makes friends with a person

void FallOut(Person * Schemer, Person * person); // fall out with a person

void StopBeingSlave(Person *Schemer);

void BecomeASlave(Person * Schemer, Person * person); // mahes you a slave of a person

void MakeSlave(Person * Schemer, Person * person); // makes someone your slave

#endif