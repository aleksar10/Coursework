#include <cstdlib>
#include "branch.hpp"
#include "tree.hpp"
#include "garden.hpp"

TREE_CLASS::TREE_CLASS() {
    tNumber = 0;
    tHeight = 0;
    tBranches = 0;
    tFruitsNumber = 0;
    tFruitsWeight = 0;
    tBranchList = NULL;
    tLastBranch = NULL;
    tNext = NULL;
    tPrev = NULL;
    tGarden = NULL;
}
TREE_CLASS::TREE_CLASS(const TREE_CLASS& tSrc) {
    BRANCH_CLASS* newBranch, *previousNewBranch = NULL;
    BRANCH_CLASS* currentBranch = tSrc.tLastBranch;

    tNumber = 0;
    tNext = NULL;
    tPrev = NULL;
    tGarden = NULL;
    tBranchList = NULL;
    tLastBranch = NULL;
    tHeight = tSrc.tHeight;
    tBranches = tSrc.tBranches;
    tFruitsNumber = tSrc.tFruitsNumber;
    tFruitsWeight = tSrc.tFruitsWeight;
    while (currentBranch != NULL) {
        newBranch = new BRANCH_CLASS(*currentBranch);
        newBranch->setHeight(currentBranch->getHeight());
        newBranch->setTreePointer(this);
        newBranch->setNext(previousNewBranch);
        if (previousNewBranch != NULL)
            previousNewBranch->setPrev(newBranch);
        else
            tLastBranch = newBranch;
        tBranchList = newBranch;
        previousNewBranch = newBranch;
        currentBranch = currentBranch->getPrev();
    }
}
TREE_CLASS::TREE_CLASS(unsigned int number, TREE_CLASS* next,
                       TREE_CLASS* prev, GARDEN_CLASS* parent) {
    tNumber = number;
    tHeight = 0;
    tBranches = 0;
    tFruitsNumber = 0;
    tFruitsWeight = 0;
    tBranchList = NULL;
    tLastBranch = NULL;
    tNext = next;
    tPrev = prev;
    tGarden = parent;
}
TREE_CLASS::~TREE_CLASS() {
    BRANCH_CLASS* currBranch = tBranchList, *tmp = NULL;

    while (currBranch != NULL) {
        tmp = currBranch;
        currBranch = currBranch->getNext();
        delete tmp;
    }
    if (tPrev != NULL)
        tPrev->tNext = tNext;
    if (tNext != NULL)
        tNext->tPrev = tPrev;
    if (tGarden != NULL)
        tGarden->adjustTreesTotal(-1);
}
unsigned int TREE_CLASS::getBranchesTotal(void) {
    return tBranches;
}
void TREE_CLASS::adjustBranchesTotal(int changeBranches) {
    tBranches += changeBranches;
}
unsigned int TREE_CLASS::getFruitsTotal(void) {
    return tFruitsNumber;
}
void TREE_CLASS::adjustFruitsTotal(int changeFruits) {
    tFruitsNumber += changeFruits;
}
unsigned int TREE_CLASS::getWeightsTotal(void) {
    return tFruitsWeight;
}
void TREE_CLASS::adjustWeightsTotal(int changeWeight) {
    tFruitsWeight += changeWeight;
}
unsigned int TREE_CLASS::getNumber(void) {
    return tNumber;
}
void TREE_CLASS::setNumber(unsigned int number) {
    tNumber = number;
}
unsigned int TREE_CLASS::getHeight(void) {
    return tHeight;
}
void TREE_CLASS::growthTree(void) {
    BRANCH_CLASS* currentBranch = tBranchList;

    tHeight++;
    while (currentBranch != NULL) {
        currentBranch->growthBranch();
        currentBranch = currentBranch->getNext();
    }
    if ((tHeight % 3) == 0) {
        BRANCH_CLASS* newBranch = new BRANCH_CLASS(tHeight, tBranchList, NULL, this);
        tBranches++;
        if (tGarden != NULL)
            tGarden->adjustBranchesTotal(1);
        if (tBranchList != NULL)
            tBranchList->setPrev(newBranch);
        else
            tLastBranch = newBranch;
        tBranchList = newBranch;
    }
}
void TREE_CLASS::fadeTree(void) {
    BRANCH_CLASS* currentBranch = tBranchList, *delBranch;

    if (tHeight > 0)
        tHeight--;
    while (currentBranch != NULL) {
        if (currentBranch->getHeight() > tHeight) {
            delBranch = currentBranch;
            if (delBranch == tBranchList)
                tBranchList = delBranch->getNext();
            currentBranch = currentBranch->getNext();
            tFruitsNumber -= delBranch->getFruitsTotal();
            if (tLastBranch == delBranch)
                tLastBranch = NULL;
            delete delBranch;
        }
        else {
            currentBranch->fadeBranch();
            currentBranch = currentBranch->getNext();
        }
    }
}
void TREE_CLASS::harvestTree(unsigned int weight) {
    BRANCH_CLASS* currentBranch = tBranchList;

    while (currentBranch != NULL) {
        currentBranch->harvestBranch(weight);
        currentBranch = currentBranch->getNext();
    }
}
void TREE_CLASS::cutTree(unsigned int height) {
    BRANCH_CLASS* currentBranch = tBranchList, *delBranch;

    if (tHeight > height)
        tHeight = height;
    while (currentBranch != NULL) {
        if (currentBranch->getHeight() > tHeight) {
            delBranch = currentBranch;
            if (delBranch == tBranchList)
                tBranchList = delBranch->getNext();
            currentBranch = currentBranch->getNext();
            if (tLastBranch == delBranch)
                tLastBranch = NULL;
            delete delBranch;
        }
        else
            currentBranch = currentBranch->getNext();
    }
}
void TREE_CLASS::cloneBranch(BRANCH_CLASS* bSrc) {
    BRANCH_CLASS* currentBranch = tLastBranch;
    BRANCH_CLASS* newBranch;

    while (currentBranch != NULL) {
        if (currentBranch->getLength() == 0)
            break;
        currentBranch = currentBranch->getPrev();
    }
    if (currentBranch != NULL) {
        newBranch = new BRANCH_CLASS(*bSrc);
        newBranch->setHeight(currentBranch->getHeight());
        newBranch->setTreePointer(this);
        newBranch->setPrev(currentBranch->getPrev());
        newBranch->setNext(currentBranch->getNext());
        if (currentBranch->getPrev() != NULL)
            currentBranch->getPrev()->setNext(newBranch);
        if (currentBranch->getNext() != NULL)
            currentBranch->getNext()->setPrev(newBranch);
        if (currentBranch == tBranchList)
            tBranchList = newBranch;
        if (currentBranch == tLastBranch)
            tLastBranch = newBranch;
        tFruitsNumber += newBranch->getFruitsTotal();
        tFruitsWeight += newBranch->getWeightsTotal();
        if (tGarden != NULL) {
            tGarden->adjustFruitsTotal(newBranch->getFruitsTotal());
            tGarden->adjustWeightsTotal(newBranch->getWeightsTotal());
        }
        currentBranch->setNext(NULL);
        currentBranch->setPrev(NULL);
        delete currentBranch;
        tBranches++;
        if (tGarden != NULL)
            tGarden->adjustBranchesTotal(1);
    }
}
GARDEN_CLASS* TREE_CLASS::getGardenPointer(void) {
    return tGarden;
}
void TREE_CLASS::setGardenPointer(GARDEN_CLASS* parentGarden) {
    tGarden = parentGarden;
}
BRANCH_CLASS* TREE_CLASS::getBranchPointer(unsigned int height) {
    BRANCH_CLASS* currentBranch = tBranchList;
    
    while (currentBranch != NULL) {
        if (currentBranch->getHeight() == height)
            break;
        currentBranch = currentBranch->getNext();
    }
    return currentBranch;
}
TREE_CLASS* TREE_CLASS::getNext(void) {
    return tNext;
};
void TREE_CLASS::setNext(TREE_CLASS* next) {
    tNext = next;
};
TREE_CLASS* TREE_CLASS::getPrev(void) {
    return tPrev;
};
void TREE_CLASS::setPrev(TREE_CLASS* prev) {
    tPrev = prev;
};