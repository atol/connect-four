#ifndef MCTS_H
#define MCTS_H

#include "board.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>

class MonteCarlo
{
private:
    // Maximum number of playouts for each legal move
    const int MAX_MOVES = 1000;
    
public:
    // Default constructor
    MonteCarlo();

    // Default deconstructor
    ~MonteCarlo();

    // Runs a pure MCTS simulation and returns the play to make
    int pMCTS(Board board);

    // Does a random playout of the game
    void randomPlayout(Board board, int* tally);

    // Returns a random legal move
    int randomMove(Board board);
};

MonteCarlo::MonteCarlo()
{
}

MonteCarlo::~MonteCarlo()
{
}

// Plays the game using pure Monte Carlo Tree Search (pMCTS).
// For each legal move, it does some number of random playouts.
// It then returns the move that resulted in the fewest number of losses.
int MonteCarlo::pMCTS(Board board)
{
    // Make a list of legal moves
    std::vector<int> legal_moves;

    for (int i = 0; i < 7; i++)
    {
        if (board.columns[i] >= 0)
        {
            legal_moves.push_back(i);
        }
    }

    // Initialize best move with minimum number of losses
    int best_move = legal_moves.front();
    int min_losses = MAX_MOVES;

    // For each legal move, do a series of random playouts
    for (auto i: legal_moves)
    {
        // Record the number of wins, losses, and draws
        int tally[3] = {0};

        // Clone the current board
        Board copy = board;

        // Make the move
        copy.makeMove(i);

        // Do random playouts on the resulting board
        randomPlayout(copy, tally);

        // If the move results in the fewest number of losses in playouts,
        // update best_move to this move and min_losses to the number of losses
        if (tally[1] < min_losses)
        {
            min_losses = tally[1];
            best_move = i;
        }
    }

    return best_move;
}

// Simulates playing the game using randomly chosen moves until it is over.
// Records the result (a win, loss, or draw), then does more random playouts.
void MonteCarlo::randomPlayout(Board board, int* tally)
{   
    // Seed random number generator for randomMove()
    srand(time(0));

    for (int i = 0; i < MAX_MOVES; i++)
    {
        // Clone the current board
        Board copy = board;

        while (true)
        {
            copy.changeTurn();

            // Quit if there are no legal moves remaining
            if (randomMove(copy) == -1)
            {
                break;
            }

            // Make a random move
            copy.makeMove(randomMove(copy));

            // If the AI wins, add 1 to the wins tally
            if (copy.winner() == 0)
            {
                tally[0]++;
                break;
            }

            // If the player wins, add 1 to the losses tally
            else if (copy.winner() == 1)
            {
                tally[1]++;
                break;
            }

            // If the game ties, add 1 to the draws tally
            else if (copy.winner() == -1)
            {
                tally[2]++;
                break;
            }
        }
    }
}

// Returns a random legal move
int MonteCarlo::randomMove(Board board)
{
    std::vector<int> legal_moves;

    // Get legal moves
    for(int i = 0; i < 7; i++)
    {
        if(board.columns[i] >= 0)
        {
            legal_moves.push_back(i);
        }
    }

    // Return -1 if there are no moves left
    if(legal_moves.size() == 0)
    {
        return -1;
    }

    // Otherwise, return a random legal move
    int x = (rand() % legal_moves.size());
    
    return legal_moves[x];
}

#endif