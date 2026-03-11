class FRUIT_CLASS;
class TREE_CLASS;

class BRANCH_CLASS {
private:
    unsigned int bLength;
    unsigned int bFruits;
    unsigned int bFruitsWeight;
    unsigned int bHeight;
    FRUIT_CLASS* bFruitList;
    TREE_CLASS* bTree;
    BRANCH_CLASS* bNext;
    BRANCH_CLASS* bPrev;
public:
    BRANCH_CLASS();
    BRANCH_CLASS(const BRANCH_CLASS&);
    BRANCH_CLASS(unsigned int, BRANCH_CLASS*, BRANCH_CLASS*, TREE_CLASS*);
    ~BRANCH_CLASS();
    unsigned int getFruitsTotal(void);
    void adjustFruitsTotal(int);
    unsigned int getWeightsTotal(void);
    void adjustWeightsTotal(int);
    unsigned int getHeight(void);
    void setHeight(unsigned int);
    unsigned int getLength(void);
    void growthBranch(void);
    void fadeBranch(void);
    void harvestBranch(unsigned int);
    void cutBranch(unsigned int);
    FRUIT_CLASS* getFruitPointer(unsigned int);
    TREE_CLASS* getTreePointer(void);
    void setTreePointer(TREE_CLASS*);
    BRANCH_CLASS* getNext(void);
    void setNext(BRANCH_CLASS*);
    BRANCH_CLASS* getPrev(void);
    void setPrev(BRANCH_CLASS*);
};