using namespace std;
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define BIG_WORDS 67469012
#define TOT_ITR 70
#define THREAD_TOT (int)(BIG_WORDS/TOT_ITR)
#define BUF_SIZE 90

int main() {
    //Open up the regex files.
    regex_t re;
    //Initial p to a vary large number.
    const char *p = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    const char *p2 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    const char *p3 = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    regmatch_t match;

    FILE *writeover;
    //Filepos222.txt contains first the position in the BigData file and second the current word in the file.
    //Open it up and write "0" to the first two lines. This way we start at line 0, word 0.
    writeover = fopen("Filepos222.txt","w");
    fputs("0\n0",writeover);
    fclose(writeover);

    //Open BigData!
    string word;
    string dict_word;


    //Numb is the current word in the file.
    int numb=1;

    //Pos is the starting file offset location in the current fork of the file search.
    //new_pos is the current position in the search. At the end of the fork, pos becomes new_pos
    long long pos=0;
    long long new_pos;

    //Create a new process with pid descriptor pid.
    pid_t pid;
    //tstring is a temporary string used to figure out the values of the previous end position/number.
    string tstring;
    //Explanation for i<136: Using cat BigData.txt | wc, I was able to find there is ~68 million words
    //in the file. Every child process ends after 500,000 words have been gone through in the file.
    //This number was chosen somewhat arbitrarily but was ultimately picked because it has the approx best
    //performance to memory ratio. We need to fork 136 processes of 500,000 words to read all 68 million
    //in the file.
    for (int i = 0; i<THREAD_TOT; i++) {
        //Fork the process!
        if ((pid = fork()) == 0) { //child process
            //Read the file starting offset position and the current word in the file.
            ifstream opost ("FilePos222.txt");
            getline(opost,tstring);
            pos=strtoll(tstring.c_str(), NULL, 0);
            getline(opost,tstring);
            numb=strtol(tstring.c_str(), NULL, 0);
            opost.close();

            fstream in ("BigData.txt");
            fstream dict ("odict");

            //Open BigData, ignoring the first "pos" characters unless it finds a null termination character.
            //The variable pos contains the starting offset position for the current processes' iteration.
            in.ignore(pos, '\0');

            //open Buid in append mode so we can write new BUIDs to it.
            ofstream post;

            //Pull in every word individually from BigData
            while (in >> word) {
                numb++;
//                fstream dict ("odict"); //I think this is ignorable.
                //Every 500,000 iterations this will happen. Numb always starts in a process at numb%500000==1.
                if (numb%TOT_ITR==0) {
                    //find the position we're ending at in the file.
                    new_pos = in.tellg();
                    dict.close();
                    in.close();
                    printf("Current word in file: %d\n",numb);
                    break;
                }
                if (numb%10==0)
                    printf("------------------------------numb: %d\n------------------------------",numb);

                char pstring[BUF_SIZE];
                dict.seekg(0); //Go to the beginning!
                //Put p as a c string.
                p2=strtok((char*)word.c_str(),"0123456789");
                while (p2 != NULL) {
                    while ( dict >> dict_word ) {
                        p=word.c_str();
                        p2=dict_word.c_str();

                        //since odict is ordered by size, we can break here & forget about future values.
                        if (strlen(p2)>strlen(p)) {
                            break;
                        }
                        regcomp(&re, p2, REG_ICASE);
                        //regexec will return 0 if there is a matched expression in the current word, comparing p to re
                        //stores the resulting match in match.
                        while(regexec(&re, p, 1, &match, 0) == 0) {
                            //rm_eo is the end of the match, rm_so is the beginning.
                            //This prints the string matching into the file.
                  //          printf("%s contains %s\n",p,p2);
                            p += match.rm_eo;
//                    strncpy(pstring,p+match.rm_eo,BUF_SIZE);
                        }
                    }
                    p2 = strtok(NULL, "0123456789");
                }
            }    //Put the new position and word into Filepos
            post.open("Filepos222.txt",ios_base::trunc);
            post << (int)new_pos;
            post << "\n";
            post << numb;
            post.close();
            return 0;
        } else { //parent process.
            pid_t childPid;
            int status;
            childPid=wait(&status);
            pos = new_pos;
            childPid = wait(&status); //wait for the child to finish.
        }
        //these shouldn't be relevant, but keeping them just because.
            pos = new_pos;
            word.clear();
    }

    return 0;
}