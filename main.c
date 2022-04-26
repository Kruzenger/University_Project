#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./Scripts/Tree.h"
#include "./Scripts/SchemerActions.h"
#include "./Scripts/AlgorithmPatterns.h"
#include "./Scripts/MainStructs.h"
#include "./Scripts/ConspiracyAlgorithm.h"

int main(int argc, char **argv) 
{
    Tree tree;
    Person *Persons;
    OperationLine *operationLines;
    FileWorker(&tree, &operationLines, argv);
    TreeCreate(&tree, &Persons, operationLines);

    TheConspiracyAlgorithm(tree, argv);

    free(operationLines);
    FreeTree(&Persons, tree.n);
}