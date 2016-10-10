//
//  Game.h
//  8 puzzle
//
//  Created by Shuying Sun on 10/9/16.
//  Copyright © 2016 Shuying Sun. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "Board_Implementaion.h"

#include <queue>
using std::priority_queue;

#include <set>
using std::set;


struct compare{
    bool operator()(const Board& a, const Board& b){
        if (a.get_score() > b.get_score()) return true;
        if (a.get_score() == b.get_score() && a.get_num_moves() > b.get_num_moves()) return true;
        return false;
    }
};


class Game{
public:
    //Constructor
    Game();  //Default randomly generate a 3*3 start board
    Game(int n); //Generate a n*n start board either randomly or by your inputs
    Game(vector<vector<int>>& arr);
    
    //methos
    void solve();
    void print_solution();
    void print_initial(){cout << start_board << endl;}
    int get_min_moves(){return min_num;}
    
private:
    Board start_board{Board()};
    int min_num{-1};
    set<Board> visited{};
    map<Board,Board> parents{};
    map<Board,pair<int,char>> from_parent{};
    priority_queue<Board,vector<Board>,compare> active{};
    vector<Board> path{};
    vector<pair<int,char>> directions{};
};


#endif /* Game_h */
