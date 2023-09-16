#include <iostream>
#include "Player.h"

void Player::insert(Card* card) {
    cards.insertAtBack(card);
}

int Player::findCard(char rank, char suit) {
    bool found = false;
    int i = 0;
    while (i < size() && !found) {
        if (cards.at(i)->getRank() == rank && cards.at(i)->getSuit() == suit) {
            found = true;
        } else {
            i++;
        }
    }
    if (!found) {
        return -1;
    }
    return i;
}

Card* Player::remove(Card* card) {
    int index = findCard(card->getRank(), card->getSuit());
    if (index == -1) {
        return NULL;
    }
    return cards.erase(index);
}

Card* Player::removeAtBack() {
    return cards.removeAtBack();
}

int Player::size() {
    return cards.size();
}

Card* Player::checkValidMove(string input, char newSuit, Card* topCard, bool firstMove) {
    int index = findCard(input.at(0), input.at(1));
    Card* toPlay = cards.at(index);

    // returns NULL if the move is invalid, otherwise returns the card being played
    if (toPlay->getRank() != topCard->getRank()) {
        if (topCard->getRank() == '8') {
            if (toPlay->getSuit() == newSuit) {
                return toPlay;
            } else {
                return NULL;
            }
        }
        if (!firstMove) {
            return NULL;
        } else if (toPlay->getRank() != '8' && toPlay->getSuit() != topCard->getSuit()) {
            return NULL;
        }          
    }
    return toPlay;
}

bool Player::canPlayCard(Card* topCard, char newSuit, bool firstMove) {
    for (int i = 0; i < cards.size(); i++) {
        if (firstMove) {
            if (topCard->getRank() == '8' && cards.at(i)->getSuit() == newSuit) {
                return true;
            }
            if (cards.at(i)->getRank() == '8') {
                return true;
            }
            if (cards.at(i)->getSuit() == topCard->getSuit() && topCard->getRank() != '8') {
                return true;
            }
        }
        if (cards.at(i)->getRank() == topCard->getRank()) {
            return true;
        }
    }
    return false;
}

bool Player::checkValidInput(string input, bool firstMove, bool inputSuit) {
    if (input.length() == 1) {
        if (inputSuit) {
            string suits[] = {"s", "h", "c", "d"};
            for (size_t i = 0; i < sizeof(suits)/sizeof(suits[0]); i++) {
                if (suits[i] == input) {
                    return true;
                }
            }
        } else if (input == "e") {
            if (firstMove) {
                cout << "You must play a card or draw before ending your turn." << endl;
                return false;
            }
            return true;
        } else if (input == "d") {
            return true;
        }
    } else if (input.length() == 2) {
        int index = findCard(input.at(0), input.at(1));
        if (index != -1) {
            return true;
        }
    }
    cout << "Invalid input." << endl;
    return false;
}

bool Player::winner() {
    return size() == 0;
}

void Player::sortHand() {
    cards.sortDeck(size());
}

void Player::printHand() {
    cards.printDeck();
}