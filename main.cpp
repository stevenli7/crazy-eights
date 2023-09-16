#include <iostream>
#include "PlayerList.h"

using namespace std;

int main() {
    //init players
    PlayerList players; 
    int numOfPlayers = 0;
    PlayerList winners;
    bool keepPlaying = false;

    do {
        cout << "How many players?" << endl;
        cin >> numOfPlayers;
    } while (numOfPlayers < 2 || numOfPlayers > 7);

    string input = "";
    if (numOfPlayers > 2) {
        do {
            cout << "Continue playing if a player has already won? (y/n)" << endl;
            cin >> input;
        } while (input != "y" && input != "n");
        if (input == "y") {
            keepPlaying = true;
        }
    }

    for (int i = 0; i < numOfPlayers; i++) {
        cout << "Enter name for player " << i+1 << ":" << endl;
        cin >> input;
        players.add(input);
    }

    Player* currentPlayer = &players.front();

    // init deck
    Deck myDeck;
    bool sortBySuit = true;
    do {
        cout << "Sort hand by rank or by suit? (r/s)" << endl;
        cin >> input;
    } while (input != "r" && input != "s");
    if (input == "r") {
        sortBySuit = false;
    }
    char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char suits[] = {'s','h','c','d'};
    for (size_t i = 0; i < sizeof(suits)/sizeof(suits[0]); i++) {
        for (size_t j = 0; j < sizeof(ranks)/sizeof(ranks[0]); j++) {
            Card* newCard = new Card(ranks[j], suits[i]);
            if (sortBySuit) {
                newCard->setValue(i);
            } else {
                newCard->setValue(j);
            }
            myDeck.insertAtBack(newCard);
        }   
    }
    myDeck.shuffleDeck(myDeck.size());

    // deal
    int numOfCards = 5;
    if (numOfPlayers == 2) {
        numOfCards = 7;
    }

    for (int i = 0; i < numOfCards; i++) {
        do {
            currentPlayer->insert(myDeck.removeAtBack());
            currentPlayer = currentPlayer->nextPlayer;
        } while (currentPlayer != &players.front());
    }

    // select starting card
    Card* startingCard = myDeck.removeAtBack();
    while (startingCard->getRank() == '8') {
        myDeck.insertAtBack(startingCard);
        myDeck.shuffleDeck(myDeck.size());
        startingCard = myDeck.removeAtBack();
    }

    Card* topCard = startingCard;
    Deck playedCards;

    // begin game
    bool gameOver = false;
    do {
        bool endTurn = false;
        bool firstMove = true;
        bool inputSuit = false;
        Card* lastCardPlayed = NULL;
        char newSuit;
        string play;

        cout << currentPlayer->name << "'s turn." << endl;
        do {
            do {
                currentPlayer->sortHand();
                cout << "Top card: " << topCard->getRank() << topCard->getSuit() << endl;
                cout << "Your cards:" << endl;
                currentPlayer->printHand();
                cout << endl;
                if (!inputSuit) {
                    if (lastCardPlayed == NULL) {
                        if (currentPlayer->canPlayCard(topCard, newSuit, firstMove)) {
                            if (myDeck.empty() && playedCards.empty()) {
                                cout << "Play a card of the same suit or of the same rank."<< endl;
                            } else {
                                cout << "Play a card of the same suit or of the same rank, or draw from the pile (d)." << endl;
                            }
                        } else {
                            cout << "Enter d to draw a card from the pile." << endl;
                        }
                    } else {
                        cout << "Play cards of the same rank. Enter e to end turn." << endl;
                    }
                } else {
                    if (currentPlayer->canPlayCard(topCard, newSuit, firstMove)) {
                        cout << "Play another card of rank 8, or enter a suit (s, h, c, d) to end your turn." << endl;
                    } else {
                        cout << "Enter a suit (s, h, c, d) to end your turn." << endl; 
                    }
                }
                cin >> play;
            } while (!currentPlayer->checkValidInput(play, firstMove, inputSuit)); 
            // test cases with input length 1 first
            if (inputSuit && play.length() == 1) {
                newSuit = play.at(0);
                cout << "The suit has been changed to " << play << "." << endl;
                if (currentPlayer->winner()) {
                    cout << currentPlayer->name << " has played all their cards!" << endl;
                    winners.add(currentPlayer->name);
                    currentPlayer = players.removePlayer(currentPlayer); 
                }
                currentPlayer = currentPlayer->nextPlayer;
                endTurn = true;
            } else if (play == "e") {
                currentPlayer = currentPlayer->nextPlayer;
                endTurn = true;
            } else if (play == "d") {
                if (lastCardPlayed != NULL) {
                    cout << "You can't draw after playing a card!" << endl;
                } else if (myDeck.empty() && playedCards.empty()) { // no cards available to draw
                    if (currentPlayer->canPlayCard(topCard, newSuit, firstMove)) {
                        cout << "No cards can be drawn. You must play a card." << endl;
                    } else {
                        cout << "Mo cards can be drawn. You must pass your turn." << endl;
                        currentPlayer = currentPlayer->nextPlayer;
                        endTurn = true;
                    }
                } else if (myDeck.empty()) {
                    // if there are no cards in draw pile, reshuffle playedCards to form a new draw pile
                    playedCards.shuffleDeck(playedCards.size());
                    while (!playedCards.empty()) {
                        myDeck.insertAtBack(playedCards.removeAtBack());
                    }
                    Card* drawn = myDeck.removeAtBack();
                    currentPlayer->insert(drawn);
                    cout << "You drew " << drawn->getRank() << drawn->getSuit() << "." << endl;
                } else {
                    Card* drawn = myDeck.removeAtBack();
                    currentPlayer->insert(drawn);
                    cout << "You drew " << drawn->getRank() << drawn->getSuit() << "." << endl;
                }
            } else if (currentPlayer->checkValidMove(play, newSuit, topCard, firstMove) != NULL) { 
                Card* toPlay = currentPlayer->checkValidMove(play, newSuit, topCard, firstMove);
                firstMove = false;
                if (toPlay->getRank() == '8') { 
                    inputSuit = true; 
                }
                currentPlayer->remove(toPlay);
                playedCards.insertAtBack(topCard);
                topCard = toPlay;
                lastCardPlayed = toPlay;

                // check if player has 0 cards in hand
                if (currentPlayer->winner()) {
                    if (keepPlaying) {
                        if (topCard->getRank() != '8') {
                            cout << currentPlayer->name << " has played all their cards!" << endl;
                            winners.add(currentPlayer->name);
                            currentPlayer = players.removePlayer(currentPlayer);
                            if (players.size() == 1) {
                                winners.add(currentPlayer->name);
                                gameOver = true;
                            }
                            currentPlayer = currentPlayer->nextPlayer;
                            endTurn = true;
                        } else {
                            if (players.size() == 2) {
                                cout << currentPlayer->name << " has played all their cards!" << endl;
                                winners.add(currentPlayer->name);
                                currentPlayer = players.removePlayer(currentPlayer);
                                winners.add(currentPlayer->name);
                                endTurn = true;
                                gameOver = true;
                            }
                        }
                    } else {
                        cout << currentPlayer->name << " wins!" << endl;
                        endTurn = true;
                        gameOver = true;
                    }
                } else if (!currentPlayer->canPlayCard(topCard, newSuit, firstMove) && topCard->getRank() != '8') {
                    // if they can't play any more cards, end turn
                    currentPlayer = currentPlayer->nextPlayer;
                    endTurn = true;
                }
            } else {
                cout << "You can't play that card right now!" << endl;
            } 
        } while (!endTurn);
        cout << endl;
    } while (!gameOver);

    // delete cards
    while (!myDeck.empty()) {
        delete myDeck.removeAtBack();
    }
    while (!playedCards.empty()) {
        delete playedCards.removeAtBack();
    }
    while (currentPlayer->size() != 0) {
        delete currentPlayer->removeAtBack();
    }
    delete topCard;
    
    if (keepPlaying) {
        cout << "The game is over!" << endl;
        int i = 0;
        currentPlayer = &winners.front();
        do {
            cout << "#" << i+1 << ": " << currentPlayer->name << endl;
            currentPlayer = currentPlayer->nextPlayer;
            i++;
        } while (currentPlayer != &winners.front());
    }
    return 0;
}