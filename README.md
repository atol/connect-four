# Connect Four

## Background

Connect Four is a two-player game played on a 6x7 grid. Players take turns dropping their disc from the top into one of 
the columns, where it occupies the lowest empty slot in that column. The goal of the game is to be the first player to form a
horizontal, vertical or diagonal line of four of their own discs.

## Instructions

Compile the program by running `make`.

Run `./main' to start the game.

## Implementation

The program implements a pure Monte Carlo tree search algorithm. During its turn, the computer makes a list of all legal moves. 
For each move, it does a number of random playouts, i.e. it simulates playing the game using randomly chosen moves until 
a win, loss or draw is reached. The result of each game is recorded, and further random playouts are done.

Once the maximum number of playouts (1,000 in this case) has been completed, the algorithm chooses the move that resulted in 
the fewest number of losses.

## Example

```
   1     2     3     4     5     6     7  
|-----|-----|-----|-----|-----|-----|-----|
|     |     |     |     |     |     |     |
|-----|-----|-----|-----|-----|-----|-----|
|     |     |     |     |     |     |     |
|-----|-----|-----|-----|-----|-----|-----|
|     |     |     |     |     |     |     |
|-----|-----|-----|-----|-----|-----|-----|
|     |     |  O  |     |     |     |     |
|-----|-----|-----|-----|-----|-----|-----|
|     |     |  X  |     |     |     |     |
|-----|-----|-----|-----|-----|-----|-----|
|     |     |  X  |  O  |     |     |     |
|-----|-----|-----|-----|-----|-----|-----|

Make your move (1-7):
```