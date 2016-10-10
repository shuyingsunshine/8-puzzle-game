

The 8 puzzle game is  a sliding puzzle that consists of a frame of numbered square tiles in random order with one tile missing. The object of the puzzle is to place the tiles in order (see diagram) by making the fewest sliding moves that use the empty space. The puzzle also exists in other sizes, say 15 puzzle on a 16 tiles board.

Not every board can be solved, it depends on the parity of the number of inversions of the tile arrangement and the row for which the missing tile is located. (In the case of 8 puzzle, if the number of inversions is odd, then it is unsolvable. Otherwise, it is solvable. In the case of 16 puzzle, it is solvable if and only if one of the following statements holds:
    
     1. the number of inversions is even, and the missing tile must be on the odd row counting from the bottom.
     2. the number of inversions is odd, and the missing tile must be on the even row counting from the bottom.

If the board can be solved, then we can solve the game by using A* search algorithm. In particular, we create a priority queue such that it it ordered by score which is defined to be the hamming distance + number of moves from the initial state. At each iteration, we pop the one with the smallest score, and explore its next moves, and insert those moves to the priority queue. By the time we pop out the goal board, we are done. 

In Board.h, I declare a class Board.
In Board_Implementation.h, I define the member functions of the class Board.

In Game.h, I declare a class Game.
In Game_Implementation.h, I define the member functions of the class Game.

In main.cpp, run for several boards, and give the solutions. 


