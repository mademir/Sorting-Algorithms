// SortCard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "cardlib.h"

#include <string>
#include <iostream>
using namespace std;

int compareCount, moveCount, maxDepth;
const int maxCard = 20;

aCard thePack[maxCard];

string cardToStr(aCard c) { //Takes one aCard. Converts the given card's value and suit to characters, makes a string from them and returns the string.
    string res;                         //String to store the result.
    string cval = "A23456789TJQK";      //String that represents the value of a card from ace to king.
    string csuit = "HCDS";              //String that represents the suit of a card from hearts to spades.
    res = cval.substr(c.cardVal-1, 1);  //Takes the character from cval according to the cardVal value of the card and writes it to result string.
    res += csuit.substr(c.cardSuit, 1); //Takes the character from csuit according to the cardSuit value of the card and appends it to result string.
    return res;
}

void printPack(string mess) {  //Takes a string for message and returns nothing. Prints the message and then the cards as a string.
    string res;                                     //String to store the result
    res = mess + ":\t";                             //Writes the message from the argument and a colon to the result string
    for (int ct = 0; ct < maxCard; ct++)            //For each card in the pack
        res += cardToStr(thePack[ct]) + ",";        //Call cardToStr for that card and add it to the result string with a comma
    cout << res.substr(0, res.length() - 1) + "\n"; //Removes the last character from res (which is a comma) and adds a new line character and prints
}

int compareCards(aCard c1, aCard c2) {  //Takes two aCards and retuns an integer. Compares two cards by their suits then their values.
    compareCount++;                             //Increase the compare counter
    if (c1.cardSuit < c2.cardSuit) return -1;   //Returns -1 if c2 has a greater suit
    if (c1.cardSuit > c2.cardSuit) return 1;    //Returns 1 if c1 has a greater suit
    if (c1.cardVal < c2.cardVal) return -1;     //If the suits are the same, returns -1 if c2 has a greater value
    if (c1.cardVal > c2.cardVal) return 1;      //If the suits are the same, returns 1 if c1 has a greater value
    return 0;                                   //Returns 0 if both the suits and the values are the same
}

void swapCards(int n1, int n2) {    //Takes 2 integers as indexes for the cards in the pack and returns nothing. Swaps the cards on given indexes.
    aCard temp = thePack[n1];   //Saves the card on the first given index to a temporary aCard variable. Move 1
    thePack[n1] = thePack[n2];  //Puts the card on the second given index to the first given index. Move 2
    thePack[n2] = temp;         //Puts the card in temp to the second given index. Move 3
    moveCount += 3;             //Adds 3 moves to the move counter
}

void bubbleSort() {//Takes no arguments and returns nothing. Sorts the cards in the pack using bubble sort method.
    for (int i = 1; i < maxCard; i++)               //For 1 to number of cards as i
        for (int j = maxCard - 1; j > i - 1; j--)   //For number of cards to i-1 as j
            if (compareCards(thePack[j - 1], thePack[j]) == 1) swapCards(j - 1, j); //If the card behind the card at index j is greater than the card at index j, then swap those 2 cards
}

void quickSort(int low, int high, int recursiveDepth = 0) {//Takes 2 integers for the low index and the high index, and another one to keep track of the depth of recursion (Default value of 0 is given). Returns nothing. Sorts the cards in the pack using quick sort method.
    aCard pivot = thePack[(low + high) / 2];    //Sets the pivot to the card at the middle
    int i = low;                                //Sets i to the low value
    int j = high;                               //Sets j to the high value
    do {
        while (compareCards(thePack[i], pivot) == -1) i++;  //From the start of the current pack, increase i while the card is less than pivot
        while (compareCards(thePack[j], pivot) == 1) j--;   //From the end of the current pack, decrease j while the card is greater than pivot
        if (i <= j){
            if (i < j) swapCards(i, j); //If i is less than j, swap the cards at indexes i and j
            i++;                        //Increase i if it is less than or equals to j
            j--;                        //Decrease j if it is greater than i
        }
    } while (i < j);                    //Keep executing the loop while i is less than j
    if (low < j) quickSort(low, j, recursiveDepth+1);   //If low index is less than j, then call the function recursively by passing j as the high index and incresing the depth value
    if (i < high) quickSort(i, high, recursiveDepth+1); //If i is less than the high index, then call the function recursively by passing i as the low index and incresing the depth value
    maxDepth = (recursiveDepth > maxDepth) ? recursiveDepth : maxDepth; //When this call is finished, set global variable to store the max depth to the current depth if the current depth is greater
}

//Already given for loop to get the cards as a function.
void getCards() {
    for (int ct = 0; ct < maxCard; ct++)
        thePack[ct] = getCard("32101234");
}

int main()
{
    cout << "Card Sorting!\n";

    //for (int ct = 0; ct < maxCard; ct++)
    //    thePack[ct] = getCard("30021984");

    //printPack("Unsorted");

    //cout << "Comparing " << cardToStr(thePack[0]) << " and " << cardToStr(thePack[1]) << " -> " << compareCards(thePack[0], thePack[1]) << "\n";
    //cout << "Comparing " << cardToStr(thePack[0]) << " and " << cardToStr(thePack[0]) << " -> " << compareCards(thePack[0], thePack[0]) << "\n";
    //cout << "Comparing " << cardToStr(thePack[2]) << " and " << cardToStr(thePack[3]) << " -> " << compareCards(thePack[2], thePack[3]) << "\n";

    //swapCards(0, 2);
    //printPack("1st and 3rd swapped");
    
    srand(100); //Set the random seed
    getCards(); //Get the cards from the student number
    printPack("Unsorted");  //Print the unsorted pack
    cout << "\n";

    compareCount = moveCount = 0;   //Set the counters to 0 before sorting
    bubbleSort();
    printPack("Bubble Sorted");     //Print the bubble sorted pack
    cout << "Comparisons made: " << compareCount << "\nTimes cards were moved: " << moveCount << "\n";  //Print the counter values
    cout << "\n";

    srand(100);
    getCards();
    compareCount = moveCount = maxDepth = 0;    //Set the counters and the recursion depth count to 0
    quickSort(0, maxCard - 1);                  //Call quick sort with 0 as the low index and number of cards - 1 as the high index
    printPack("Quick Sorted");                  //Print the quick sorted pack
    cout << "Comparisons made: " << compareCount << "\nTimes cards were moved: " << moveCount << "\nMaximum depth of recursion: " << maxDepth <<"\n";   //Print the counter values

}


