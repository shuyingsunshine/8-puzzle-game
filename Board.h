//
//  Board.h
//  8 puzzle
//
//  Created by Shuying Sun on 10/9/16.
//  Copyright © 2016 Shuying Sun. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <stdio.h>
#include <iostream>
using std::cout; using std::endl; using std::ostream; using std::cin; using std::string;
#include <vector>
using std::vector;
#include <unordered_map>
using std::unordered_map;
#include <random>
#include<map>
using std::pair; using std::make_pair; using std::map;


class Board{
public:
    friend ostream& operator<<(ostream& os, const Board& my_board);
    friend bool operator<(const Board& a, const Board& b);
    //Constructor
    Board();      //default: generate a 3*3 board randomly
    Board(int n); //either generate n*n board randomly or by your inputs
    Board(vector<vector<int>>& arr);
    //Copy
    Board(const Board& orig);
    //methods
    bool is_solvable() const; //test if this is solvable tile
    bool is_goal() const {return num_wrong == 0;}
    int get_size() const {return size;}
    int get_score() const{ return num_wrong+num_moves;}
    int get_hamming_distance() const{return num_wrong;}
    int get_num_moves() const{return num_moves;}
    map<Board,pair<int,char>> next_boards();
    
private:
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> get_distribution(int n);
    void input_generate();
    void random_generate();
    pair<int,char> corres_direction(pair<int,int>);
    
    
    vector<vector<int>> tiles{};
    int size{0};
    int space_row{0};
    int space_column{0};
    int num_wrong{0};
    int num_moves{0};
    
};



#endif /* Board_h */
