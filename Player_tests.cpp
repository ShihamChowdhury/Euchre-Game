// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * amogus = Player_factory("amogus", "Simple");
    ASSERT_EQUAL("amogus", amogus->get_name());

    delete amogus;
}

// Add more tests here

TEST(test_add_card) {
    Player * amogus = Player_factory("Amogus", "Simple");
    std::string trump = Card::SUIT_CLUBS;
    Card ledcard = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    amogus->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(Card(Card::RANK_ACE,Card::SUIT_SPADES), amogus->lead_card(trump));
    delete amogus;
}

TEST(test_make_trump) {
    Player * amogus = Player_factory("Amogus", "Simple");
    amogus->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    amogus->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    amogus->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    amogus->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    amogus->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    std::string orderupsuit = upcard.get_suit();
    ASSERT_EQUAL(true, amogus->make_trump(upcard, false, 1, orderupsuit));
    ASSERT_EQUAL(true, amogus->make_trump(upcard, true, 1, orderupsuit));
    ASSERT_EQUAL(true, amogus->make_trump(upcard, false, 2, orderupsuit));
    ASSERT_EQUAL(true, amogus->make_trump(upcard, true, 2, orderupsuit));
    
    upcard = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    orderupsuit = upcard.get_suit();
    ASSERT_EQUAL(false, amogus->make_trump(upcard, false, 1, orderupsuit));
    ASSERT_EQUAL(false, amogus->make_trump(upcard, true, 1, orderupsuit));
    ASSERT_EQUAL(true, amogus->make_trump(upcard, false, 2, orderupsuit));
    ASSERT_EQUAL(true, amogus->make_trump(upcard, true, 2, orderupsuit));

    upcard = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    orderupsuit = upcard.get_suit();
    ASSERT_EQUAL(false, amogus->make_trump(upcard, false, 1, orderupsuit));
    ASSERT_EQUAL(false, amogus->make_trump(upcard, true, 1, orderupsuit));
    ASSERT_EQUAL(false, amogus->make_trump(upcard, false, 2, orderupsuit));
    ASSERT_EQUAL(true, amogus->make_trump(upcard, true, 2, orderupsuit));
    delete amogus;
}

TEST(test_add_and_discard) {
    Player * amogus = Player_factory("Amogus", "Simple");
    amogus->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    amogus->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    amogus->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    amogus->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    amogus->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card upcard = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    amogus->add_and_discard(upcard);
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_SPADES), 
    amogus->lead_card(upcard.get_suit()));
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_CLUBS), 
    amogus->lead_card(upcard.get_suit()));
    ASSERT_EQUAL(Card(Card::RANK_ACE, Card::SUIT_SPADES), 
    amogus->lead_card(upcard.get_suit()));
    ASSERT_EQUAL(Card(Card::RANK_QUEEN, Card::SUIT_SPADES), 
    amogus->lead_card(upcard.get_suit()));
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_SPADES), 
    amogus->lead_card(upcard.get_suit()));
    delete amogus;

    Player * agomus = Player_factory("Agomus", "Simple");
    agomus->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    agomus->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    agomus->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    agomus->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    agomus->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    upcard = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    agomus->add_and_discard(upcard);
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_SPADES),
     agomus->lead_card(upcard.get_suit()));
    ASSERT_EQUAL(Card(Card::RANK_ACE, Card::SUIT_SPADES), 
    agomus->lead_card(upcard.get_suit()));
    ASSERT_EQUAL(Card(Card::RANK_KING, Card::SUIT_SPADES), 
    agomus->lead_card(upcard.get_suit()));
    ASSERT_EQUAL(Card(Card::RANK_QUEEN, Card::SUIT_SPADES), 
    agomus->lead_card(upcard.get_suit()));
    ASSERT_EQUAL(Card(Card::RANK_TEN, Card::SUIT_SPADES),
    agomus->lead_card(upcard.get_suit()));
    delete agomus;
}

TEST(test_play_card) {
    Player * amogus = Player_factory("Amogus", "Simple");
    amogus->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    amogus->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    amogus->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    amogus->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    amogus->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card ledcard = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    std::string trump = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
    amogus->play_card(ledcard,trump));
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_SPADES), 
    amogus->play_card(ledcard,trump));
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_SPADES), 
    amogus->play_card(ledcard,trump));
    ASSERT_EQUAL(Card(Card::RANK_TEN, Card::SUIT_HEARTS), 
    amogus->play_card(ledcard,trump));
    ASSERT_EQUAL(Card(Card::RANK_TEN, Card::SUIT_CLUBS), 
    amogus->play_card(ledcard,trump));
    delete amogus;

    Player * agomus = Player_factory("Agomus", "Simple");
    agomus->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    agomus->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    agomus->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    agomus->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    agomus->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    ledcard = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    trump = Card::SUIT_CLUBS;
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_SPADES),
    agomus->play_card(ledcard,trump));
    ASSERT_EQUAL(Card(Card::RANK_TEN, Card::SUIT_CLUBS), 
    agomus->play_card(ledcard,trump));
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_SPADES), 
    agomus->play_card(ledcard,trump));
    ASSERT_EQUAL(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS), 
    agomus->play_card(ledcard,trump));
    ASSERT_EQUAL(Card(Card::RANK_QUEEN, Card::SUIT_SPADES), 
    agomus->play_card(ledcard,trump));
    delete agomus;
}

TEST_MAIN()
