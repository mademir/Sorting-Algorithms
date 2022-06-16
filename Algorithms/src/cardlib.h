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
void printPack(std::string mess);  // declares function to print the cards in a pack
int compareCards(aCard c1, aCard c2);           // declares function to compare two cards
void swapCards(int n1, int n2);    // declares function to swap two cards in a deck
void bubbleSort();                    //declares function to sort the cards using bubble sort

