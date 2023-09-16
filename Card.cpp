#include "Card.h"

Card::Card(char r, char s) {
    rank = r;
    suit = s;
}

char& Card::getSuit() {
    return suit;
}

char& Card::getRank() {
    return rank;
}

int& Card::getValue() {
    return value;
}

void Card::setValue(int v) {
    value = v;
}

