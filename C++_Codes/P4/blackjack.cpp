#include <iostream>
#include "rand.h"
#include "player.h"
#include "deck.h"

using namespace std;

//cause type of player will affect the shuffled() in the shuffle process, a function is needed
//deck need to be changed here
void shuffle(Player *player, Deck &deck) {
    cout << "Shuffling the deck\n";
    player->shuffled();
    for (int i = 0; i < 7; ++i) {
        int cut = get_cut();
        cout << "cut at " << cut << endl;
        deck.shuffle(cut);
    }

}

Card dealCard(Deck &deck, Hand &hand, Player *player, bool isPlayerTurn, bool isCardExposed) {
    Card card = deck.deal();
    hand.addCard(card);
    if(isCardExposed) {
        player->expose(card);
        if(isPlayerTurn) cout << "Player dealt " << string(SpotNames[card.spot]) << " of "
                                   << string(SuitNames[card.suit]) << endl;
        else if(!isPlayerTurn) cout << "Dealer dealt " << string(SpotNames[card.spot]) << " of "
                                        << string(SuitNames[card.suit]) << endl;
    }
    return card;
}


int main(int argc, char *argv[]) {
    unsigned int bankroll = static_cast<unsigned int>(stoi(argv[1]));
    int handNum = atoi(argv[2]);
    string playerType = argv[3];
    Deck deck;
    Player *player; //because Player is abstract class

    if (playerType == "simple") {
        player = get_Simple();
    } else {
        player = get_Counting();
    }

    //till now, the player has a particular type
    shuffle(player, deck);
    Hand dealerHand, playerHand;
    int thishand = 1;
    //now start the game loop
    while (bankroll >= 5 && thishand <= handNum) {
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        //check whether reshuffle is needed at the beginning !!!
        if (deck.cardsLeft() < 20) {
            shuffle(player, deck);

        }

        int wager = player->bet(bankroll, 5);
        cout << "Player bets " << wager << endl;
        //discard can be put at last
        dealerHand.discardAll();
        playerHand.discardAll();

        thishand += 1;



        dealCard(deck, playerHand, player, true, true ); // 发给玩家的牌，展示牌面
        Card upCard = dealCard(deck, dealerHand, player, false, true); // 发给庄家的牌，展示牌面
        dealCard(deck, playerHand, player, true, true); // 再次发给玩家的牌，展示牌面
        Card holeCard = dealCard(deck, dealerHand, player, false, false ); // 发给庄家的隐藏牌
        if (playerHand.handValue().count == 21) {
            bankroll += int(3 * wager) / 2;
            cout << "Player dealt natural 21\n";
        } else {
            while (player->draw(upCard, playerHand)) {                     //最大的bug在这里maad
                dealCard(deck, playerHand, player, true, true);
            }
            int player_count = playerHand.handValue().count;
            cout << "Player's total is " << player_count << endl;
            if (player_count > 21) {
                bankroll -= wager;
                cout << "Player busts\n";
            } else {
                player->expose(holeCard);
                cout << "Dealer's hole card is " << SpotNames[holeCard.spot] << " of " << SuitNames[holeCard.suit]
                     << endl;
                int dealer_count = dealerHand.handValue().count;
                while (dealer_count < 17) {
                    dealCard(deck, dealerHand, player, false, true);
                    dealer_count = dealerHand.handValue().count;
                }

                cout << "Dealer's total is " << dealer_count << endl;
                if (dealer_count > 21) {
                    cout << "Dealer busts\n";
                    bankroll += wager;
                } else if (dealer_count > player_count) {
                    cout << "Dealer wins\n";
                    bankroll = bankroll - wager;
                } else if (dealer_count < player_count) {
                    cout << "Player wins\n";
                    bankroll = bankroll + wager;
                } else if (dealer_count == player_count) {
                    cout << "Push\n";
                }
            }
        }
    }
    cout << "Player has " << bankroll << " after " << thishand - 1 << " hands\n";
    delete player;
    return 0;
}