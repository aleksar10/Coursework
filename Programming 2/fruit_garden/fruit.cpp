#include <cstdlib>
#include "fruit.hpp"
#include "branch.hpp"
#include "tree.hpp"
#include "garden.hpp"

FRUIT_CLASS::FRUIT_CLASS() {
    fWeight = 0;
    fBranch = NULL;
    fNext = NULL;
    fPrev = NULL;
}
FRUIT_CLASS::FRUIT_CLASS(const FRUIT_CLASS& fSrc) {
    fWeight = fSrc.fWeight;
    fBranchPos = fSrc.fBranchPos;
    fBranch = NULL;
    fNext = NULL;
    fPrev = NULL;
}
FRUIT_CLASS::FRUIT_CLASS(unsigned int branchPos, FRUIT_CLASS* next,
                         FRUIT_CLASS* prev, BRANCH_CLASS* parentBranch) {
    fWeight = 0;
    fBranchPos = branchPos;
    fBranch = parentBranch;
    fNext = next;
    fPrev = prev;
}
FRUIT_CLASS::~FRUIT_CLASS() {
    if (fPrev != NULL)
        fPrev->fNext = fNext;
    if (fNext != NULL)
        fNext->fPrev = fPrev;
    if (fBranch != NULL) {
        fBranch->adjustFruitsTotal(-1);
        if (fBranch->getTreePointer() != NULL) {
            fBranch->getTreePointer()->adjustFruitsTotal(-1);
            if (fBranch->getTreePointer()->getGardenPointer() != NULL)
                fBranch->getTreePointer()->getGardenPointer()->adjustFruitsTotal(-1);
        }
    }
    if (fWeight > 0) {
        if (fBranch != NULL) {
            fBranch->adjustWeightsTotal(-fWeight);
            if (fBranch->getTreePointer() != NULL) {
                fBranch->getTreePointer()->adjustWeightsTotal(-fWeight);
                if (fBranch->getTreePointer()->getGardenPointer() != NULL)
                    fBranch->getTreePointer()->getGardenPointer()->adjustWeightsTotal(-fWeight);
            }
        }
    }
}
unsigned int FRUIT_CLASS::getLength(void) {
    return fBranchPos;
}
unsigned int FRUIT_CLASS::getWeight(void) {
    return fWeight;
}
void FRUIT_CLASS::growthFruit(void) {
    fWeight++;
    if (fBranch != NULL) {
        fBranch->adjustWeightsTotal(1);
        if (fBranch->getTreePointer() != NULL) {
            fBranch->getTreePointer()->adjustWeightsTotal(1);
            if (fBranch->getTreePointer()->getGardenPointer() != NULL)
                fBranch->getTreePointer()->getGardenPointer()->adjustWeightsTotal(1);
        }
    }
}
void FRUIT_CLASS::fadeFruit(void) {
    if (fWeight > 0) {
        fWeight--;
        if (fBranch != NULL) {
            fBranch->adjustWeightsTotal(-1);
            if (fBranch->getTreePointer() != NULL) {
                fBranch->getTreePointer()->adjustWeightsTotal(-1);
                if (fBranch->getTreePointer()->getGardenPointer() != NULL)
                    fBranch->getTreePointer()->getGardenPointer()->adjustWeightsTotal(-1);
            }
        }
    }
}
void FRUIT_CLASS::pluckFruit(void) {
    unsigned int oldfWeight = fWeight;
    if (oldfWeight > 0) {
        fWeight = 0;
        if (fBranch != NULL) {
            fBranch->adjustWeightsTotal(-oldfWeight);
            if (fBranch->getTreePointer() != NULL) {
                fBranch->getTreePointer()->adjustWeightsTotal(-oldfWeight);
                if (fBranch->getTreePointer()->getGardenPointer() != NULL)
                    fBranch->getTreePointer()->getGardenPointer()->adjustWeightsTotal(-oldfWeight);
            }
        }
    }
}
BRANCH_CLASS* FRUIT_CLASS::getBranchPointer(void) {
    return fBranch;
}
FRUIT_CLASS* FRUIT_CLASS::getNext(void) {
    return fNext;
};
void FRUIT_CLASS::setNext(FRUIT_CLASS* next) {
    fNext = next;
}
void FRUIT_CLASS::setPrev(FRUIT_CLASS* prev) {
    fPrev = prev;
}
void FRUIT_CLASS::setParent(BRANCH_CLASS* parent) {
    fBranch = parent;
}