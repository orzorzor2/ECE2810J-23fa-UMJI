#include "hand.h"

Hand::Hand() {
    this->discardAll();
}

void Hand::discardAll() {
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::addCard(Card card) {

    switch (card.spot) {
        case (JACK):
            this->curValue.count += 10;
            break;
        case (QUEEN) :
            this->curValue.count += 10;
            break;
        case (KING) :
            this->curValue.count += 10;
            break;
        case (ACE) :
            if (this->curValue.soft || this->curValue.count >= 21) {
                this->curValue.count += 1;
            } else {
                this->curValue.count += 11;
                this->curValue.soft = true;
            }
            break;
        default:
            this->curValue.count += (card.spot + 2);
            break;
    }
    if (this->curValue.count > 21 && this->curValue.soft){
        this->curValue.count -= 10;
        this->curValue.soft = false;
    }
}

//cannot change, so I have to do the judge and finalize in addCard function
HandValue Hand::handValue() const {
    return this->curValue;
}



