// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include <string>
#include <vector>
#include <array>
#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

class SimplePlayer : public Player {
  private:
  string simplename;
  std::vector<Card> simplecards;

  //Constructor for SimplePlayer
  public:
  SimplePlayer(string nameinput) {
    simplename = nameinput;
  }

  //EFFECTS returns player's name
  const std::string & get_name() const {
    return simplename;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c){
    assert(simplecards.size() < MAX_HAND_SIZE);
    simplecards.push_back(c);
    std::sort(simplecards.begin(),simplecards.end());
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const {
   assert(round == 1 || round == 2);
   if(round == 1){
     int numgoodcards = 0;
     for(int i = 0; i < simplecards.size(); i++){
        if(simplecards[i].is_face_or_ace() == true && 
        simplecards[i].is_trump(upcard.get_suit())){
            numgoodcards++;
        }
     }
     if(numgoodcards >= 2){
        order_up_suit = upcard.get_suit();
        cout << simplename << " orders up " << order_up_suit << endl << endl; 
        return true; 
     }
     cout << simplename << " passes" << endl;
     return false;
   }
   if(round == 2){
     int numgoodcards = 0;
     for(int i = 0; i < simplecards.size(); i++){
         if(simplecards[i].is_face_or_ace() == true && 
         simplecards[i].is_trump(Suit_next(upcard.get_suit()))){
            numgoodcards++;
        }
     }
     if(is_dealer == true){
        order_up_suit = Suit_next(upcard.get_suit());
        cout << simplename << " orders up " << order_up_suit << endl << endl;
        return true;
     }
     else if(numgoodcards >= 1){
          order_up_suit = Suit_next(upcard.get_suit());
          cout << simplename << " orders up " << order_up_suit << endl << endl;
          return true;
     }
     cout << simplename << " passes" << endl;
     return false;
     }
     return false;
     }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) {
     assert(simplecards.size() >= 1);
     Card lowestcard = simplecards[0];
     int index = 0;
     for(int x = 1; x < simplecards.size(); x++){
           if(Card_less(simplecards[x],lowestcard,upcard.get_suit()) == true){
             lowestcard = simplecards[x];
             index = x;
           }
        }
    if(Card_less(lowestcard, upcard, upcard.get_suit()) == true){
       simplecards.erase(simplecards.begin() + index);
       simplecards.push_back(upcard);
    }
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump) {
    assert(simplecards.size() >= 1);
    int trumpcount = 0;
    int index = 0;
    int nontrump = 0;
    bool condition = false;
    Card leadcard;
    for(int i = 0; i < simplecards.size(); i++){
       if( simplecards[i].is_trump(trump) == true){
         trumpcount++;
       }
       else if(condition == false){
            nontrump = i;
            condition = true;
       }
    }
    if((unsigned) trumpcount == simplecards.size()){
        index = 0;
        for(int i = 1; i < simplecards.size(); i++){
          if(Card_less(simplecards[index],simplecards[i],trump) == true){
              index = i;
         }
        }
        leadcard = simplecards[index];
        simplecards.erase(simplecards.begin() + index);
        return leadcard;
    }
    else{
        index = nontrump;
        for(int i = 0; i < simplecards.size(); i++){
          if(Card_less(simplecards[index],simplecards[i],trump) == true 
          && simplecards[i].is_trump(trump) == false){
              index = i;
         }
        }
        leadcard = simplecards[index];
        simplecards.erase(simplecards.begin() + index);
        return leadcard;
    }
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const std::string &trump) {
    assert(simplecards.size() >= 1);
    int leadcount = 0;
    int index;
    int suitindex = 0;
    bool condition = false;
    Card playcard;
    string suit = led_card.get_suit(trump);
    for(int i = 0; i < simplecards.size(); i++){
        if(simplecards[i].get_suit(trump) == suit){
          leadcount++;
          if(condition == false){
             suitindex = i;
             condition = true; 
          }
        }
        
    }
    if(leadcount > 0){
      index = suitindex;
       for(int i = 0; i < simplecards.size(); i++){
          if((Card_less(simplecards[index], simplecards[i], led_card, trump)
           == true) && (simplecards[i].get_suit(trump) == suit)){
              index = i;
          }
        }
       playcard = simplecards[index];
       simplecards.erase(simplecards.begin() + index);
       return playcard;
    }
    else {
       index = 0;
       for(int i = 1; i < simplecards.size(); i++){
          if(Card_less(simplecards[index],simplecards[i],led_card, trump) == false){
              index = i;
         }
        }
        playcard = simplecards[index];
        simplecards.erase(simplecards.begin() + index);
        return playcard;
    }
}
};

class HumanPlayer : public Player {
  private:
  string humanname;
  std::vector<Card> humancards;
  void print_hand() const {
    for (int i = 0; i < humancards.size(); i++)
    {
        cout << "Human player " << humanname << "'s hand: " 
             << "[" << i << "] " << humancards[i] << endl;
    } 
  }

  //Constructor for SimplePlayer
  public:
  HumanPlayer(string nameinput) {
    humanname = nameinput;
  }

  //EFFECTS returns player's name
  const std::string & get_name() const{
    return humanname;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c){
    assert(humancards.size() < MAX_HAND_SIZE);
    humancards.push_back(c);
    std::sort(humancards.begin(),humancards.end());
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const {
   assert(round == 1 || round == 2);
   string choice;
   print_hand();
   cout << "Human player " << humanname << ", please enter a suit, or \"pass\":" << endl;
   cin >> choice;
   if(choice == Card::SUIT_CLUBS || choice == Card::SUIT_DIAMONDS ||
   choice == Card::SUIT_HEARTS || choice == Card::SUIT_SPADES)
   {
      order_up_suit = choice;
      cout << humanname << " orders up " << order_up_suit << endl;
      if(round == 2){
         cout << endl;
      }
      return true;
   }
   else{
      cout << humanname << " passes" << endl;;
      return false;
   }
   }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) {
     assert(humancards.size() >= 1);
     int choice;
     print_hand();
     cout << "Discard upcard: [-1]" << endl;
     cout << "Human player " << humanname
      << ", please select a card to discard:" << endl << endl;
     cin >> choice;
     if (choice != -1)
     {
        humancards.erase(humancards.begin() + choice);
        add_card(upcard);
     }
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump) {
     assert(humancards.size() >= 1);
     int choice;
     print_hand();
     cout << "Human player " << humanname << ", please select a card:" << endl;
     cin >> choice;
     Card chosencard = humancards[choice];
     humancards.erase(humancards.begin() + choice);
     return chosencard;
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const std::string &trump) {
    assert(humancards.size() >= 1);
    int choice;
    print_hand();
    cout << "Human player " << humanname << ", please select a card:" << endl;
    cin >> choice;
    Card chosencard = humancards[choice];
    humancards.erase(humancards.begin() + choice);
    return chosencard;
}
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){
   if(strategy == "Simple") {
      return new SimplePlayer(name);
   }
   else {
      return new HumanPlayer(name);
   }
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}

