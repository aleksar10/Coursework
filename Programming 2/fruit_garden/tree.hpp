class BRANCH_CLASS;
class GARDEN_CLASS;

class TREE_CLASS {
private:
    unsigned int tNumber;
    unsigned tHeight;
    unsigned int tBranches;
    unsigned int tFruitsNumber;
    unsigned int tFruitsWeight;
    BRANCH_CLASS* tBranchList;
    BRANCH_CLASS* tLastBranch;
    TREE_CLASS* tNext;
    TREE_CLASS* tPrev;
    GARDEN_CLASS* tGarden;
public:
    TREE_CLASS();
    TREE_CLASS(const TREE_CLASS &);
    TREE_CLASS(unsigned int, TREE_CLASS*, TREE_CLASS*, GARDEN_CLASS*);
    ~TREE_CLASS();
unsigned int getBranchesTotal(void);
    void adjustBranchesTotal(int);
    unsigned int getFruitsTotal(void);
    void adjustFruitsTotal(int);
    unsigned int getWeightsTotal(void);
    void adjustWeightsTotal(int);
    unsigned int getNumber(void);
    void setNumber(unsigned int);
    unsigned int getHeight(void);
    void growthTree(void);
    void fadeTree(void);
    void harvestTree(unsigned int);
    void cutTree(unsigned int);
    void cloneBranch(BRANCH_CLASS*);
    GARDEN_CLASS* getGardenPointer(void);
    void setGardenPointer(GARDEN_CLASS*);
    BRANCH_CLASS* getBranchPointer(unsigned int);
    TREE_CLASS* getNext(void);
    TREE_CLASS* getPrev(void);
    void setNext(TREE_CLASS*);
    void setPrev(TREE_CLASS*);
};