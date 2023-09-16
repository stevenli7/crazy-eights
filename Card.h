class Card {
    public:
    Card(char r, char s);
    char& getSuit();
    char& getRank();
    int& getValue();
    void setValue(int v);

    private:
    char suit;
    char rank;
    int value;
};


