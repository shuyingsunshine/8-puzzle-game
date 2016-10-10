//
//  Board_Implementaion.h
//  8 puzzle
//
//  Created by Shuying Sun on 10/9/16.
//  Copyright © 2016 Shuying Sun. All rights reserved.
//

#ifndef Board_Implementaion_h
#define Board_Implementaion_h


#include "Board.h"

#include <vector>
using std::vector;

int inversions(vector<int>::iterator beg, vector<int>::iterator end){ //modified mergesort to get inversion number
    if (beg + 1 == end) return 0;
    if (beg + 2 == end){
        if (*beg > *(beg+1)){
            std::swap(*beg,*(beg+1));
            return 1;
        }
        return 0;
    }
    auto med = beg + (end-beg)/2;
    int res = inversions(beg,med+1)+inversions(med+1,end);
    vector<int> temp(beg,med+1);
    auto first = temp.begin();
    auto second = med+1;
    auto cur = beg;
    while ( first != temp.end() && second != end){
        if (*first <= *second){
            *cur = *first;
            ++first;
            ++cur;
        }
        else{
            *cur = *second;
            res += (temp.end()-first);
            ++second;
            ++cur;
        }
    }
    if (second != end) return res;
    while (first != temp.end()){
        *cur = *first;
        ++first;
        ++cur;
    }
    return res;
}


std::default_random_engine Board::generator(time(0));


std::uniform_int_distribution<int> Board::get_distribution(int n){
    return std::uniform_int_distribution<int>(0,n-1);
}


// random generate a tile
void Board::random_generate(){
    int random_board[size*size];
    random_board[0] = 1;
    for (int i = 2; i <= size*size;++i){ //uniformly randomly generate a permutation of [1,2,...,n*n] in O(n*n).
        std::uniform_int_distribution<int> my_dis = get_distribution(i);
        my_dis.reset();
        int temp = my_dis(generator);
        random_board[i-1] = i;
        std::swap(random_board[temp],random_board[i-1]);
        if (i == size*size){
            space_column = (temp)%size; space_row = temp/size;
        }
    }
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            int label{i*size+j};
            if (label+1 != random_board[label]) ++num_wrong;
            tiles[i][j] = random_board[label];
        }
    }
}

//generate a tile by input
void Board::input_generate(){
    unordered_map<int,bool> appeared;
    for (int i = 0; i < size; ++i){
        cout << "please write the " << size << " elements of the " << i+1 << " line \n";
        for (int j = 0; j < size; ++j){
            int a;
            cin >> a;
            while (a <= 0 || a > size*size || appeared[a]){
                cout << "invalid number, shown before, please write a valid number between 1 and "<<size*size <<":\n";
                cin >> a;
            }
            if (a == size*size){
                space_row = i; space_column = j;
            }
            if (a != i*size+j+1) ++num_wrong;
            tiles[i][j] = a;
            appeared[a] = true;
        }
    }
}


//Board Constructor

Board::Board():size(3),tiles(vector<vector<int>>(3,vector<int>(3,0))){
    random_generate();
}

Board::Board(int n):size(n),tiles(vector<vector<int>>(n,vector<int>(n,0))){
    if (n == 0) return;
    cout << "Do you want to build the board yourself? y/n" << endl;
    string s;
    cin >> s;
    while (s != "y" && s != "n"){
        cout << "please answer y or n" << endl; cin >> s;
    }
    if (s == "y") input_generate();
    else random_generate();
}

Board::Board(vector<vector<int>>& arr): size(arr.size()),tiles(vector<vector<int>>(size,vector<int>(size,0))){ //given a tile, generate the board
    cout << "Generating the board in your way" << endl;
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++i){
            tiles[i][j] = arr[i][j];
            if (tiles[i][j] != i*size+j+1) ++num_wrong;
            if (tiles[i][j] == size*size){
                space_row = i; space_column = j;
            }
        }
    }
}



//Board Copy

Board::Board(const Board& orig):size(orig.size),tiles(vector<vector<int>>(orig.size,vector<int>(orig.size,0))),space_row(orig.space_row), space_column(orig.space_column), num_wrong(orig.num_wrong), num_moves(orig.num_moves){
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            tiles[i][j] = orig.tiles[i][j];
        }
    }
}


//Determine if this board is solvable.
bool Board::is_solvable() const{
    vector<int> in_order;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (tiles[i][j] != size*size) in_order.push_back(tiles[i][j]);
    int number = inversions(in_order.begin(),in_order.end());
    if (size % 2 == 1) return number % 2 ==0;
    if (number % 2 == 0) return (size-space_row)%2 == 1;
    return (size-space_row)%2 == 0;
}


//Given the next board's space position, determine how we could move from the current board
pair<int,char> Board::corres_direction(pair<int, int> a){
    char res;
    if (a.first == space_row) res = (a.second == space_column+1) ? 'l' : 'r';
    else res = (a.first == space_row+1) ? 'u'  : 'd';
    return make_pair(tiles[a.first][a.second],res);
}

//move from the current board to the next avaiable boards
map<Board,pair<int,char>> Board::next_boards(){
    vector<pair<int,int>> neighbors_space{make_pair(space_row,space_column-1),make_pair(space_row,space_column+1),make_pair(space_row-1,space_column), make_pair(space_row+1,space_column)};
    map<Board,pair<int,char>> res;
    for (pair<int,int> s : neighbors_space){
        if (s.first >= 0 && s.first < size && s.second >=0 && s.second < size){
            Board temp(*this);
            temp.num_moves += 1;
            temp.space_row = s.first;
            temp.space_column = s.second;
            temp.tiles[s.first][s.second] = size*size;
            if (space_row == size-1 && space_column == size-1) ++temp.num_wrong;
            else if (s.first == size-1 && s.second == size-1) --temp.num_wrong;
            temp.tiles[space_row][space_column] = tiles[s.first][s.second];
            if (tiles[s.first][s.second] == s.first*size+s.second+1) ++temp.num_wrong;
            else if (tiles[s.first][s.second] == space_row*size+space_column+1) --temp.num_wrong;
            res[temp] = corres_direction(s);
        }
    }
    return res;
}



//overloaded << operator
ostream  &operator<< (ostream &os, const Board & my_board){
    int n = my_board.size;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (my_board.tiles[i][j] != n*n) os << my_board.tiles[i][j] << "\t";
            else os << " " << "\t";
        }
        os << endl;
    }
    return os;
}

//overloaded < operator
bool operator<(const Board& a, const Board& b){
    return a.tiles < b.tiles;
}


#endif /* Board_Implementaion_h */
