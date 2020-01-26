#include "board.hpp"
#include "mcts.hpp"
#include <stdlib.h>

using std::cout;
using std::endl;

int main(void)
{
    // Create new board and MCTS objects
    Board board;
    MonteCarlo mcts;

    // Display blank board if player's turn
    if(board.turn == 0)
    {
        board.display();
        cout << endl;
    }

    // While the game is still active (no winner, no draw)
    while (board.winner() == 2)
    {
        board.changeTurn();

        // If player's turn
        if(board.turn == 1)
        {
            // Ask for a legal move as input
            int playerMove = board.getMove();
            // Update board
            board.makeMove(playerMove);
            // Display board
            board.display();
            cout << endl;
        }

        // Else if AI's turn
        else
        {
            // Run simulation
            int aiMove = mcts.pMCTS(board);
            // Update board
            board.makeMove(aiMove);
            // Display board
            cout << "AI makes its move: " << (aiMove + 1) << endl;
            board.display();
            cout << endl;
        }
    }
    
    // Display results
    if (board.winner() == 1)
    {
        cout << "Connect 4: Player wins!" << endl;
    }

    else if(board.winner() == 0)
    {
        cout << "Connect 4: AI wins!" << endl;
    }

    else
    {
        cout << "It's a draw!" << endl;
    }
    return EXIT_SUCCESS;
}