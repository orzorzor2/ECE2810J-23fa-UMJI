#include "player.h"


static bool reimpleDraw(Card dealer, const Hand &player) {
    HandValue curvalue = player.handValue();

    if (!curvalue.soft) {
        if (curvalue.count <= 11) {
            return true;
        } else if (curvalue.count == 12) {
            return dealer.spot < FOUR || dealer.spot > SIX;
        } else if (curvalue.count >= 13 && curvalue.count <= 16) {
            return dealer.spot < TWO || dealer.spot > SIX;
        } else { // curvalue.count >= 17
            return false;
        }
    } else {
        if (curvalue.count <= 17) {
            return true;
        } else if (curvalue.count == 18) {
            return dealer.spot != TWO && dealer.spot != SEVEN && dealer.spot != EIGHT;
        } else { // curvalue.count >= 19
            return false;
        }
    }
}

class SimplePlayer : public Player {


     int bet(unsigned int bankroll, unsigned int minimum) override {
        return static_cast<int>(minimum);
    }


    bool draw(Card dealer, const Hand &player) override {
        return reimpleDraw(dealer, player);
    }


    void expose(Card card)
    override {

    }

    void shuffled()
    override {

    }
};

class CountingPlayer : public Player {

    int count;

public:
    int bet(unsigned int bankroll, unsigned int minimum) override {
        if (count >= 2 && bankroll >= 2 * minimum) {
            return static_cast<int>(2 * minimum);
        }
        else{
            return static_cast<int>(minimum);
        }
    }


    bool draw(Card dealer, const Hand &player) override {
        return reimpleDraw(dealer, player);
    }

    void expose(Card c) override {
        if (c.spot <= ACE && c.spot >= TEN) {
            count -= 1;
        } else if (c.spot >= TWO && c.spot <= SIX) {
            count += 1;
        }
    }

    void shuffled() override {
        this->count = 0;
    }
};


static SimplePlayer simplePlayer;
static CountingPlayer countingPlayer;

extern Player *get_Simple() {
    return &simplePlayer;
}

extern Player *get_Counting() {
    return &countingPlayer;
}

//Player *get_Simple()
//{
//    return (Player*) new SimplePlayer();
//}
//
//Player *get_Counting()
//{
//    return (Player*) new CountingPlayer();
//}