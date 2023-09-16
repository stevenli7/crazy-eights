#include <string>
#include "Deck.h"

using namespace std;

typedef string Name;

class Player {
    public:

    void insert(Card* card);
    int findCard(char rank, char suit);
    Card* remove(Card* card);
    Card* removeAtBack();
    int size();
    Card* checkValidMove(string input, char newSuit, Card* topCard, bool firstMove); 
    bool canPlayCard(Card* topCard, char newSuit, bool firstMove); 
    bool checkValidInput(string input, bool firstMove, bool inputSuit); 
    bool winner();
    void sortHand();
    void printHand();

    Name name;
    Player* nextPlayer;

    private:
    Deck cards;

};




