class BRANCH_CLASS;

class FRUIT_CLASS {
private:
    unsigned int fWeight;
    BRANCH_CLASS* fBranch;
    unsigned int fBranchPos;
    FRUIT_CLASS* fNext;
    FRUIT_CLASS* fPrev;
public:
    FRUIT_CLASS();
    FRUIT_CLASS(const FRUIT_CLASS&);
    FRUIT_CLASS(unsigned int, FRUIT_CLASS*, FRUIT_CLASS*, BRANCH_CLASS*);
    ~FRUIT_CLASS();
    unsigned int getLength(void);
    unsigned int getWeight(void);
    void growthFruit(void);
    void fadeFruit(void);
    void pluckFruit(void);
    BRANCH_CLASS* getBranchPointer(void);
    FRUIT_CLASS* getNext(void);
    void setNext(FRUIT_CLASS*);
    void setPrev(FRUIT_CLASS*);
    void setParent(BRANCH_CLASS*);
};