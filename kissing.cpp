#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <map>

using namespace std;
bool fullalph(map<char,int>); //Sees if the map contains all the alphabetic characters
void zero_map(map<char,int> &out); //Sets the alphabetic map to zero
//Adds the map into itself
void add_maps(map<char,int> &out, map<string,map<char,int> > &temp, string s);
void printpal(vector<string>); //prints the kissing palindrome string
void printmap(map<char,int> &in,bool nl); //prints a map, nl =newline, otherwise just uses spaces
void printvec(map<char,vector<string> > &in); //prints the maps of characters to strings
bool test_vector(vector<string> pal, string s); //tests if a string is inside of a vector
bool skipqxz(char c); //skips the character if it's q, x, or z
bool maps_diff(map<char,int> &map1, map<char,int> &map2);//True is map1/2 have overlaping char
bool check_end(string s, map<char,vector<string> > &map1); //check if s is the last string to that start char
int sum_map(map<char,int> &in);

int main() { //Test program
    //Screw it. I don't even care. Just throw the whole damned dictionary into here.
    vector<string> pal; //Contains only the relevant palindromes
    vector<string> kiss; //The kissing palindrome!
    vector<string> final_kiss; //The kissing palindrome!
    map<char,vector<string> > start_map; //map of the starting chars.
    map<string, map<char,int> > alph_map; //map containing a value for every individual pal.
    map<char,int> all_maps; //map containing the value of the kissing pal.
    int i, j;

    fstream pald ("pal");

    string entry;
    while (pald >> entry) //Put the palindrome entries into a vector
        if (entry.length()!=1)
            pal.push_back(entry);

    char first_char, cur_char;
    for (int i=0; i<pal.size(); i++) {
        first_char=*pal.at(i).begin();
        start_map[first_char].push_back(pal.at(i));
        for (int j=0; j<pal.at(i).length(); j++) { //put all the palindromes in the alpha map
            cur_char=*(pal.at(i).begin()+j); //find the char at location
            alph_map[pal.at(i)][cur_char]=1; //map all the possible chars
        }
    }
    zero_map(all_maps);

//bool test_vector(vector<string> pal, string s); //tests if a string is inside of a vector
//bool skipqxz(char c); //skips the character if it's q, x, or z
//bool maps_diff(map<char,int> &map1, map<char,int> &map2);//True is map1/2 have overlaping char
//map<char,vector<string> > start_map; //map of the starting chars.
//map<string, map<char,int> > alph_map; //map containing a value for every individual pal.
//map<char,int> all_maps; //map containing the value of the kissing pal.
    map<char,int> tmp_map; //map containing the value of the kissing pal.
    bool jflag;
    int length, final_length=99999;
    char last_char;
    string prev="a";
    string cur="a";
    string cur_final="a";
    int randval;
    int randpos;
    int itrs=1;
//    int sum_map(map<char,int> &in) {
//    bool fullalph(map<char,int> inmap) { //check if every letter is present in the map
//void add_maps(map<char,int> &out, map<string,map<char,int> > &temp, string s) {
    randval=rand()%26;
    randpos=rand()%(start_map['a'+randval].size());
    cur_final=start_map['a'+randval].at(randpos);
    printf("first: %s\n",cur_final.c_str());
    last_char=*(cur_final.end()-1);
    for (i=0; i<10; i++) {
        zero_map(tmp_map);
        add_maps(all_maps,alph_map,cur_final);
        randpos=rand()%(start_map['a'+randval].size());
        prev=cur_final; //put the last one on this one!
        kiss.push_back(prev); //throw that on kiss!
        last_char=*(cur_final.end()-1);

    return 0;
}

int sum_map(map<char,int> &in) {
    int out;
    for (int i=0; i<26; i++)
        out+=in['a'+i];
    return out;
}

bool check_end(string s, map<char,vector<string> > &map1) {
    string last_string=map1[*(s.begin())].back();
    if (!strcmp(last_string.c_str(),s.c_str()))
        return true;
    else
        return false;
}

void zero_map(map<char,int> &out) { //zeros all the letters in out.
    for (int i=0; i<26; i++)
        out['a'+i]=0;
}

void add_maps(map<char,int> &out, map<string,map<char,int> > &temp, string s) {
    for (int i=0; i<26; i++) //Adds together out+temp[s], stores in out.
        if (static_cast<int>(temp[s]['a'+i]))
            out['a'+i]=1;
}

bool fullalph(map<char,int> inmap) { //check if every letter is present in the map
    for (int i=0; i<26; i++) {
        if (skipqxz('a'+i))
            continue;
        if (inmap['a'+i]==0)
            return false;
    }
    return true;
}

void printpal(vector<string> pal) { //Prints the vector of strings
    for (int i=0; i<pal.size(); i++)
        printf("%s, ",pal.at(i).c_str());
    printf("\n");
}

void printvec(map<char,vector<string> > &in) { //Prints the map of the vector of strings
    for (int i=0; i<26; i++) {
        printf("\n%c: ",'a'+i);
        for (int j=0; j<in['a'+i].size(); j++)
            printf("%s%s",in['a'+i].at(j).c_str(),(j==in['a'+i].size()-1)?"\n":", ");
    }
    printf("\n");
}

void printmap(map<char,int> &in,bool nl) { //prints map, if nl=1, print newlines
    for (int i=0; i<26; i++) {
        printf("%c: %d%s",'a'+i,in['a'+i],nl?"\n":(i==25?"\n":", "));

    }
}

bool skipqxz(char c) { //skips the character if it's q, x, or z
    if ( (c=='q')||(c=='x')||(c=='z') )
        return true;
    else
        return false;
}

bool test_vector(vector<string> pal, string s) {
    for (int i=0; i<pal.size(); i++) //make sure there are no repeats
        if (s==pal.at(i)) //in the palindrome.
            return true;
    return false;
}

bool maps_diff(map<char,int> &map1, map<char,int> &map2) {
    printf("Maps_Dif: \n");
    printmap(map1,0);
    printf("\n");
    printmap(map2,0);
    printf("\n");
    for (int i=0; i<26; i++) {
        if (skipqxz('a'+i))
            continue;
        if (map1['a'+i]!=map2['a'+i])
            return false;
    }
    return true;
}
