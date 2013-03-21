//Trie data structure. File contains Trie/Node classes
//Concept taken from http://login2win.blogspot.com/2011/06/c-tries.html
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct Rhits { //Rhits contains the amount of hits in a word search and the related strings
    int hits;
    vector<string> words;
    Rhits& operator+=(Rhits& a) { //Overload += operator.
        hits+=a.hits;
        for (int i=0; i<a.words.size(); i++)
            words.push_back(a.words.at(i));
    }
};

class Node { //Node is a class describing individual nodes in the trie structure.
public:
    //The Node is a particular character in the trie struct. It contains a single character,
    //a marker to denote potential end of words (EOW), and potential children.
    Node() { Data = ' '; Eow = false; } //Start with a space char and no EOW marker
    ~Node() {} //Default destructor
    char data() { return Data; }
    void setData(char c) { Data = c; }
    bool eow() { return Eow; }
    void setEow() { Eow = true; }
    Node* findChild(char c); //Sees if a child is on the Node.
    void appendChild(Node* child) { Child.push_back(child); }
    vector<Node*> children() { return Child; }

private:
    char Data;
    bool Eow;
    vector<Node*> Child;
};

class Trie { //Trie class. Contains a tree of char that represent words that split at different
public:      //characters. Functions are named coherently. (They say what they do)
    Trie();
    ~Trie();
    void addWord(string s);
    bool searchWord(string s); //See if the string is a word.
    Rhits searchSubWords(string s); //search for all subwords within the string.
    void deleteWord(string s);
private:
    Node* root;
};

//If a child node belongs to the current node, return the Node* relating to the child,
//Otherwise, return NULL (there is no matching child)
Node* Node::findChild(char c) {
    //Child is a vector of Nodes. Using the std::vector functions the total amount of children
    //belonging to Child can be found using the STL ::size() function
    for ( int i = 0; i < Child.size(); i++ ) { //Loop through ever
        //std::vector::at(n) returns the pointer relating to the nth element of the vector.
        Node* child = Child.at(i);
        if ( child->data() == c ) {
            return child;
        }
    }
    return NULL; //If no children nodes match the char input argument, return NULL.
}

Trie::Trie() { //Create a default node on Trie construction.
    root = new Node();
}

Trie::~Trie() { } //Default Class distructor

void Trie::addWord(string s) { //Adds a word to the Trie tree.
    Node* current = root;

    if ( s.length() == 0 ) { //if s is empty, create Eow flag at the root.
        current->setEow();
        return;
    }

    for ( int i = 0; i < s.length(); i++ ) { //go through the string char by char
        Node* child = current->findChild(s[i]); //See if there is a child.
        if ( child != NULL ) {
            current = child; //If so, go down in the trie to the child node.
        } else { //If no child, create a new node and set the data to the current string char
            Node* nchild = new Node();
            nchild->setData(s[i]);
            current->appendChild(nchild); //append the new child node to the parent node.
            current = nchild; //Go down in the trie to the newly created child node.
        }
        if ( i == s.length() - 1 )
            current->setEow(); //Set the Eow flag at the last node.
    }
}

//Searches through the trie for matching strings.
//Returns true if the word is in the trie, otherwise false.
bool Trie::searchWord(string s) {
    Node* current = root;
    while (current != NULL) { //while not strictly necessary, but here as a precaution
        for (int i=0; i<s.length(); i++) { //loop through entirety of string by char
            Node* child = current->findChild(s[i]); //See if the node has current char in children
            if (child == NULL) //findChild returns NULL if there is no relevant child.
                return false;  //Therefore this is false in that case.
            current = child; //Go down to the next child.
        }

        if ( current->eow() ) //Once done check if last node has an eow flag.
            return true;
        else
            return false;
    }
    return false; //Just in case.
}

Rhits Trie::searchSubWords(string s) {
//    Node* current = root;
    //struct Rhits contains: int hits,   vector<string> words
    Rhits results;
    int length=-1;
    bool breakflag;
    string sub_str;
    //Look for substrings throughout the entirety of the string. First test for substrings
    //throughout the entire string (substrings starting with the first char), then loop
    //though the string starting at it's second string (substrings starting with the second
    //char in the string). Continue until the end of the string.
    for (int i=0; i<s.length(); i++) { //loop through s by char. Do this s.length() times.
        breakflag=1;
        Node* current = this->root; //Set current node to the root.
        Node* child = this->root; //See if node has string char in child
        for (int j=i; (j<s.length())&&(breakflag); j++) {
            Node* child = current->findChild(s[j]); //See if node has string char in child
      //      printf("i: %d, j: %d",i,j);
            if (child == NULL) {//Make sure there are substrings that start here!
    //            printf("\nNull child!\n");
                breakflag=0;  //Test the next substring. All substrings that may happen after
                //the null child will be caught in further iterations.
            } else {
//                printf(", char: %c\n",child->data());
                if (child->eow()) { //See if there's currently an eow flag
                    results.hits++; //Increment hits
                    sub_str=s.substr(i,j-i+1);
  //                  printf("Found result: %s! for i=%d\n",sub_str.c_str(),i);
                    results.words.push_back(sub_str); //add the substring to the string vec
                }
                current = child; //Bring current down to the next child node.
            }
        }
    }
    return results;
}


int main() { //Test program
    Trie* trie = new Trie();

    fstream in ("SmallData.txt");
    fstream dict ("Dictionary");
    //struct Rhits contains: int hits,   vector<string> words
    Rhits hits;
    Rhits hits2;
    hits2.hits=2;

    string entry;
    string word;
    while (dict >> entry) {
        transform(entry.begin(), entry.end(), entry.begin(), ::tolower);
        trie->addWord(entry);
    }
    printf("Trie constructed from dictionary!\n");

    hits=trie->searchSubWords("hellooob2all");
    cout << "Found the following results for hellooob2all: ";
    for (int i=0; i < hits.words.size(); i++) {
        cout << hits.words.at(i) << " ";
    }
    printf("\nWith total: %d\n",hits.hits);
    hits2 = trie->searchSubWords("poop");
    cout << "Found the following results for poop: ";
    for (int i=0; i < hits2.words.size(); i++) {
        cout << hits2.words.at(i) << " ";
    }
    printf("\nWith total: %d\n",hits2.hits);
    hits2 += hits;
    cout << "Found the following results for the two summed: ";
    for (int i=0; i < hits2.words.size(); i++) {
        cout << hits2.words.at(i) << " ";
    }
    printf("With total: %d\n",hits2.hits);

    if (trie->searchWord("n"))
        printf("There was an n\n");

    delete trie;
}
