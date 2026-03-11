#include <iostream>
#include <string>

using namespace std;

class CAESAR_CLASS;
class ARENA_CLASS;
class SQUAD_CLASS;

class PLAYER_CLASS {
protected:
    unsigned int maxHealth;
    unsigned int currentHealth;
    unsigned int attack;
    unsigned int agility;
    string playerID;
    PLAYER_CLASS* next;
    PLAYER_CLASS* prev;
    SQUAD_CLASS* parentSquad;
    friend CAESAR_CLASS;
    friend SQUAD_CLASS;
    virtual void die();
public:
    PLAYER_CLASS();
    PLAYER_CLASS(unsigned int, unsigned int, unsigned int, unsigned int);
    virtual unsigned int getRemainingHealth();
    virtual unsigned int getAgility();
    virtual void applyWinnerReward();
    virtual void cure();
    PLAYER_CLASS* getNext();
    PLAYER_CLASS* getPrev();
    void setNext(PLAYER_CLASS*);
    void setPrev(PLAYER_CLASS*);
    void setParentSquad(SQUAD_CLASS*);
    virtual const string& getID();
    virtual unsigned int getDamage() = 0;
    virtual void takeDamage(unsigned int) = 0;
    virtual void printParams() = 0;
    virtual unsigned int getDefense();
};

class HUMAN_CLASS : virtual public PLAYER_CLASS {
protected:
    string humanID;
    unsigned int defense;
public:
    HUMAN_CLASS(string);
    virtual const string& getID();
    virtual unsigned int getDamage();
    virtual void takeDamage(unsigned int);
    void setDefense(unsigned int);
    virtual void printParams();
    virtual unsigned int getDefense();
};

class BEAST_CLASS : virtual public PLAYER_CLASS {
protected:
    string beastID;
public:
    BEAST_CLASS(string);
    virtual const string& getID();
    virtual unsigned int getDamage();
    virtual void takeDamage(unsigned int);
    virtual void printParams();
    virtual unsigned int getDefense();
};

class BERSERKER_CLASS : public HUMAN_CLASS, public BEAST_CLASS {
    BERSERKER_CLASS();
public:
    BERSERKER_CLASS(string, string);
    virtual const string& getID();
    virtual unsigned int getDamage();
    virtual void takeDamage(unsigned int);
    virtual void printParams();
    virtual unsigned int getDefense();
};

class CAESAR_CLASS {
    unsigned short defendants;
    unsigned short attacksCount;
    friend ARENA_CLASS;
public:
    CAESAR_CLASS();
    void judgeDeathOrLife(PLAYER_CLASS*);
};

class ARENA_CLASS {
    CAESAR_CLASS caesar;
    ARENA_CLASS();
public:
    ARENA_CLASS(CAESAR_CLASS*);
    void fight(PLAYER_CLASS*, PLAYER_CLASS*);
    friend CAESAR_CLASS;
};

class SQUAD_CLASS : public PLAYER_CLASS {
    string squadID;
    PLAYER_CLASS* playerList;
    unsigned int members;
public:
    SQUAD_CLASS(string);
    void addPlayer(PLAYER_CLASS*);
    virtual unsigned int getDamage();
    virtual void takeDamage(unsigned int);
    virtual unsigned int getAgility();
    void printParams();
    virtual const string& getID();
    void removePlayer(PLAYER_CLASS*);
    virtual void die();
    virtual void cure();
    bool firstLesserThanSecond(PLAYER_CLASS*, PLAYER_CLASS*);
    virtual unsigned int getRemainingHealth();
    virtual void applyWinnerReward();
    PLAYER_CLASS* split(PLAYER_CLASS*);
    PLAYER_CLASS* merge(PLAYER_CLASS*, PLAYER_CLASS*);
    PLAYER_CLASS* mergeSort(PLAYER_CLASS*);
};
PLAYER_CLASS::PLAYER_CLASS() :
    maxHealth(0),
    currentHealth(0),
    attack(0),
    agility(0),
    playerID(""),
    next(NULL),
    prev(NULL),
    parentSquad(NULL)
    {}
PLAYER_CLASS::PLAYER_CLASS(unsigned int inputMaxHealth, unsigned int inputCurrentHealth,
                           unsigned int inputAttack, unsigned int inputAgility) :
    maxHealth(inputMaxHealth),
    currentHealth(inputCurrentHealth),
    attack(inputAttack),
    agility(inputAgility),
    playerID(""),   
    next(NULL),
    prev(NULL),
    parentSquad(NULL)
    {}

void PLAYER_CLASS::die() {
    currentHealth = 0;
    if (parentSquad != NULL)
        parentSquad->removePlayer(this);
}
unsigned int PLAYER_CLASS::getRemainingHealth() {
    return (currentHealth*100)/maxHealth;
}
unsigned int PLAYER_CLASS::getAgility() {
    return agility;
}
void PLAYER_CLASS::applyWinnerReward() {
    attack += 2;
    agility += 2;
}
void PLAYER_CLASS::cure() {
    currentHealth = maxHealth;
}
PLAYER_CLASS* PLAYER_CLASS::getNext() {
    return next;
}
PLAYER_CLASS* PLAYER_CLASS::getPrev() {
    return prev;
}
void PLAYER_CLASS::setNext(PLAYER_CLASS* inputNext) {
    next = inputNext;
}
void PLAYER_CLASS::setPrev(PLAYER_CLASS* inputPrev) {
    prev = inputPrev;
}
const string& PLAYER_CLASS::getID() {
    return playerID;
}
void PLAYER_CLASS::setParentSquad(SQUAD_CLASS* inputSquad) {
    parentSquad = inputSquad;
}
unsigned int PLAYER_CLASS::getDefense() {
    return 0;
}
HUMAN_CLASS::HUMAN_CLASS(string inputId) :
    PLAYER_CLASS(200, 200, 30, 10),
    humanID(inputId),
    defense(10)
    {}
unsigned int HUMAN_CLASS::getDamage() {
    return attack;
}
void HUMAN_CLASS::takeDamage(unsigned int inputDamage) {
    if ((defense + agility) < inputDamage) {
        unsigned int damage;
        damage = inputDamage - defense - agility;
        if (damage >= currentHealth)
            die();
        else
            currentHealth -= damage;
    }
}
void HUMAN_CLASS::setDefense(unsigned int inputDefense) {
    defense = inputDefense;
}
void HUMAN_CLASS::printParams() {
    cout << humanID << ":";
    if (currentHealth > 0)
        cout << maxHealth << ":" << currentHealth << ":" << getRemainingHealth()
             << "%:" << attack << ":" << agility << ":" << defense << endl;
    else
        cout << "R.I.P." << endl;
}
const string& HUMAN_CLASS::getID(){
    return humanID;
}
unsigned int HUMAN_CLASS::getDefense() {
    return defense;
}
BEAST_CLASS::BEAST_CLASS(string inputId) :
    PLAYER_CLASS(150, 150, 40, 20),
    beastID(inputId)
    {}
const string& BEAST_CLASS::getID(){
    return beastID;
}
unsigned int BEAST_CLASS::getDamage() {
    if (getRemainingHealth() < 25)
        return 2*attack;
    else
        return attack;
}
void BEAST_CLASS::takeDamage(unsigned int inputDamage) {
    if ((agility/2) >= inputDamage)
        return;
    if ((inputDamage - agility/2) >= currentHealth)
        die();
    else
        currentHealth -= (inputDamage - agility/2);
}
void BEAST_CLASS::printParams() {
    cout << beastID << ":";
    if (getRemainingHealth() > 0) {
        unsigned int currentAttack;
        if (getRemainingHealth() < 25)
            currentAttack = 2*attack;
        else
            currentAttack = attack;
        cout << maxHealth << ":" << currentHealth << ":" << getRemainingHealth()
             << "%:" << currentAttack << ":" << agility << endl;
    }
    else
        cout << "R.I.P." << endl;
}
unsigned int BEAST_CLASS::getDefense() {
    return 0;
}
BERSERKER_CLASS::BERSERKER_CLASS(string inputHumanID, string inputBeastID) :
    PLAYER_CLASS(200, 200, 35, 5),
    HUMAN_CLASS(inputHumanID),
    BEAST_CLASS(inputBeastID) {
    setDefense(15);
}
const string& BERSERKER_CLASS::getID() {
    if ((getRemainingHealth() < 25) && (getRemainingHealth() > 0))
        return BEAST_CLASS::getID();
    else
        return HUMAN_CLASS::getID();
}
unsigned int BERSERKER_CLASS::getDamage() {
    if (getRemainingHealth() < 25)
        return BEAST_CLASS::getDamage();
    else
        return HUMAN_CLASS::getDamage();
}
void BERSERKER_CLASS::takeDamage(unsigned int damage) {
    if (getRemainingHealth() < 25)
        return BEAST_CLASS::takeDamage(damage);
    else
        return HUMAN_CLASS::takeDamage(damage);
}
void BERSERKER_CLASS::printParams() {
    if ((getRemainingHealth() < 25) && (getRemainingHealth() > 0))
        return BEAST_CLASS::printParams();
    else
        return HUMAN_CLASS::printParams();
}
unsigned int BERSERKER_CLASS::getDefense() {
    if ((getRemainingHealth() < 25) && (getRemainingHealth() > 0))
        return BEAST_CLASS::getDefense();
    else
        return HUMAN_CLASS::getDefense();
}
CAESAR_CLASS::CAESAR_CLASS() :
    defendants(0),
    attacksCount(0)
    {}
void CAESAR_CLASS::judgeDeathOrLife(PLAYER_CLASS* player) {
    defendants++;
    if (defendants == 3) {
        defendants = 0;
        if ((attacksCount % 2) == 0)
            player->die();
    }
}
ARENA_CLASS::ARENA_CLASS(CAESAR_CLASS* inputCaesar) {
    caesar = *inputCaesar;
}
void ARENA_CLASS::fight(PLAYER_CLASS* player1, PLAYER_CLASS* player2) {
    if ((player1->getRemainingHealth() <= 0) || (player2->getRemainingHealth() <= 0))
        return;

    caesar.attacksCount = 0;
    PLAYER_CLASS* firstPlayer = player1, *secondPlayer = player2;

    if (player2->getAgility() > player1->getAgility()) {
        firstPlayer = player2;
        secondPlayer = player1;
    }
    firstPlayer->printParams();
    secondPlayer->printParams();
    while (true) {
        if (firstPlayer->getRemainingHealth() > 0) {
            caesar.attacksCount++;
            secondPlayer->takeDamage(firstPlayer->getDamage());
            secondPlayer->printParams();
            if ((caesar.attacksCount == 40) || (secondPlayer->getRemainingHealth() < 10))
                break;
        }
        else
            break;
        if (secondPlayer->getRemainingHealth() > 0) {
            caesar.attacksCount++;
            firstPlayer->takeDamage(secondPlayer->getDamage());
            firstPlayer->printParams();
            if ((caesar.attacksCount == 40) || (firstPlayer->getRemainingHealth() < 10))
                break;
        }
        else
            break;
    }
    if (firstPlayer->getRemainingHealth() > 0) {
        caesar.judgeDeathOrLife(firstPlayer);
        firstPlayer->printParams();
    }
    if (secondPlayer->getRemainingHealth() > 0) {
        caesar.judgeDeathOrLife(secondPlayer);
        secondPlayer->printParams();
    }
    if (firstPlayer->getRemainingHealth() > 0) {
        firstPlayer->applyWinnerReward();
        firstPlayer->cure();
    }
    if (secondPlayer->getRemainingHealth() > 0) {
        secondPlayer->applyWinnerReward();
        secondPlayer->cure();
    }
    firstPlayer->printParams();
    secondPlayer->printParams();
}
SQUAD_CLASS::SQUAD_CLASS(string identifier) :
    PLAYER_CLASS(0, 0, 0, ~0u),
    squadID(identifier),
    playerList(NULL),
    members(0)
    {}
void SQUAD_CLASS::addPlayer(PLAYER_CLASS* inputPlayer) {
    PLAYER_CLASS* currentPlayer = playerList;
    PLAYER_CLASS* prevPlayer = NULL;

    if (inputPlayer->getRemainingHealth() == 0)
        return;

    if (currentPlayer == NULL) {
        playerList = inputPlayer;
        inputPlayer->setPrev(NULL);
        inputPlayer->setNext(NULL);
    }
    else {
        while (currentPlayer != NULL) {
            if (currentPlayer == inputPlayer)
                return;
            if (firstLesserThanSecond(currentPlayer, inputPlayer)) {
                prevPlayer = currentPlayer;
                currentPlayer = currentPlayer->getNext();
            }
            else {
                if (inputPlayer == currentPlayer)
                    return;
                inputPlayer->setNext(currentPlayer);
                inputPlayer->setPrev(currentPlayer->getPrev());
                if (currentPlayer->getPrev() == NULL)
                    playerList = inputPlayer;
                else
                    currentPlayer->getPrev()->setNext(inputPlayer);
                currentPlayer->setPrev(inputPlayer);
                break;
            }
        }
        if (currentPlayer == NULL) {
            inputPlayer->setPrev(prevPlayer);
            inputPlayer->setNext(NULL);
            prevPlayer->setNext(inputPlayer);
        }
    }
    members++;
    inputPlayer->setParentSquad(this);
}
unsigned int SQUAD_CLASS::getDamage() {
    PLAYER_CLASS* currentPlayer = playerList;
    unsigned int currentDamage = 0;

    while (currentPlayer != NULL) {
        currentDamage += currentPlayer->getDamage();
        currentPlayer = currentPlayer->getNext();
    }
    return currentDamage;
}
void SQUAD_CLASS::takeDamage(unsigned int inputDamage) {
    PLAYER_CLASS* currentPlayer = playerList;
    unsigned int damage = inputDamage / members;

    while (currentPlayer != NULL) {
        currentPlayer->takeDamage(damage);
        currentPlayer = currentPlayer->getNext();
    }
}
unsigned int SQUAD_CLASS::getAgility() {
    PLAYER_CLASS* currentPlayer = playerList;
    unsigned int currentAgility = ~0u;

    while (currentPlayer != NULL) {
        if (currentPlayer->getAgility() < currentAgility)
            currentAgility = currentPlayer->getAgility();
        currentPlayer = currentPlayer->getNext();
    }
    return currentAgility;
}
void SQUAD_CLASS::printParams() {
    PLAYER_CLASS* currentPlayer;

    playerList = mergeSort(playerList);
    currentPlayer = playerList;
    cout << squadID << ":";
    if (playerList != NULL) {
        cout << members << ":" << getRemainingHealth() << "%:"
             << getDamage() << ":" << getAgility() << endl;
        while (currentPlayer != NULL) {
            currentPlayer->printParams();
            currentPlayer = currentPlayer->getNext();
        }
    }
    else
       cout << "nemo" << endl;
}
const string& SQUAD_CLASS::getID() {
    return squadID;
}
void SQUAD_CLASS::removePlayer(PLAYER_CLASS* removePlayer) {
    PLAYER_CLASS* currentPlayer = playerList;

    while (currentPlayer != NULL) {
        if (currentPlayer == removePlayer) {
            if (removePlayer->getPrev() != NULL) {
                removePlayer->getPrev()->setNext(removePlayer->getNext());
            }
            else
                playerList = removePlayer->getNext();
            if (removePlayer->getNext() != NULL) {
                removePlayer->getNext()->setPrev(removePlayer->getPrev());
            }
            members--;
            break;
        }
        currentPlayer = currentPlayer->getNext();
    }
}
void SQUAD_CLASS::die() {
    PLAYER_CLASS* currentPlayer = playerList;

    while (currentPlayer != NULL) {
        currentPlayer->die();
        currentPlayer = currentPlayer->getNext();
    }
}
void SQUAD_CLASS::cure() {
    PLAYER_CLASS* currentPlayer = playerList;

    while (currentPlayer != NULL) {
        currentPlayer->cure();
        currentPlayer = currentPlayer->getNext();
    }
}
bool SQUAD_CLASS::firstLesserThanSecond(PLAYER_CLASS* player1, PLAYER_CLASS* player2) {
    if (player1->getID() < player2->getID()) return true;
    if (player1->getID() > player2->getID()) return false;
    if (player1->maxHealth < player2->maxHealth) return true;
    if (player1->maxHealth > player2->maxHealth) return false;
    if (player1->currentHealth < player2->currentHealth) return true;
    if (player1->currentHealth > player2->currentHealth) return false;
    if (player1->getRemainingHealth() < player2->getRemainingHealth()) return true;
    if (player1->getRemainingHealth() > player2->getRemainingHealth()) return false;
    if (player1->getDamage() < player2->getDamage()) return true;
    if (player1->getDamage() > player2->getDamage()) return false;
    if (player1->getAgility() < player2->getAgility()) return true;
    if (player1->getAgility() > player2->getAgility()) return false;
    return (player1->getDefense() < player2->getDefense());
}
unsigned int SQUAD_CLASS::getRemainingHealth() {
    PLAYER_CLASS* currentPlayer = playerList;
    unsigned int remainingHealth = 0;

    while (currentPlayer != NULL) {
        if (currentPlayer->getRemainingHealth() > remainingHealth)
            remainingHealth = currentPlayer->getRemainingHealth();
        currentPlayer = currentPlayer->getNext();
    }
    return remainingHealth;
}
void SQUAD_CLASS::applyWinnerReward() {
    PLAYER_CLASS* currentPlayer = playerList;

    while (currentPlayer != NULL) {
        currentPlayer->applyWinnerReward();
        currentPlayer = currentPlayer->getNext();
    }
}
PLAYER_CLASS* SQUAD_CLASS::split(PLAYER_CLASS* head) {
    PLAYER_CLASS* slow = head;
    PLAYER_CLASS* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    PLAYER_CLASS* secondHalf = slow->next;
    slow->next = NULL;
    if (secondHalf) secondHalf->prev = NULL;
    return secondHalf;
}
PLAYER_CLASS* SQUAD_CLASS::merge(PLAYER_CLASS* first, PLAYER_CLASS* second) {
    if (!first) return second;
    if (!second) return first;

    if (firstLesserThanSecond(first, second)) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    } else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}
PLAYER_CLASS* SQUAD_CLASS::mergeSort(PLAYER_CLASS* head) {
    if (!head || !head->next) return head;

    PLAYER_CLASS* secondHalf = split(head);
    head = mergeSort(head);
    secondHalf = mergeSort(secondHalf);

    return merge(head, secondHalf);
}