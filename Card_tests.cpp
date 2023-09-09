// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here

TEST(test_card_rank_and_suit_with_trump) {
    Card a(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    std::string trump = Card::SUIT_CLUBS;
    ASSERT_EQUAL(Card::RANK_ACE, a.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, a.get_suit());
    ASSERT_EQUAL(Card::RANK_JACK, b.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, b.get_suit());
    ASSERT_EQUAL(Card::RANK_JACK, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    trump = Card::SUIT_HEARTS;
    ASSERT_EQUAL(Card::RANK_ACE, a.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, a.get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, a.get_suit(trump));
    ASSERT_EQUAL(Card::RANK_JACK, b.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, b.get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, b.get_suit(trump));
    ASSERT_EQUAL(Card::RANK_JACK, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit(trump));
    trump = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(Card::RANK_ACE, a.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, a.get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, a.get_suit(trump));
    ASSERT_EQUAL(Card::RANK_JACK, b.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, b.get_suit());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, b.get_suit(trump));
    ASSERT_EQUAL(Card::RANK_JACK, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit(trump));
}

TEST(test_is_face_or_ace) {
    Card a(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card b(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card d(Card::RANK_KING, Card::SUIT_HEARTS);
    Card e(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, a.is_face_or_ace());
    ASSERT_EQUAL(true, b.is_face_or_ace());
    ASSERT_EQUAL(true, c.is_face_or_ace());
    ASSERT_EQUAL(true, d.is_face_or_ace());
    ASSERT_EQUAL(false, e.is_face_or_ace());
}

TEST(test_is_right_or_left_bower) {
    Card a(Card::RANK_JACK, Card::SUIT_SPADES);
    Card b(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card d(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_ACE, Card::SUIT_SPADES);
    std::string trump = Card::SUIT_SPADES;
    ASSERT_EQUAL(false, a.is_left_bower(trump));
    ASSERT_EQUAL(true, a.is_right_bower(trump));
    ASSERT_EQUAL(true, b.is_left_bower(trump));
    ASSERT_EQUAL(false, b.is_right_bower(trump));
    ASSERT_EQUAL(false, c.is_left_bower(trump));
    ASSERT_EQUAL(false, c.is_right_bower(trump));
    ASSERT_EQUAL(false, d.is_left_bower(trump));
    ASSERT_EQUAL(false, d.is_right_bower(trump));
    ASSERT_EQUAL(false, e.is_left_bower(trump));
    ASSERT_EQUAL(false, e.is_right_bower(trump));
    trump = Card::SUIT_CLUBS;
    ASSERT_EQUAL(true, a.is_left_bower(trump));
    ASSERT_EQUAL(false, a.is_right_bower(trump));
    ASSERT_EQUAL(false, b.is_left_bower(trump));
    ASSERT_EQUAL(true, b.is_right_bower(trump));
    ASSERT_EQUAL(false, c.is_left_bower(trump));
    ASSERT_EQUAL(false, c.is_right_bower(trump));
    ASSERT_EQUAL(false, d.is_left_bower(trump));
    ASSERT_EQUAL(false, d.is_right_bower(trump));
    ASSERT_EQUAL(false, e.is_left_bower(trump));
    ASSERT_EQUAL(false, e.is_right_bower(trump));
}

TEST(test_is_trump) {
    Card a(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    std::string trump = Card::SUIT_HEARTS;
    ASSERT_EQUAL(true, a.is_trump(trump));
    ASSERT_EQUAL(true, b.is_trump(trump));
    trump = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(false, a.is_trump(trump));
    ASSERT_EQUAL(true, b.is_trump(trump));
    trump = Card::SUIT_CLUBS;
    ASSERT_EQUAL(false, a.is_trump(trump));
    ASSERT_EQUAL(false, a.is_trump(trump));

}

TEST(test_bool_operators) {
    Card a(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card b(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card d(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card e(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card f(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card g(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card h(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card i(Card::RANK_JACK, Card::SUIT_HEARTS);
    std::string trump = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(true, a == b);
    ASSERT_EQUAL(true, a > c);
    ASSERT_EQUAL(true, a < d);
    ASSERT_EQUAL(true, a <= e);
    ASSERT_EQUAL(true, a >= f);
    ASSERT_EQUAL(true, a > g);
    ASSERT_EQUAL(true, a > h);
    ASSERT_EQUAL(true, a > i);
    ASSERT_EQUAL(false, a != b);
}

TEST(test_os_operator) {
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    std::ostringstream os;
    std::string output1;
    std::string output2;
    std::string output3;
    os << c;
    ASSERT_EQUAL("Ace of Spades", os.str());
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Card::SUIT_CLUBS, Suit_next(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_SPADES, Suit_next(Card::SUIT_CLUBS));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, Suit_next(Card::SUIT_HEARTS));
    ASSERT_EQUAL(Card::SUIT_HEARTS, Suit_next(Card::SUIT_DIAMONDS));
}

TEST(test_card_less) {
    Card a(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card b(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card d(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card e(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card f(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card g(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card h(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card i(Card::RANK_JACK, Card::SUIT_HEARTS);
    std::string trump = Card::SUIT_DIAMONDS;

    
    ASSERT_EQUAL(false, Card_less(a,b,trump));
    ASSERT_EQUAL(false, Card_less(a,c,trump));
    ASSERT_EQUAL(true, Card_less(a,d,trump));
    ASSERT_EQUAL(true, Card_less(a,e,trump));
    ASSERT_EQUAL(false, Card_less(a,f,trump));
    ASSERT_EQUAL(true, Card_less(a,g,trump));
    ASSERT_EQUAL(true, Card_less(a,h,trump));
    ASSERT_EQUAL(true, Card_less(a,i,trump));
    ASSERT_EQUAL(true, Card_less(i,h,trump));
    Card ledcard = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(false, Card_less(a,b,ledcard, trump));
    ASSERT_EQUAL(true, Card_less(a,c,ledcard, trump));
    ASSERT_EQUAL(true, Card_less(a,d,ledcard, trump));
    ASSERT_EQUAL(true, Card_less(a,e,ledcard, trump));
    ASSERT_EQUAL(false, Card_less(a,f,ledcard, trump));
    ASSERT_EQUAL(true, Card_less(a,g,ledcard, trump));
    ASSERT_EQUAL(true, Card_less(a,h,ledcard, trump));
    ASSERT_EQUAL(true, Card_less(a,i,ledcard, trump));
    ASSERT_EQUAL(true, Card_less(i,h,ledcard, trump));

}

TEST_MAIN()
