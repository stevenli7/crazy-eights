#define NUM_OF_CARDS_IN_DECK 52
#include "Card.h"

class Deck {
    public:
    Deck();
    ~Deck();

    Card* at(int i);
    void set(int i, Card* card);
    void insert(int i, Card* card);
    void insertAtBack(Card* card);
    Card* erase(int i);
    Card* removeAtBack();
    int size();
    bool empty();

    void shuffleDeck(int numCards);
    void printDeck();
    void sortDeck(int numCards);

    private:
    Card* cards[NUM_OF_CARDS_IN_DECK];
    int currentSize;

};