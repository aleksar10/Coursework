class TREE_CLASS;

class GARDEN_CLASS {
private:
    unsigned int gTreesTotal;
    TREE_CLASS* gTreeList;
    unsigned int gBranchesTotal;
    unsigned int gFruitsNumberTotal;
    unsigned int gFruitsWeightTotal;
    TREE_CLASS* gLastTree;
public:
    GARDEN_CLASS();
    ~GARDEN_CLASS();
    unsigned int getTreesTotal(void);
    void adjustTreesTotal(int);
    unsigned int getBranchesTotal(void);
    void adjustBranchesTotal(int);
    unsigned int getFruitsTotal(void);
    void adjustFruitsTotal(int);
    unsigned int getWeightsTotal(void);
    void adjustWeightsTotal(int);
    void plantTree(void);
    void extractTree(unsigned int);
    void growthGarden(void);
    void fadeGarden(void);
    void harvestGarden(unsigned int);
    TREE_CLASS* getTreePointer(unsigned int);
    void cloneTree(unsigned int);
};