//
//  Game_Implementation.h
//  8 puzzle
//
//  Created by Shuying Sun on 10/9/16.
//  Copyright © 2016 Shuying Sun. All rights reserved.
//

#ifndef Game_Implementation_h
#define Game_Implementation_h
#include "Game.h"



//Constructor

Game::Game():start_board(Board()){
    visited.insert(start_board);
    active.push(start_board);
}

Game::Game(int n):start_board(Board(n)){
    visited.insert(start_board);
    active.push(start_board);
}

Game::Game(vector<vector<int>>& arr):start_board(Board(arr)){
    visited.insert(start_board);
    active.push(start_board);
}




// Solve the puzzle
void Game::solve(){
    cout << start_board << endl;
    if (!start_board.is_solvable()){
        cout << "This is impossible to solve!" << endl; return;
    }
    parents[start_board] = Board(0);
    from_parent[start_board] = {};
    while (!active.top().is_goal()){
        Board temp = active.top();
        active.pop();
        map<Board,pair<int,char>> neighbors = temp.next_boards();
        for (auto p : neighbors){
            Board b = p.first;
            if (visited.find(b) == visited.end()){
                parents[b] = temp;
                from_parent[b] = neighbors[b];
                visited.insert(b);
                active.push(b);
            }
        }
    }
    path.push_back(active.top());
    directions.push_back(from_parent[active.top()]);
    while(parents[path[path.size()-1]].get_size() != 0){
        path.push_back(parents[path[path.size()-1]]);
        directions.push_back(from_parent[path[path.size()-1]]);
    }
    min_num = path.size()-1;
    //print_solution();
}



// Print the best way to succeed.
void Game::print_solution(){
    if (min_num < 0){
        cout << "No solution" << endl;
        return;
    }
    cout << "we need to make " << min_num << " move\n" << endl;
    for (int i = path.size()-2; i >= 0; --i){
        cout << "we move " << directions[i].first << " ";
        switch(directions[i].second){
            case 'u' : cout << "up" << endl; break;
            case 'd' : cout << "down" << endl; break;
            case 'l' : cout << "left" << endl; break;
            case 'r' : cout << "right" << endl; break;
                
        }
        cout << path[i] << endl;
    }
}


#endif /* Game_Implementation_h */
