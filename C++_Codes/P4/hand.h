#ifndef __HAND_H__
#define __HAND_H__

#include "card.h"

struct HandValue {
    int  count;    // Value of hand`
    bool soft;     // true if hand value is a soft count
};

class Hand {
    // OVERVIEW: A blackjack hand of zero or more cards
    // Note: this really is the only private state you need!
    HandValue curValue;
 public:
    Hand(); 
    // EFFECTS: establishes an empty blackjack hand.
    
    void discardAll();
    // MODIFIES: this
    // EFFECTS: discards any cards presently held, restoring the state
    // of the hand to that of an empty blackjack hand.

    void addCard(Card c);
    // MODIFIES: this
    // EFFECTS: adds the card "c" to those presently held.

    HandValue handValue() const; //这里要返回2个信息
    //为什么这里要搞这么一个函数，它设置成了const，实现只有一行return就结束了，原因就是
    //curvalue 是私有成员变量，在player.cpp中调用时不能直接访问的，需要一个公有的函数
    //handValue!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // EFFECTS: returns the present value of the blackjack hand.  The
    // count field is the highest blackjack total possible without
    // going over 21.  The soft field should be true if and only if at
    // least one ACE is present, and its value is counted as 11 rather
    // than 1.  If the hand is over 21, any value over 21 may be returned.
    //
    // Note: the const qualifier at the end of handValue means that
    // you are not allowed to change any member variables inside
    // handValue. Adding this prevents any accidental change by you.
};

#endif /* __HAND_H__ */
