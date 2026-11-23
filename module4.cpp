#include <iostream>
using namespace std;

// Display Game Board
void displayBoard(char board[3][3])
{
    cout << "\n";

    cout << " " << board[0][0] << " | "
         << board[0][1] << " | "
         << board[0][2] << endl;

    cout << "---|---|---\n";

    cout << " " << board[1][0] << " | "
         << board[1][1] << " | "
         << board[1][2] << endl;

    cout << "---|---|---\n";

    cout << " " << board[2][0] << " | "
         << board[2][1] << " | "
         << board[2][2] << endl;

    cout << "\n";
}

// Check Winner
bool checkWinner(char board[3][3], char player)
{
    // Check Rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return true;
        }
    }

    // Check Columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == player &&
            board[1][i] == player &&
            board[2][i] == player)
        {
            return true;
        }
    }

    // Check Diagonals
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
    {
        return true;
    }

    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
    {
        return true;
    }

    return false;
}

// Main Game Function
void playGame()
{
    char board[3][3] =
    {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char currentPlayer = 'X';
    int position;
    int row, col;
    int moves = 0;

    cout << "\n===== TIC TAC TOE GAME =====\n";

    while (moves < 9)
    {
        displayBoard(board);

        cout << "Player " << currentPlayer;
        cout << ", enter position (1-9): ";
        cin >> position;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid input! Enter a number.\n";
            continue;
        }

        if (position < 1 || position > 9)
        {
            cout << "\nInvalid position! Try again.\n";
            continue;
        }

        row = (position - 1) / 3;
        col = (position - 1) % 3;

        if (board[row][col] == 'X' ||
            board[row][col] == 'O')
        {
            cout << "\nPosition already occupied! Try again.\n";
            continue;
        }

        board[row][col] = currentPlayer;
        moves++;

        if (checkWinner(board, currentPlayer))
        {
            displayBoard(board);

            cout << "Player " << currentPlayer;
            cout << " Wins!\n";

            return;
        }

        if (currentPlayer == 'X')
        {
            currentPlayer = 'O';
        }
        else
        {
            currentPlayer = 'X';
        }
    }

    displayBoard(board);

    cout << "Game Draw!\n";
}

// Main Function
int main()
{
    char replay;

    do
    {
        playGame();

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> replay;

    } while (replay == 'Y' || replay == 'y');

    cout << "\nThank You for Playing!\n";

    return 0;
}