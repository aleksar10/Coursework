#include <cstdlib>
#include "fruit.hpp"
#include "branch.hpp"
#include "tree.hpp"
#include "garden.hpp"

BRANCH_CLASS::BRANCH_CLASS() {
    bLength = 0;
    bFruits = 0;
    bFruitsWeight = 0;
    bHeight = 0;
    bFruitList = 0;
    bTree = 0;
    bNext = NULL;
    bPrev = NULL;
}
BRANCH_CLASS::BRANCH_CLASS(const BRANCH_CLASS& bSrc) {
    FRUIT_CLASS* newFruit;
    FRUIT_CLASS* currentSrcFruit = bSrc.bFruitList;

    bLength = bSrc.bLength;
    bFruits = bSrc.bFruits;
    bFruitsWeight = bSrc.bFruitsWeight;
    bFruitList = NULL;
    while (currentSrcFruit != NULL) {
        newFruit = new FRUIT_CLASS(*currentSrcFruit);
        newFruit->setParent(this);
        newFruit->setNext(bFruitList);
        if (bFruitList != NULL) { 
            bFruitList->setPrev(newFruit);
        }
        bFruitList = newFruit;
        currentSrcFruit = currentSrcFruit->getNext();
    }
    bHeight = 0;
    bTree = NULL;
    bNext = NULL;
    bPrev = NULL;
}
BRANCH_CLASS::BRANCH_CLASS(unsigned int height, BRANCH_CLASS* next,
                           BRANCH_CLASS* prev, TREE_CLASS* parent) {
    bLength = 0;
    bFruits = 0;
    bFruitsWeight = 0;
    bHeight = height;
    bFruitList = 0;
    bTree = parent;
    bNext = next;
    bPrev = prev;
}
BRANCH_CLASS::~BRANCH_CLASS() {
    FRUIT_CLASS* currFruit = bFruitList, *tmp = NULL;

    while (currFruit != NULL) {
        tmp = currFruit;
        currFruit = currFruit->getNext();
        delete tmp;
    }
    if (bPrev != NULL)
        bPrev->bNext = bNext;
    if (bNext != NULL)
        bNext->bPrev = bPrev;
    if (bTree != NULL) {
        bTree->adjustBranchesTotal(-1);
        if (bTree->getGardenPointer() != NULL)
            bTree->getGardenPointer()->adjustBranchesTotal(-1);
    }
}
unsigned int BRANCH_CLASS::getFruitsTotal(void) {
    return bFruits;
}
void BRANCH_CLASS::adjustFruitsTotal(int fruitsChange) {
    bFruits += fruitsChange;
}
unsigned int BRANCH_CLASS::getWeightsTotal(void) {
    return bFruitsWeight;
}
void BRANCH_CLASS::adjustWeightsTotal(int weightChange) {
    bFruitsWeight += weightChange;
}
unsigned int BRANCH_CLASS::getHeight(void) {
    return bHeight;
}
void BRANCH_CLASS::setHeight(unsigned int height) {
    bHeight = height;
}
unsigned int BRANCH_CLASS::getLength(void) {
    return bLength;
}
void BRANCH_CLASS::growthBranch(void) {
    FRUIT_CLASS* currentFruit = bFruitList, *newFruit;

    bLength++;
    while (currentFruit != NULL) {
        currentFruit->growthFruit();
        currentFruit = currentFruit->getNext();
    }
    if ((bLength % 2) == 0) {
        newFruit = new FRUIT_CLASS(bLength, bFruitList, NULL, this);
        bFruits++;
        if (bTree != NULL) {
            bTree->adjustFruitsTotal(1);
            if (bTree->getGardenPointer() != NULL)
                bTree->getGardenPointer()->adjustFruitsTotal(1);
        }
        if (bFruitList != NULL)
            bFruitList->setPrev(newFruit);
        bFruitList = newFruit;
    }
}
void BRANCH_CLASS::fadeBranch(void) {
    FRUIT_CLASS* currentFruit = bFruitList, *delFruit;

    if (bLength > 0)
        bLength--;
    while (currentFruit != NULL) {
        if (currentFruit->getLength() > bLength) {
            delFruit = currentFruit;
            if (delFruit == bFruitList)
                bFruitList = delFruit->getNext();
            currentFruit = currentFruit->getNext();
            delete delFruit;
        }
        else {
            currentFruit->fadeFruit();
            currentFruit = currentFruit->getNext();
        }
    }
}
void BRANCH_CLASS::harvestBranch(unsigned int weight) {
    FRUIT_CLASS* currentFruit = bFruitList;

    while (currentFruit != NULL) {
        if (currentFruit->getWeight() >= weight) {
            currentFruit->pluckFruit();
        }
        currentFruit = currentFruit->getNext();
    }
}
void BRANCH_CLASS::cutBranch(unsigned int length) {
    FRUIT_CLASS* currentFruit = bFruitList, *delFruit;

    if (bLength > length)
        bLength = length;
    while (currentFruit != NULL) {
        if (currentFruit->getLength() > bLength) {
            delFruit = currentFruit;
            if (delFruit == bFruitList)
                bFruitList = delFruit->getNext();
            currentFruit = currentFruit->getNext();
            delete delFruit;
        }
        else {
            currentFruit = currentFruit->getNext();
        }
    }
}
FRUIT_CLASS* BRANCH_CLASS::getFruitPointer(unsigned int length) {
    FRUIT_CLASS* currentFruit = bFruitList;
    
    while (currentFruit != NULL) {
        if (currentFruit->getLength() == length)
            break;
        currentFruit = currentFruit->getNext();
    }
    return currentFruit;
}
TREE_CLASS* BRANCH_CLASS::getTreePointer(void) {
    return bTree;
}
void BRANCH_CLASS::setTreePointer(TREE_CLASS* parentTree) {
    bTree = parentTree;
}
BRANCH_CLASS* BRANCH_CLASS::getNext(void) {
    return bNext;
};
void BRANCH_CLASS::setNext(BRANCH_CLASS* next) {
    bNext = next;
};
BRANCH_CLASS* BRANCH_CLASS::getPrev(void) {
    return bPrev;
};
void BRANCH_CLASS::setPrev(BRANCH_CLASS* prev) {
    bPrev = prev;
}