#ifndef CONSPIRACY_ALGORITHM_H_
#define CONSPIRACY_ALGORITHM_H_

#include "./MainStructs.h"
#include "./AlgorithmPatterns.h"
#include "./SchemerActions.h"

void TheConspiracyAlgorithm(Tree  tree, char **argv);

// OperationLine * ConspiracyTrying(Person * headPerson, Person * person, Tree tree);

OperationLine * RecursiveConspiracyTrying(Person * headPerson, Tree tree, Person ** personsPassed);

void ShowAnswer(OperationLine * operations0, OperationLine * operations1, OperationLine * operations2,  OperationLine * operations3, char **argv);

OperationLine * TryToGetFree();

void HugeConspiracy(Tree tree, OperationLine * freeOperations, char **argv);

Person ** FindNewLords(Tree tree);

void RecursiveFind(Person ** Lords, Person ** CloseList, Person * headPerson);

#endif