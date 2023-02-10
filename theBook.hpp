/*
 * Grave
 *
 * theBook class
 * 
 * 
 */

#ifndef _THE_BOOK_H_
#define _THE_BOOK_H_

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

//Defining type so that we know which "side" of the bet the user is on.
//      for instance... true would always mean the left side of the bet:
//      home team (for moneyline), over (for O/U), and favorite in the spread.
//      false would be right side of the bet.
//      ideally, I'd make it easier than always saying true or false.
typedef bool side;

class theBook {
public:
        //Function to search user information array, display their bets
        
        //Function to put a bet into the user information array

        //Function to put a bet into the book hash table
        
        //Function to print out the state of the book

        

private:
        struct bet {
                side leftOrRight;
                int betAmount;
                string userName;
        }
        struct key {
                //Vectors of unmatched bets.
                vector<bet> openSpreadBets;
                vector<bet> openOverUnderBets;
                vector<bet> openMLBets;
                //Need a good data structure in order to be able to print
                //out bets that are matched.

        }
        //Is this the right way
        hash<string> myHash;
        unordered_map<string, key> book;
        //This vector will display a user's bets (open and closed)
        vector<string> userInformation;
};

#endif