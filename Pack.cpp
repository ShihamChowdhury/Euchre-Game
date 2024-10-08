// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include <array>
#include <string>
#include <cassert>
#include <iostream>
#include "Pack.h"
using namespace std;

  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack() {
      for (int suit = 0; suit < 4; suit++) 
      {
         for (int rank = 0; rank < 6; rank++) {
            cards[suit*6 + rank] = Card(RANK_NAMES_BY_WEIGHT[rank + 7],
             SUIT_NAMES_BY_WEIGHT[suit]);
         }
      }
      next = 0;
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input){
     for (int card = 0; card < cards.size(); card++) 
      {
        string rank = "";
        string of = "";
        string suit = "";
        pack_input >> rank;
        pack_input >> of;
        pack_input >> suit;
        cards[card] = Card(rank, suit);
      }
      next = 0;
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    assert(Pack::empty() == false);
    next++;
    return cards[next-1];
  }
  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
     next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
      std::array<Card,PACK_SIZE> pack;
      for (int shuffle = 0; shuffle < 7; shuffle++)
      {
        pack = cards; 
        int iterator = 0;
        for(int i = 0; i < 24; i+=2) {
            cards[i] = pack[12 + iterator];
            cards[i+1] = pack[iterator]; 
            iterator++;
        }
      }
      reset();  
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
       if(next == cards.size()){
        return true;
       }
       return false;
  }