#include<iostream>
#include<fstream>
#include <windows.h>
#include<string>
using namespace std;
void displayMenu(void);
char selectOption(void);
char modeSelect(void);
void readMaze(int rowColumn, char** maze, string boardName);
void displayMaze(int rowColumn, char** maze);
void gamePlay(char** maze, int rowColumn, int moves, int lives, int xValue, int yValue);
bool blockageCheck(char** maze, int xValue, int yValue); bool monsterCheck(char** maze, int xValue, int yValue);
bool CheckLastColumn(int rowcolumn, int yValue);
bool gameEnd(int moves, int lives);
void saveGame(int lives, int moves, char** maze, int rowColumn, int xValue, int yValue);
int countLinesInFile(string fileName);
void readPausedSaved(int& lives, int rowColumn, int& moves, char** maze, int& yValue, int& xValue);
int main() {
	char selection;
	int rowColumn = 0;
	int moves;
	int xValue = 0, yValue = 0;
	char** maze;
	while (true) 
	{
		displayMenu();
		selection = selectOption();
		if (selection == '1')
		{
			char modeSelection = modeSelect();
			system("CLS");
			if (modeSelection == 'e' || modeSelection == 'E')
			{
				rowColumn = 4;
				maze = new char* [rowColumn];
				for (int i = 0; i < rowColumn; i++)
				{
					maze[i] = new char[rowColumn];
				}
				string boardName = "TableEasy.txt";
				readMaze(rowColumn, maze, boardName);
				displayMaze(rowColumn, maze);
				moves = 10;
				lives = 3;
				gamePlay(maze, rowColumn, moves, lives, xValue, yValue);
				system("pause");
			}
			else if (modeSelection == 'm' || modeSelection == 'M')
			{
				rowColumn = 6;
				maze = new char* [rowColumn];
				for (int i = 0; i < rowColumn; i++)
				{
					maze[i] = new char[rowColumn];
				}
				string boardName = "TableMedium.txt";
				readMaze(rowColumn, maze, boardName);
				displayMaze(rowColumn, maze);
				moves = 8;
				lives = 2;
				gamePlay(maze, rowColumn, moves, lives, xValue, yValue);
				system("pause");
			}
			else {
				rowColumn = 8;
				maze = new char* [rowColumn];
				for (int i = 0; i < rowColumn; i++)
				{
					maze[i] = new char[rowColumn];
				}
				string boardName = "TableHard.txt";
				readMaze(rowColumn, maze, boardName);
				displayMaze(rowColumn, maze);
				moves = 12;
				lives = 1;
				gamePlay(maze, rowColumn, moves, lives, xValue, yValue);
				system("pause");
			}
		}
		else if (selection == '2')
		{
			rowColumn = countLinesInFile("pauseGame.txt");
			if (rowColumn > 1)
			{
				rowColumn -= 5;
				maze = new char* [rowColumn];
				for (int i = 0; i < rowColumn; i++)
					maze[i] = new char[rowColumn];

				gamePlay(maze, rowColumn, xValue, yValue, moves);
			}
			else {
				cout << "There is no Unfinished Game\n";
			}
		}
		else {
			break;
		}
	}
	return 0;
}
char selectOption(void) {
	char a;
	cout << "Your Selection: ";
	while (true) {
		cin >> a;
		if (a == '1' || a == '2' || a == '3') {
			break;
		}
		cout << "Invalid Input!!!" << endl;
		cout << "Try Again: ";
	}
	return a;
}
void displayMaze(int rowColumn, char** maze) {
	for (int i = 0; i < rowColumn; i++)
	{
		for (int j = 0; j < rowColumn; j++) {
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
}
void gamePlay(char** maze, int rowColumn, int moves, int xValue, int yValue) {
	char playerMove;
	bool winValidation = false;
	while (!gameEnd(moves))
	{
		system("CLS");
		displayMaze(rowColumn, maze);
		cout << "w/W to mover up" << endl;
		cout << "s/S to mover Down" << endl;
		cout << "a/A to mover left" << endl;
		cout << "d/D to mover right" << endl;
		cin >> playerMove;
		if (playerMove == 'a' || playerMove == 'A') {
			if (yValue - 1 < 0)
			{
				cout << "You can't move further Left\n";
				continue;
			}
			else if (blockageCheck(maze, xValue, yValue - 1))
				cout << "You cant cross Blockage\n";
			else
			{
				yValue = yValue - 1;
				maze[xValue][yValue] = '1';
				moves--;
			}
		}
		else if (playerMove == 's' || playerMove == 'S') {
			if (xValue + 1 == rowColumn)
			{
				cout << "You can't move further Down\n";
				continue;
			}
			else if (blockageCheck(maze, xValue + 1, yValue)) {
				cout << "You cant cross Blockage\n";
			}
			else
			{
				xValue++;
				maze[xValue][yValue] = '1';
				moves--;
			}
		}
		else if (playerMove == 'w' || playerMove == 'W') {
			if (xValue - 1 < 0)
			{
				cout << "You can't move further Up\n";
				continue;
			}
			else if (blockageCheck(maze, xValue - 1, yValue))
				cout << "You cant cross Blockage\n";
			else
			{
				xValue--;
				maze[xValue][yValue] = '1';
				moves--;
			}
		}
		else if (playerMove == 'd' || playerMove == 'D')
		{
			if (blockageCheck(maze, xValue, yValue + 1))
				cout << "You cant cross Blockage\n";
			else
			{
				yValue = yValue + 1;
				maze[xValue][yValue] = '1';
				moves--;
			}
			if (CheckLastColumn(rowColumn, yValue))
			{
				winValidation = true;
				break;
			}
		}
	}
	Sleep(1000);
	if (winValidation) {
		cout << endl << "Congratulation!!!" << endl;
		cout << "You won the game!!!" << endl;
	}

}
bool blockageCheck(char** maze, int xValue, int yValue)
{
	if (maze[xValue][yValue] == '|')
		return true;
	return false;

}
bool CheckLastColumn(int rowcolumn, int yValue)
{
	if (yValue == rowcolumn - 1) {
		return true;
	}
	else {
		return false;
	}
}
bool gameEnd(int moves, int lives)
{
	cout << endl << "Moves Left : " << moves << "\nLives Left : " << lives << endl;
	bool over = false;
	if (moves == 0)
	{
		cout << "You are out of move\n";
		over = true;
	}
	else if (lives == 0)
	{
		cout << "You are out of Lives\n";
		over = true;
	}
	return over;
}
