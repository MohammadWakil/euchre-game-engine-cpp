#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_add_card){
    Player * john = Player_factory("John", "Simple");
    Card c(ACE, SPADES);
    john->add_card(c);
    Card played = john->lead_card(SPADES);
    ASSERT_EQUAL(played, c);

    delete john;
}

/*TEST(test_player_lead_card_fail){
    Player * logan = Player_factory("Logan", "Simple");
    Card c(ACE, SPADES);
    Card c1(QUEEN, DIAMONDS);
    Card c2(KING, HEARTS);
    Card c3(ACE, CLUBS);
    Card c4(JACK, CLUBS);
    logan->add_card(c);
    logan->add_card(c1);
    logan->add_card(c2);
    logan->add_card(c3);
    logan->add_card(c4);
    
    Card played = logan->lead_card(SPADES);
    ASSERT_EQUAL(played, c);

    Card played2 = logan->lead_card(DIAMONDS);
    ASSERT_EQUAL(played2, c1);

    Card played3 = logan->lead_card(HEARTS);
    ASSERT_EQUAL(played3, c2);

    Card played4 = logan->lead_card(CLUBS);
    ASSERT_EQUAL(played4, c4);

    Card played5 = logan->lead_card(CLUBS);
    ASSERT_EQUAL(played5, c3);

    logan->lead_card(SPADES);
    
    delete logan;
}*/

TEST(test_player_make_trump_strong_hand){
    Player * bonnie = Player_factory("Bonnie", "Simple");
    Card c1(QUEEN, HEARTS);
    Card c2(KING, HEARTS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(KING, SPADES);
    bonnie->add_card(c1);
    bonnie->add_card(c2);
    bonnie->add_card(c3);
    bonnie->add_card(c4);
    bonnie->add_card(c5);
    Card up_card(ACE, HEARTS);
    Suit order_up;
    bool result = bonnie->make_trump(up_card, false, 1, order_up);
    ASSERT_TRUE(result);
    ASSERT_EQUAL(HEARTS, order_up);

    delete bonnie;
}

TEST(test_player_make_trump_upcard_jack){
    Player * bonnie = Player_factory("Bonnie", "Simple");
    Card c1(QUEEN, HEARTS);
    Card c2(KING, HEARTS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(KING, SPADES);
    bonnie->add_card(c1);
    bonnie->add_card(c2);
    bonnie->add_card(c3);
    bonnie->add_card(c4);
    bonnie->add_card(c5);
    Card up_card(JACK, HEARTS);
    Suit order_up;
    bool result = bonnie->make_trump(up_card, false, 1, order_up);
    ASSERT_TRUE(result);
    ASSERT_EQUAL(HEARTS, order_up);

    delete bonnie;
}

TEST(test_player_make_trump_left_bower){
    Player * bonnie = Player_factory("Bonnie", "Simple");
    Card c1(QUEEN, HEARTS);
    Card c2(KING, SPADES);
    Card c3(ACE, SPADES);
    Card c4(JACK, DIAMONDS);
    Card c5(KING, SPADES);
    bonnie->add_card(c1);
    bonnie->add_card(c2);
    bonnie->add_card(c3);
    bonnie->add_card(c4);
    bonnie->add_card(c5);
    Card up_card(JACK, HEARTS);
    Suit order_up;
    bool result = bonnie->make_trump(up_card, false, 1, order_up);
    ASSERT_TRUE(result);
    ASSERT_EQUAL(HEARTS, order_up);

    delete bonnie;
}


TEST(test_player_make_trump_weak_hand){
    Player * connor = Player_factory("Connor", "Simple");
    Card c1(TEN, DIAMONDS);
    Card c2(NINE, DIAMONDS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(KING, SPADES);
    connor->add_card(c1);
    connor->add_card(c2);
    connor->add_card(c3);
    connor->add_card(c4);
    connor->add_card(c5);
    Card up_card(ACE, HEARTS);
    Suit order_up;
    bool result = connor->make_trump(up_card, false, 1, order_up);
    ASSERT_FALSE(result);

    delete connor;
}

TEST(test_player_make_trump_round_2){
    Player * bron = Player_factory("Bron", "Simple");
    Card c1(KING, DIAMONDS);
    Card c2(QUEEN, DIAMONDS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(KING, SPADES);
    bron->add_card(c1);
    bron->add_card(c2);
    bron->add_card(c3);
    bron->add_card(c4);
    bron->add_card(c5);
    Card up_card(ACE, HEARTS);
    Suit order_up;
    bool result = bron->make_trump(up_card, false, 2, order_up);
    ASSERT_TRUE(result);
    ASSERT_EQUAL(DIAMONDS, order_up);

    delete bron;
}

TEST(test_player_make_trump_round_2_left_bower){
    Player * bron = Player_factory("Bron", "Simple");
    Card c1(KING, DIAMONDS);
    Card c2(QUEEN, SPADES);
    Card c3(ACE, SPADES);
    Card c4(JACK, HEARTS);
    Card c5(KING, SPADES);
    bron->add_card(c1);
    bron->add_card(c2);
    bron->add_card(c3);
    bron->add_card(c4);
    bron->add_card(c5);
    Card up_card(ACE, HEARTS);
    Suit order_up;
    bool result = bron->make_trump(up_card, false, 2, order_up);
    ASSERT_TRUE(result);
    ASSERT_EQUAL(DIAMONDS, order_up);

    delete bron;
}

TEST(test_player_make_trump_dealer){
    Player * james = Player_factory("James", "Simple");
    Card c1(TEN, DIAMONDS);
    Card c2(NINE, DIAMONDS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(KING, SPADES);
    james->add_card(c1);
    james->add_card(c2);
    james->add_card(c3);
    james->add_card(c4);
    james->add_card(c5);
    Card up_card(ACE, HEARTS);
    Suit order_up;
    bool result = james->make_trump(up_card, true, 2, order_up);
    ASSERT_TRUE(result);
    ASSERT_EQUAL(DIAMONDS, order_up);

    delete james;
}

TEST(test_player_add_and_discard){
    Player * linda = Player_factory("Linda", "Simple");
    Card c1(TEN, DIAMONDS);
    Card c2(NINE, DIAMONDS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(KING, SPADES);
    Card c6(NINE, SPADES);
    linda->add_card(c1);
    linda->add_card(c2);
    linda->add_card(c3);
    linda->add_card(c4);
    linda->add_card(c5);
    Card up_card(ACE, HEARTS);
    linda->add_and_discard(up_card);

    Card lead = linda->lead_card(up_card.get_suit());
    ASSERT_EQUAL(lead, c3); 

    Card lead1 = linda->lead_card(up_card.get_suit());
    ASSERT_EQUAL(lead1, c5); 
    
    Card lead2 = linda->lead_card(up_card.get_suit());
    ASSERT_EQUAL(lead2, c4); 

    Card lead3 = linda->lead_card(up_card.get_suit());
    ASSERT_EQUAL(lead3, c1); 

    Card lead4 = linda->lead_card(up_card.get_suit());
    ASSERT_EQUAL(lead4, up_card); 
    
    delete linda;
}

TEST(test_player_add_and_discard_hand_size_1){
    Player* kobe = Player_factory("Kobe", "Simple");
    Card c1(JACK, CLUBS);
    kobe->add_card(c1);
    Card up_card(ACE, HEARTS);
    kobe->add_and_discard(up_card);
    Card lead = kobe->lead_card(up_card.get_suit());
    ASSERT_EQUAL(lead, up_card);
}

TEST(test_player_lead_card_trump){
    Player * jamal = Player_factory("Jamal", "Simple");
    Card c3(QUEEN, HEARTS);
    Card c5(KING, HEARTS);
    jamal->add_card(c3);
    jamal->add_card(c5);
    Card up_card(ACE, HEARTS);
    Suit trump = up_card.get_suit();
    Card led = jamal->lead_card(trump);
    ASSERT_EQUAL(led, c5);

    delete jamal;
}

TEST(test_player_lead_card_trump_left_and_right_bower){
    Player * jamal = Player_factory("Jamal", "Simple");
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, HEARTS);
    Card c3(QUEEN, HEARTS);
    Card c5(KING, HEARTS);
    jamal->add_card(c1);
    jamal->add_card(c2);
    jamal->add_card(c3);
    jamal->add_card(c5);
    Card up_card(ACE, HEARTS);
    Suit trump = up_card.get_suit();
    Card led = jamal->lead_card(trump);
    ASSERT_EQUAL(led, c2);
    Card led2 = jamal->lead_card(trump);
    ASSERT_EQUAL(led2, c1);

    delete jamal;
}

TEST(test_player_lead_card_no_trump){
    Player * sally = Player_factory("Sally", "Simple");
    Card c1(TEN, DIAMONDS);
    Card c2(NINE, DIAMONDS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(KING, SPADES);
    sally->add_card(c1);
    sally->add_card(c2);
    sally->add_card(c3);
    sally->add_card(c4);
    sally->add_card(c5);
    Card up_card(ACE, HEARTS);
    Suit trump = up_card.get_suit();
    Card led = sally->lead_card(trump);
    ASSERT_EQUAL(led, c3);

    delete sally;
}

TEST(test_player_lead_card_mix){
    Player * sally = Player_factory("Sally", "Simple");
    Card c1(TEN, DIAMONDS);
    Card c2(NINE, DIAMONDS);
    Card c3(ACE, SPADES);
    Card c4(JACK, HEARTS);
    Card c5(KING, HEARTS);
    sally->add_card(c1);
    sally->add_card(c2);
    sally->add_card(c3);
    sally->add_card(c4);
    sally->add_card(c5);
    Card up_card(ACE, HEARTS);
    Suit trump = up_card.get_suit();
    Card led = sally->lead_card(trump);
    ASSERT_EQUAL(led, c3);

    delete sally;
}

TEST(test_player_play_card_some_matching_suit){
    Player * harden = Player_factory("Harden", "Simple");
    Card c1(TEN, DIAMONDS);
    Card c2(NINE, DIAMONDS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(KING, SPADES);
    harden->add_card(c1);
    harden->add_card(c2);
    harden->add_card(c3);
    harden->add_card(c4);
    harden->add_card(c5);
    Suit trump = HEARTS;
    Card led(ACE, DIAMONDS);
    Card played = harden->play_card(led, trump);
    ASSERT_EQUAL(played, c1);

    delete harden;
}

TEST(test_player_play_card_all_trump){
    Player * harden = Player_factory("Harden", "Simple");
    Card c1(TEN, HEARTS);
    Card c2(NINE, HEARTS);
    Card c4(JACK, HEARTS);
    Card c5(KING, HEARTS);
    harden->add_card(c1);
    harden->add_card(c2);
    harden->add_card(c4);
    harden->add_card(c5);
    Suit trump = HEARTS;
    Card led(ACE, DIAMONDS);
    Card played = harden->play_card(led, trump);
    ASSERT_EQUAL(played, c2);

    delete harden;
}
TEST(test_player_play_card_all_matching_suit){
    Player * harden = Player_factory("Harden", "Simple");
    Card c1(TEN, DIAMONDS);
    Card c2(NINE, DIAMONDS);
    Card c4(JACK, DIAMONDS);
    Card c5(KING, DIAMONDS);
    harden->add_card(c1);
    harden->add_card(c2);
    harden->add_card(c4);
    harden->add_card(c5);
    Suit trump = HEARTS;
    Card led(ACE, DIAMONDS);
    Card played = harden->play_card(led, trump);
    ASSERT_EQUAL(played, c5);

    delete harden;
}

TEST(test_player_play_card_no_matching_suit){
    Player * cole = Player_factory("Cole", "Simple");
    Card c1(TEN, DIAMONDS);
    Card c2(NINE, DIAMONDS);
    Card c3(ACE, SPADES);
    Card c4(JACK, CLUBS);
    Card c5(KING, SPADES);
    cole->add_card(c1);
    cole->add_card(c2);
    cole->add_card(c3);
    cole->add_card(c4);
    cole->add_card(c5);
    Suit trump = SPADES;
    Card led(ACE, HEARTS);
    Card played = cole->play_card(led, trump);
    ASSERT_EQUAL(played, c2);

    delete cole;
}


// Add more tests here

TEST_MAIN()
