#include <iostream>
#include <string>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);
	
	while (true) {
		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);
		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}
	
	return 0;
}

bool isWon(char xo, char board[][3])
{
	int winRow = 0;
	int winCol = 0;
	int winDiag = 0;
	int winAntiDiag = 0;
	bool winCond = false;
	for (int dim1 = 0; dim1 < sizeof(board[0]) / sizeof(char); dim1++)
	{
		for (int dim2 = 0; dim2 < sizeof(board[0]) / sizeof(char); dim2++)
		{
			//check rows
			if (board[dim1][dim2] == xo)
			{
				winRow++;
			}
			//check cols
			if (board[dim2][dim1] == xo)
			{
				winCol++;
			}
		}
		if (winRow == 3 || winCol == 3)
		{
			winCond = true;
		}
		else
		{
			winRow = 0;
			winCol = 0;
		}
	}
	//check diagonals
	for (int dim = 0; dim < sizeof(board[0]) / sizeof(char); dim++)
	{
		if (board[dim][dim] == xo)
		{
			winDiag++;
		}
		if (board[(sizeof(board[0]) / sizeof(char)) - dim - 1][dim] == xo)
		{
			winAntiDiag++;
		}
		if (winAntiDiag == 3 || winDiag == 3)
		{
			winCond = true;
		}
	}
	return winCond;
}

bool isDraw(char board[][3])
{
	bool boardFilled = true;
	for (int row = 0; row < sizeof(board[0]) / sizeof(char); row++)
	{
		for (int col = 0; col < sizeof(board[0]) / sizeof(char); col++)
		{
			if (board[row][col] == ' ')
			{
				boardFilled = false;
			}
		}
	}
	return boardFilled;
}

void displayBoard(char board[][3])
{
	cout << "-------------" << endl;
	//assume the number of rows = number of cols
	for (int row = 0; row < sizeof(board[0]) / sizeof(char); row++)
	{
		cout << "| ";
		for (int col = 0; col < sizeof(board[0]) / sizeof(char); col++)
		{
			cout << board[row][col] << " | ";
		}
		cout << endl;
		cout << "-------------" << endl;
	}
}

void makeAMove(char board[][3], char xo)
{
	bool makingMove = true;
	while (makingMove) {
		int row;
		int col;
		string promptRow = string("Enter a row (0, 1, 2) for player ") + xo + "   : ";
		cout << promptRow;
		cin >> row;
		while (cin.fail() || row < 0 || row > 2)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << promptRow;
			cin >> row;
		}
		string promptCol = string("Enter a column (0, 1, 2) for player ") + xo + ": ";
		cout << promptCol;
		cin >> col;
		while (cin.fail() || col < 0 || col > 2)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << promptCol;
			cin >> col;
		}
		if (board[row][col] == 'X' or board[row][col] == 'O')
		{
			cout << "This cell is already occupied. Try a different cell" << endl;
		}
		else
		{
			board[row][col] = xo;
			makingMove = false;
		}
	}
}
