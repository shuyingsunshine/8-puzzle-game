//
//  main.cpp
//  8 puzzle
//
//  Created by Shuying Sun on 10/8/16.
//  Copyright © 2016 Shuying Sun. All rights reserved.
//






#include "Game_Implementation.h"
#include <queue>
using std::queue;



int main(int argc, const char * argv[]) {
    for (int i = 1; i <= 3; ++i){
        Game g;
        g.solve();
        g.print_solution();
    } 
    
    return 1;

}
