#include <iostream>
#include <time.h>
#include "Deck.h"

using namespace std;

Deck::Deck() {
    currentSize = 0;
}

Deck::~Deck() {
}

Card* Deck::at(int i) {
    if (i < 0 || i >= currentSize) {
        throw out_of_range("Invalid index.");
    }
    return cards[i];
}

void Deck::set(int i, Card* card) {
    if (i < 0 || i >= currentSize) {
        throw out_of_range("Invalid index.");
    }
    cards[i] = card;
}

void Deck::insert(int i, Card* card) {
    if (i < 0 || i >= currentSize) {
        throw out_of_range("Invalid index.");
    }
    for (int j = currentSize-1; j >= i; j--) {
        cards[j+1] = cards[j];
    }
    cards[i] = card;
    currentSize++;
}

void Deck::insertAtBack(Card* card) {
    if (currentSize >= NUM_OF_CARDS_IN_DECK) {
        return;
    }
    cards[currentSize] = card;
    currentSize++;
}

Card* Deck::erase(int i) {
    if (i < 0 || i >= currentSize) {
        throw out_of_range("Invalid index.");
    }
    Card* temp = cards[i];
    for (int j = i+1; j < currentSize; j++) {
        cards[j-1] = cards[j];
    }
    currentSize--;
    return temp;
}

Card* Deck::removeAtBack() {
    if (empty()) {
        return NULL;
    }
    Card* temp = cards[currentSize-1];
    currentSize--;
    return temp;
}

int Deck::size() {
    return currentSize;
}

bool Deck::empty() {
    if (size() == 0) {
        return true;
    }
    return false;
}

void Deck::shuffleDeck(int numCards) {
    srand(time(NULL));
    for (int i = numCards-1; i > 0; i--) {
        int j = rand() % (i+1);
        Card* temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

void Deck::printDeck() {
    for (int i = 0; i < currentSize; i++) {
        cout << cards[i]->getRank() << cards[i]->getSuit() << " ";
    }
}

void Deck::sortDeck(int numCards) {
    for (int i = 1; i < numCards; i++) {
        Card* key = cards[i];
        int j = i-1;
        while (key->getValue() < cards[j]->getValue() && j >= 0) {
            cards[j+1] = cards[j];
            j--;
        }
        cards[j+1] = key; 
    }
}