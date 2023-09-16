#include "Player.h"

class PlayerList {
    public:
    PlayerList();
    ~PlayerList();
    bool empty();
    Player& front();
    Player& back();
    void advance();
    void add(const Name& name);
    void remove();
    Player* removePlayer(Player* player);
    int size();

    private:
    Player* cursor;

};

