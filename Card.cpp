// Project UID 1d9f47bfc76643019cfbf037641defe1


#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

//EFFECTS Initializes Card to the Two of Spades
  Card::Card() {
  Card::rank = RANK_TWO;
  Card::suit = SUIT_SPADES;
  }

  //REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
  //  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
  //  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
  //EFFECTS Initializes Card to specified rank and suit
  Card::Card(const std::string &rank_in, const std::string &suit_in){
    if(rank_in == RANK_TWO || RANK_THREE || RANK_FOUR || RANK_FIVE || 
                  RANK_SIX || RANK_SEVEN || RANK_EIGHT || RANK_NINE ||
                  RANK_TEN || RANK_JACK || RANK_QUEEN || RANK_KING || RANK_ACE){
                if(suit_in == SUIT_SPADES || SUIT_HEARTS ||
                              SUIT_CLUBS || SUIT_DIAMONDS) {
            Card::rank = rank_in;
            Card::suit = suit_in;
        }
    }
  }

  //EFFECTS Returns the rank
  std::string Card::get_rank() const {
    return Card::rank;
  }

  //EFFECTS Returns the suit.  Does not consider trump.
  std::string Card::get_suit() const{
    return Card::suit;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  std::string Card::get_suit(const std::string &trump) const{
    if(Card::get_rank() == RANK_JACK && Card::is_left_bower(trump) == true){
      return trump;
    }
    else {
      return Card::get_suit();
    }
  }

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool Card::is_face_or_ace() const{
    if (Card::get_rank() == RANK_JACK || Card::get_rank() == RANK_QUEEN ||
    Card::get_rank() == RANK_KING || Card::get_rank() == RANK_ACE) {
      return true;
    }
    else {
      return false;
    }
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(const std::string &trump) const{
    if (Card::get_rank() == RANK_JACK && Card::get_suit() == trump){
        return true;
      }
    else {
      return false;
    }
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
  bool Card::is_left_bower(const std::string &trump) const{
    if(Card::get_rank() == RANK_JACK && Card::get_suit() == Suit_next(trump)){
      return true;
    }
    else {
      return false;
    }
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool Card::is_trump(const std::string &trump) const{
    if(Card::get_suit() == trump || Card::is_left_bower(trump) == true){
      return true;
    } 
    else {
      return false;
    }
  }

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

static int getRank(const Card &Card){
  for (int i = 0; i < NUM_RANKS; i++)
  {
    if(Card.get_rank() == RANK_NAMES_BY_WEIGHT[i]){
      return i;
    }
  }
  return 0;
}

static int getSuit(const Card &Card){
  for (int i = 0; i < NUM_SUITS; i++)
  {
    if(Card.get_suit() == SUIT_NAMES_BY_WEIGHT[i]){
      return i;
    }
  }
  return 0;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
   if (getRank(lhs) > getRank(rhs))
   {
     return false;
   }
   else if (getRank(lhs) < getRank(rhs))
   {
     return true;
   }
   else {
     return (getSuit(lhs) < getSuit(rhs));
   }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
  if (operator<(lhs, rhs) == true || operator==(lhs, rhs) == true)
  {
    return true;
  }
  else {
    return false;
  }
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
  if(operator<=(lhs, rhs) == false) {
     return true;
  }
  else {
    return false;
  }
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
  if (operator>(lhs, rhs) == true || operator==(lhs, rhs) == true)
  {
    return true;
  }
  else {
    return false;
  }
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
  if (getRank(lhs) == getRank(rhs) && getSuit(lhs) == getSuit(rhs))
  {
    return true;
  }
  else {
    return false;
  }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
  return !(operator==(lhs, rhs));
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
  if(suit == Card::SUIT_SPADES) {
    return Card::SUIT_CLUBS;
  }
  if(suit == Card::SUIT_CLUBS) {
    return Card::SUIT_SPADES;
  }
  if(suit == Card::SUIT_HEARTS) {
    return Card::SUIT_DIAMONDS;
  }
  else {
    return Card::SUIT_HEARTS;
  }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

bool bower_and_trump_check(const Card &a, const Card &b, 
const std::string &trump){
  if (a.is_right_bower(trump) == true){
    return false;
  }
  else if (b.is_right_bower(trump) == true){
    return true; 
  }
  else if (a.is_left_bower(trump) == true){
    return false;
  }
  else if (b.is_left_bower(trump) == true){
    return true;
  }
  else if(a.is_trump(trump) == true && b.is_trump(trump) == true){
    return (getRank(a) < getRank(b));
  }
  else if(a.get_suit() == trump && b.get_suit() != trump){
    return false;
  }
  else if(b.get_suit() == trump && a.get_suit() != trump){
    return true;
  }
  return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
  if(a.is_trump(trump) == true || b.is_trump(trump) == true){
    return bower_and_trump_check(a, b, trump);
  }
  else {
    return a < b;
  }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
  if(a.is_trump(trump) == true || b.is_trump(trump) == true){
    return bower_and_trump_check(a, b, trump);
  }
  else if(a.get_suit(trump) == led_card.get_suit(trump) && 
  (b.get_suit(trump) != led_card.get_suit(trump) && b.get_suit(trump) != trump)){
    return false;
  }
  else if(b.get_suit(trump) == led_card.get_suit(trump) && 
  (a.get_suit(trump) != led_card.get_suit(trump) && a.get_suit(trump) != trump)){
    return true;
  }
  else {
    return a < b;
  }
  }
