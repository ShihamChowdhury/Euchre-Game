#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
TEST(test_player_get_name_2) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    ASSERT_NOT_EQUAL("  Alice  ", alice->get_name());

    delete alice;
}

TEST(test_player_output) {
    Player * alice = Player_factory("Alice", "Simple");
    ostringstream os;
    os << *alice;
    ASSERT_EQUAL(os.str(), "Alice");
    ASSERT_NOT_EQUAL(os.str(), " alice ");

    delete alice;
}

// TEST(test_player_add_card) {
//   Player * bob = Player_factory("Bob", "Simple");
//   bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
//   bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
//   ASSERT_EQUAL()

// TEST(test_player_add_card) {
//   Player * alice = Player_factory("Alice", "Simple");
//   Card c(Card::RANK_TEN, Card::SUIT_HEARTS);
//   alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
//   ASSERT_EQUAL(Card c, (Card::RANK_TEN Card::SUIT_HEARTS));
// }  

TEST(test_player_make_trump) {
  Player * bobo = Player_factory("Bobo", "Simple");
  bobo->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bobo->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bobo->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bobo->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bobo->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  string trump;
  bool orderup = bobo->make_trump(
    queen_diamonds,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
  ASSERT_NOT_EQUAL(trump, Card::SUIT_CLUBS);
  orderup = bobo->make_trump(Card(Card::RANK_NINE, Card::SUIT_SPADES), true, 1,trump);
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
  delete bobo;
}

TEST(test_player_make_trump_2) {
  Player * bobo = Player_factory("Bobo", "Simple");
  bobo->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bobo->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bobo->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bobo->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bobo->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  string trump;
  bool orderup = bobo->make_trump(
    queen_diamonds,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);

  Card jackHearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  orderup = bobo->make_trump(
    jackHearts,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  ASSERT_FALSE(orderup);

  Card jackClub(Card::RANK_JACK, Card::SUIT_CLUBS);
  orderup = bobo->make_trump(
    jackClub,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  ASSERT_FALSE(orderup);

  delete bobo;
}

TEST(test_player_make_trump_3) {
    Player * dan = Player_factory("Dan", "Simple");
  dan->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  dan->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  dan->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  dan->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  dan->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Dan makes tump
  Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
  string trump;
  bool orderup = dan->make_trump(
    jack_spades,    // Upcard
    false,           // Dan is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
  );

  // Verify Dan's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_NOT_EQUAL(trump, Card::SUIT_SPADES);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  orderup = dan->make_trump(
    jack_hearts,    // Upcard
    true,           // Dan is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
  
  Player * bob = Player_factory("Dan", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  orderup = bob->make_trump(
    ace_diamonds, //upcard
    false, // is dealer
    2, //round 
    trump //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,Card::SUIT_HEARTS);

  delete dan;
  delete bob;
}

TEST(test_player_add_discard) {
  Player * Anupam = Player_factory("Anupam", "Simple");
  Anupam->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  Anupam->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  Anupam->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));

  Anupam->add_and_discard(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  Card led = Anupam->lead_card(Card::SUIT_CLUBS);

  Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
  
  ASSERT_EQUAL(led, ten_spades);
  ASSERT_NOT_EQUAL(led, nine_diamonds);
  ASSERT_NOT_EQUAL(led, jack_clubs);

  //They now have jack clubs, queen clubs and ten clubs
  Anupam->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  //get rid of ten
  Anupam->add_and_discard(Card(Card::RANK_SEVEN, Card::SUIT_SPADES));
  //now they have jack clubs, queen clubs and seven spades

  //get rid of queen
  Anupam->add_and_discard(Card(Card::RANK_TEN, Card::SUIT_SPADES));

  //now they have jack clubs, ten spades, seven spades.
  led = Anupam->lead_card(Card::SUIT_SPADES);

  ASSERT_EQUAL(led.get_rank(), Card::RANK_JACK);

delete Anupam;
}

TEST(test_play_card) {
Player * ann = Player_factory("Bob", "Simple");
  ann->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  ann->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  ann->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  ann->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  ann->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  Card led(Card::RANK_ACE , Card::SUIT_CLUBS);
  string trump = Card::SUIT_SPADES;
  Card playedCard;
  playedCard = ann->play_card(led, trump);
  ASSERT_EQUAL(playedCard.get_rank(), Card::RANK_NINE);

  led = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  playedCard = ann->play_card(led, trump);
  ASSERT_EQUAL(Card::RANK_JACK, playedCard.get_rank());
  ASSERT_NOT_EQUAL(Card::RANK_ACE, playedCard.get_rank());
  ASSERT_NOT_EQUAL(Card::RANK_NINE, playedCard.get_rank());

  playedCard = ann->play_card(led, trump);
  ASSERT_EQUAL(Card::RANK_ACE, playedCard.get_rank());
  
  led = Card(Card::RANK_ACE , Card::SUIT_CLUBS);
  ann->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  playedCard = ann->play_card(led, trump);
  ASSERT_NOT_EQUAL(Card::RANK_JACK, playedCard.get_rank());
  ASSERT_EQUAL(Card::RANK_TEN, playedCard.get_rank());


delete ann;
}



TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TWO, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

  string trump = Card::SUIT_HEARTS;
  // Bob leads
  Card card_led = bob->lead_card(trump);

  // Verify the card Bob selected to lead
  Card twoHearts(Card::RANK_TWO, Card::SUIT_HEARTS);
  Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, king_spades);
  ASSERT_NOT_EQUAL(card_led, twoHearts); //check led card

  trump = Card::SUIT_CLUBS;
  card_led = bob->lead_card(trump);
  ASSERT_EQUAL(Card::RANK_TEN, card_led.get_rank());
  delete bob;

}

TEST_MAIN()