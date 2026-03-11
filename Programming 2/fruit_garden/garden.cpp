#include <cstdlib>
#include "garden.hpp"
#include "tree.hpp"

GARDEN_CLASS::GARDEN_CLASS() {
    gTreesTotal = 0;
    gTreeList = NULL;
    gBranchesTotal = 0;
    gFruitsNumberTotal = 0;
    gFruitsWeightTotal = 0;
    gLastTree = NULL;
}
GARDEN_CLASS::~GARDEN_CLASS() {
    TREE_CLASS* currentTree = gTreeList, *tmp = NULL;

    while (currentTree != NULL) {
        tmp = currentTree;
        currentTree = currentTree->getNext();
        delete tmp;
    }
}
unsigned int GARDEN_CLASS::getTreesTotal(void) {
    return gTreesTotal;
}
void GARDEN_CLASS::adjustTreesTotal(int changeTrees) {
    gTreesTotal += changeTrees;
}
unsigned int GARDEN_CLASS::getBranchesTotal(void) {
    return gBranchesTotal;
}
void GARDEN_CLASS::adjustBranchesTotal(int changeBranches) {
    gBranchesTotal += changeBranches;
}
unsigned int GARDEN_CLASS::getFruitsTotal(void) {
    return gFruitsNumberTotal;
}
void GARDEN_CLASS::adjustFruitsTotal(int fruitsChange) {
    gFruitsNumberTotal += fruitsChange;
}
unsigned int GARDEN_CLASS::getWeightsTotal(void) {
    return gFruitsWeightTotal;
}
void GARDEN_CLASS::adjustWeightsTotal(int weightChange) {
    gFruitsWeightTotal += weightChange;
}
void GARDEN_CLASS::plantTree(void) {
    TREE_CLASS* currentTree = gTreeList;
    TREE_CLASS* newTree, *prevTree = NULL;
    unsigned int lowestId = 0;

    if (gLastTree != NULL) {
        if ((gLastTree->getNumber() + 1) == gTreesTotal) {
            lowestId = gTreesTotal;
            currentTree = NULL;
            prevTree = gLastTree;
        }
        else {
            while (currentTree != NULL) {
                if (currentTree->getNumber() > lowestId)
                    break;
                else
                    lowestId = currentTree->getNumber() + 1;
                prevTree = currentTree;
                currentTree = currentTree->getNext();
            }
        }
    }
    newTree = new TREE_CLASS(lowestId, currentTree, prevTree, this);
    if (gTreeList == currentTree)
        gTreeList = newTree;
    if (prevTree != NULL)
        prevTree->setNext(newTree);
    if (currentTree != NULL)
        currentTree->setPrev(newTree);
    gTreesTotal++;
    if (currentTree == NULL)
        gLastTree = newTree;
}
void GARDEN_CLASS::extractTree(unsigned int number) {
    TREE_CLASS* currentTree = gLastTree;

    while (currentTree != NULL) {
        if (currentTree->getNumber() == number)
            break;
        currentTree = currentTree->getPrev();
    }
    if (currentTree != NULL) {
        if (currentTree->getPrev() != NULL)
            currentTree->getPrev()->setNext(currentTree->getNext());
        if (currentTree->getNext() != NULL)
            currentTree->getNext()->setPrev(currentTree->getPrev());
        if (gTreeList == currentTree)
            gTreeList = currentTree->getNext();
        if (currentTree == gLastTree)
            gLastTree = currentTree->getPrev();
        delete currentTree;
    }
}
void GARDEN_CLASS::growthGarden(void) {
    TREE_CLASS* currentTree = gTreeList;

    while (currentTree != NULL) {
        currentTree->growthTree();
        currentTree = currentTree->getNext();
    }
}
void GARDEN_CLASS::fadeGarden(void) {
    TREE_CLASS* currentTree = gTreeList;

    while (currentTree != NULL) {
        currentTree->fadeTree();
        currentTree = currentTree->getNext();
    }
}
void GARDEN_CLASS::harvestGarden(unsigned int weight) {
    TREE_CLASS* currentTree = gTreeList;

    while (currentTree != NULL) {
        currentTree->harvestTree(weight);
        currentTree = currentTree->getNext();
    }
}
TREE_CLASS* GARDEN_CLASS::getTreePointer(unsigned int number) {
    TREE_CLASS* currentTree = gTreeList;

    while (currentTree != NULL) {
        if (currentTree->getNumber() == number)
            break;
        currentTree = currentTree->getNext();
    }
    return currentTree;
}
void GARDEN_CLASS::cloneTree(unsigned int number) {
    unsigned int lowestId = 0, currentNumber;
    TREE_CLASS* treeToClone = NULL, *treeInsertAfter = NULL, *newTree;
    TREE_CLASS* currentTree = gTreeList;
    bool prevTreeFound = false;

    while (currentTree != NULL) {
        currentNumber = currentTree->getNumber();
        if (currentNumber == number)
            treeToClone = currentTree;
        if (prevTreeFound == false) {
            if (currentNumber > lowestId) {
                treeInsertAfter = currentTree->getPrev();
                prevTreeFound = true;
            }
            else {
                lowestId = currentNumber + 1;
                treeInsertAfter = currentTree;
            }
        }
        if ((treeToClone != NULL) && (prevTreeFound == true))
            break;
        currentTree = currentTree->getNext();
    }
    if (treeToClone != NULL) {
        newTree = new TREE_CLASS(*treeToClone);
        newTree->setNumber(lowestId);
        if (treeInsertAfter != NULL) {
            newTree->setNext(treeInsertAfter->getNext());
            if (treeInsertAfter->getNext() != NULL)
                treeInsertAfter->getNext()->setPrev(newTree);
            treeInsertAfter->setNext(newTree);
            if (treeInsertAfter == gLastTree)
                gLastTree = newTree;
        }
        else {
            newTree->setNext(gTreeList);
            gTreeList->setPrev(newTree);
            gTreeList = newTree;
        }
        newTree->setPrev(treeInsertAfter);
        newTree->setGardenPointer(this);
        gTreesTotal++;
        gBranchesTotal += newTree->getBranchesTotal();
        gFruitsNumberTotal += newTree->getFruitsTotal();
        gFruitsWeightTotal += newTree->getWeightsTotal();
    }
}