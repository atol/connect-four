#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;

class Board
{
friend class MonteCarlo; // Allow MonteCarlo class to access private members
private:
    // 6x7 2D array representing the current state of the board
    int state[6][7];
    // Array of columns containing the height of the column (filled column)
    int columns[7];
public:
    // Whose turn it is. Player = 1, AI = 0
    int turn;
    
    // Default constructor
    Board();
    // Default destructor
    ~Board();
    
    void display();
    void getTurn();
    void makeMove(int move);
    void nextState(int row, int col, int val);
    void changeTurn();
    void legalMoves(int col);
    int getMove();
    int winner();
    bool checkWinner();  
};

// Constructor
Board::Board()
{
    // Initialize board values to -1
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            state[i][j] = -1;
        }
    }

    // Initialize column depths to the last row (empty)
    for (int i = 0; i < 7; i++)
    {
        columns[i] = 5;
    }

    getTurn();
}

// Deconstructor
Board::~Board()
{
}

// Decide who goes first
void Board::getTurn()
{
    // Initialize random seed
    srand(time(NULL));

    // Randomly generate 0 or 1
    int n = rand() % 2;

    // If the number is 1, player goes first
    if (n == 1)
    {
        turn = 1;
    }

    // Otherwise, AI goes first
    else
    {
        turn = 0;
    }
}

// Get a move from the player
int Board::getMove()
{   
    bool valid_input = false;
    int move;

    while (!valid_input)
    {
        cout << "Make your move (1-7): ";
        cin >> move;

        // If input is not an integer, output an error message
        if(cin.fail())
        {
            cout << "Invalid input. Please pick a column from 1 to 7.\n";
            // Clear error flag on cin
            cin.clear();
            // Ignore the rest of the current line (skip to next newline)
            // to avoid another parse failure
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // If input is out of range, output an error message
        if (move < 1 || move > 7)
        {
            cout << "Please pick a column from 1 to 7.\n";
            continue;
        }
        
        // If column is full, output an error message
        if(state[0][move-1] != -1)
        {
            cout << "That column is full. Please pick another column.\n";
            continue;
        }
        
        move -= 1; // Offset because board starts at column 1
        valid_input = true;
    }
    
    return move;
}

// Make a move on the board (mark board and update legal moves)
void Board::makeMove(int move)
{
    int col = move;
    int row = columns[col];
    int val = turn;

    nextState(row, col, val);
    legalMoves(col);
}

// Update the state of the board
void Board::nextState(int row, int col, int val)
{
    state[row][col] = val;
}

// Change turn of player.
// Should be called everytime nextState() is called
void Board::changeTurn()
{
    turn = !turn;
}

// Update the columns variable (i.e. valid columns to place a move).
// Should be called everytime nextState() is called
void Board::legalMoves(int col)
{
    columns[col] -= 1;
}

// Takes the current state of the board, and returns:
//  1: Player has won
//  0: AI has won
//  -1: Draw
//  2: Game still playing
int Board::winner()
{
    // Check for winner
    if (checkWinner() == true)
    {
        // Player has won
        if (turn == 1)
        {
            return 1;
        }
        
        // AI has won
        else
        {
            return 0;
        }
    }

    // Check for draw
    for (int i = 0; i < 7; i++)
    {
        // If columns are not all full, continue playing game
        if(columns[i] != -1)
        {
            return 2;
        }
    }

    return -1;
}

// Returns true if the current state of the board results in a winner
bool Board::checkWinner()
{
    // Check for horizontal win
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (state[row][col] == turn && state[row][col+1] == turn && state[row][col+2] == turn && state[row][col+3] == turn)
            {
                return true;
            }
        }
    }

    // Check for vertical win
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            if (state[row][col] == turn && state[row+1][col] == turn && state[row+2][col] == turn && state[row+3][col] == turn)
            {
                return true;
            }
        }
    }

    // Check for diagonal win
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (state[row][col] == turn && state[row+1][col+1] == turn && state[row+2][col+2] == turn && state[row+3][col+3] == turn)
            {
                return true;
            }
        }
    }

    // Check for antidiagonal win
    for (int row = 3; row < 6; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (state[row][col] == turn && state[row-1][col+1] == turn && state[row-2][col+2] == turn && state[row-3][col+3] == turn)
            {
                return true;
            }
        }
    }

    return false;
}

// Displays the board to the console
void Board::display()
{
    for (int i = 0; i < 7; i++)
    {
        cout << "   " << i + 1 << "  ";
    }

    cout << endl;
    
    for (int i = 0; i < 7; i++)
    {
        if ((i + 1) % 7 != 0)
        {
            cout << "|-----";
        }

        else
        {
            cout << "|-----|";
        }
    }

    cout << endl;
    
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((j + 1) % 7 != 0)
            {
                if (state[i][j] == -1)
                {
                    cout << "|     ";
                }

                else
                {
                    if(state[i][j] == 1)
                    {
                        cout << "|  X  ";
                    }
                    
                    else
                    {
                        cout << "|  O  ";
                    }
                }
            }

            else
            {
                if (state[i][j] == -1)
                {
                    cout << "|     |\n";
                }

                else
                {
                    if(state[i][j] == 1)
                    {
                        cout << "|  X  |\n";
                    }
                    
                    else
                    {
                        cout << "|  O  |\n";
                    }
                }
            }
        }

        for (int j = 0; j < 7; j++)
        {
            if ((j + 1) % 7 != 0)
            {
                cout << "|-----";
            }

            else
            {
                cout << "|-----|";
            }
        }

        cout << endl;
    }
}

#endif