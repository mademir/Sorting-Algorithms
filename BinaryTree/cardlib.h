#pragma once
// header file for cardlib

#include <string>

enum Suit { hearts, clubs, diamonds, spades };      // define suits

struct aCard {                          // defines a card
    int cardVal;                        // number 1..13
    Suit cardSuit;                      // suit
};

aCard getCard(std::string stdno);               // declares function to get a card from stdno string
std::string cardToStr(aCard c);                 // declares function to make a string from a card
int compareCards(aCard c1, aCard c2);           // declares function to compare two cards

