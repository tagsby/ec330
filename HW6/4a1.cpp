#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
//Stupid simple implementation.

int main() {
/* Solves the following crossword puzzle:
____
_###
____
*/
    int size[6]; //contains the # of letters for every n letter word
    int a1,a2,a3,a4,a5;

    char *ar1; //one letter length.
    char *ar2[2]; //two letter length.
    char *ar3[3]; //three letter length.
    char *ar4[4]; //four letter length.
    char *ar5[5]; //five letter length.

    fstream in ("dictionary");
    string entry;

    while (in >> entry) { //Find the number of available entries of each size
        if (entry.length() == 1)
            size[1]++;
        if (entry.length() == 2)
            size[2]++;
        if (entry.length() == 3)
            size[3]++;
        if (entry.length() == 4)
            size[4]++;
        if (entry.length() == 5)
            size[5]++;
    }
    printf("1: %d, 2: %d, 3: %d, 4: %d, 5: %d\n",size[1],size[2],size[3],size[4],size[5]);

    ar1 = new char [size[1]];
    for (int i=0; i<2; i++)
        ar2[i] = new char [size[2]];
    for (int i=0; i<3; i++)
        ar3[i] = new char [size[3]];
    for (int i=0; i<4; i++)
        ar4[i] = new char [size[4]];
    for (int i=0; i<5; i++)
        ar5[i] = new char [size[5]];

    in.seekg (0,in.beg); //Go back to the beginning!
    while (in >> entry) { //Fill the crossword puzzle in!
        if (entry.length() == 1)
            
        if (entry.length() == 2)
            size[2]++;
        if (entry.length() == 3)
            size[3]++;
        if (entry.length() == 4)
            size[4]++;
        if (entry.length() == 5)
            size[5]++;
    }


    delete[] ar1;
    for (int i=0; i<2; i++)
        delete[] ar2[i];
    for (int i=0; i<3; i++)
        delete[] ar3[i];
    for (int i=0; i<4; i++)
        delete[] ar4[i];
    for (int i=0; i<5; i++)
        delete[] ar5[i];
    return 0;
}
