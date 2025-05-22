#include "deck.h"


Deck::Deck() {
    this->reset();
}

void Deck::reset() {
    for (int i = 0; i <= DIAMONDS; i++) {
        for (int j = 0; j <= ACE; j++) {
            this->deck[13 * i + j].spot = Spot(j);
            this->deck[13 * i + j].suit = Suit(i);
        }
    }
    this->next = 0;
}

void Deck::shuffle(int n) {
    int lNum = n;
    int rNum = DeckSize - n;
    Card left[lNum];
    Card right[rNum];
    for (int i = 0; i < lNum; ++i) {
        left[i] = this->deck[i];
    }
    for (int i = 0; i < rNum; ++i) {
        right[i] = this->deck[lNum + i];
    }
    if (n >= DeckSize / 2) { //左边堆比较多
        for (int j = 0; j < rNum; ++j) {
            this->deck[2 * j] = right[j];
            this->deck[2 * j + 1] = left[j];
        }
        for (int j = 0; j < DeckSize - 2 * rNum; ++j) {
            this->deck[2 * rNum + j] = left[rNum + j];
        }
    } else { //右边堆比较多
        for (int j = 0; j < lNum; ++j) {
            this->deck[2 * j] = right[j];
            this->deck[2 * j + 1] = left[j];
        }
        for (int j = 0; j < DeckSize - 2 * lNum; ++j) {
            this->deck[2 * lNum + j] = right[lNum + j];
        }
    }
    this->next = 0;
}

Card Deck::deal() {
    if (this->next < DeckSize) {
        return this->deck[next++];
    }
    throw DeckEmpty();

}


int Deck::cardsLeft() {
    return DeckSize - this->next;
}