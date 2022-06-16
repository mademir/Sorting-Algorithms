#include <string>
#include <iostream>
#include "cardlib.h"
using namespace std;

// structure for a node in a binary sorted tree
struct treeNode {
    aCard card;                     //Actual data to be stored, which is an aCard variable in this case
    treeNode* less, * more;          // pointers to node with data less or more than in this node
};

treeNode* treeTop;                  // pointer to top of tree

treeNode* newNode(aCard c) {       //Create a new node with aCard c, return pointer to it
    treeNode* p = new treeNode;     // create space for node
    p->card = c;                    //Add data aCard c
    p->less = NULL;                 // pointers less and more are set to NULL
    p->more = NULL;
    return p;                       // return pointer to this new node 
}

int compareCards(aCard c1, aCard c2) {
    if (c1.cardSuit < c2.cardSuit) return -1;
    if (c1.cardSuit > c2.cardSuit) return 1;
    if (c1.cardVal < c2.cardVal) return -1;
    if (c1.cardVal > c2.cardVal) return 1;
    return 0;
}

string cardToStr(aCard c) {
    string res;
    string cval = "A23456789TJQK";
    string csuit = "HCDS";
    res = cval.substr(c.cardVal - 1, 1);
    res += csuit.substr(c.cardSuit, 1);
    return res;
}

void printTree(treeNode* p) {   // print the tree from node p
    if (p != NULL) {
        printTree(p->less);                     // print any nodes in less sub tree
        cout << cardToStr(p->card) << ", ";     //Print this node by using cardToStr to convert the card to a string
        printTree(p->more);                     // print any nodes in more sub tree
    }
}


treeNode* insertTree(treeNode* p, aCard c) {
    treeNode* ans = p;
    if (p == NULL) ans = newNode(c);    // if found NULL pointer, create new node and this is returned connecting to node above
    else if (compareCards(p->card, c) >= 0) p->less = insertTree(p->less, c);    //If c is less than the card in the current node, insert the card in less by calling insertTree recurively as the less of this node as p
    else p->more = insertTree(p->more, c);    //else insert the card in more by recursively calling insertTree as more of this node as p
    return ans;         // return pointer to new node, or to this node, as appropriate
}

int main()
{
    cout << "Tree Program!\n";

    treeTop = NULL;                             // initially an empty tree

    for (int ct = 0; ct < 20; ct++) //From 0 to 20
        treeTop = insertTree(treeTop, getCard("30021984")); //Get a card from the student ID and insert it to the tree

    

    printTree(treeTop);                         // and print
    cout << "\n";
}