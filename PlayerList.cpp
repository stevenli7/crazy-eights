#include <iostream>
#include "PlayerList.h"

PlayerList::PlayerList() {
    cursor = NULL;
}

PlayerList::~PlayerList() {
    while (!empty()) {
        remove();
    }
}

bool PlayerList::empty() {
    return cursor == NULL;
}

Player& PlayerList::front() {
    return *cursor->nextPlayer;
}

Player& PlayerList::back() {
    return *cursor;
}

void PlayerList::advance() {
    cursor = cursor->nextPlayer;
}

void PlayerList::add(const Name& name) {
    // add after cursor, and set cursor to the new element
    Player* newPlayer = new Player;
    newPlayer->name = name;
    if (cursor == NULL) {
        newPlayer->nextPlayer = newPlayer;
        cursor = newPlayer;
    } else {
        newPlayer->nextPlayer = cursor->nextPlayer;
        cursor->nextPlayer = newPlayer;
        advance();
    }
    
}

void PlayerList::remove() {
    // remove element after the cursor
    if (empty()) {
        return;
    }
    Player* temp = cursor->nextPlayer;
    if (temp == cursor) {
        cursor = NULL;
    } else {
        cursor->nextPlayer = temp->nextPlayer;
    }
    delete temp;
}

Player* PlayerList::removePlayer(Player* player) {
    if (empty()) {
        return NULL;
    }
    if (cursor == cursor->nextPlayer) { 
        // size 1
        cursor = NULL;
        return cursor;
    }
    bool found = false;
    Player* current = cursor;
    Player* temp = current;
    do {
       if (current->nextPlayer == player) { 
            temp = current->nextPlayer;
            current->nextPlayer = temp->nextPlayer;
            if (temp == cursor) {
                cursor = current;
            }
            found = true;
        } else {
            current = current->nextPlayer;
        }
    } while (!found && current != cursor);
    
    if (!found) {
        return NULL;
    }
    delete temp;
    // returns element before the removed player
    return current; 
}

int PlayerList::size() {
    if (empty()) {
        return 0;
    }
    Player* current = cursor->nextPlayer;
    int num = 0;
    do {
        num++;
        current = current->nextPlayer;
    } while (current != cursor->nextPlayer);
    return num; 
}