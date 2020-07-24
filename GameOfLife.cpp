/*Conway's Game of Life rules:
1) live cell with 2 or 3 live neighbors survives
2) dead cell with 3 live neighbors becomes alive
3) all other cells remain in an unchanged state
(Wikipedia) CAUTION: program's behavior at the boundaries is not determined*/

#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;
constexpr int GS = 20; //short for Grid Size - set initially to 11
void prt(char t[][GS]) //printing the grid
{
	for (int y = 0; y < GS; y++)
	{
		for (int x = 0; x < GS; x++)
		{
			cout << t[y][x];
		}
		cout << "\n";
	}
}

void init(char t[][GS]) //initializing the grid
{
	t[0][0] = '#';
	char one = 49;
	for (int x = 1; x < GS; x++)
	{
		t[0][x] = one++;
	}
	one = 49;
	for (int y = 1; y < GS; y++)
	{
		t[y][0] = one++;
	}
	for (int y = 1; y < GS; y++)
	{
		for (int x = 1; x < GS; x++)
		{
			t[y][x] = '.';
		}
	}
}
//this function does NOT chceck for grid boundaries!!!!
int neighbors(char t[][GS], int x, int y) //x and y indicate the pos. of current elem.
{
	int neighbor_cnt = 0;
	if (t[y - 1][x] == 'X') neighbor_cnt++;
	if (t[y - 1][x + 1] == 'X') neighbor_cnt++;
	if (t[y][x + 1] == 'X') neighbor_cnt++;
	if (t[y + 1][x + 1] == 'X') neighbor_cnt++;
	if (t[y + 1][x] == 'X') neighbor_cnt++;
	if (t[y + 1][x - 1] == 'X') neighbor_cnt++;
	if (t[y][x - 1] == 'X') neighbor_cnt++;
	if (t[y - 1][x - 1] == 'X') neighbor_cnt++;
	return neighbor_cnt;
}
void fate(char t[][GS], int neighbor_cnt, int x, int y)
{
	if (t[y][x] == 'X') //if it's live, then...
	{
		if (neighbor_cnt < 2) t[y][x] = '.';
		if (neighbor_cnt == 2 || neighbor_cnt == 3) t[y][x] = 'X';
		if (neighbor_cnt > 3) t[y][x] = '.';
	}
	if (t[y][x] == '.') //if it's dead, then...
	{
		if (neighbor_cnt == 3) t[y][x] = 'X';
	}
}
int main()
{
	char grid[GS][GS]; //create a grid ((GS-1)x(GS-1) with one extra row and column)
	init(grid);
	cout << "*****Welcome to C++ implementation of Conway's Game of Life!*****\n";
	cout << "Live cells are marked by X\n";
	cout << "How many alive cells initially?\n";
	int number_init = 0;
	cin >> number_init;
	int x_pos, y_pos;
	for (int i = 0; i < number_init; i++)
	{
		cout << "Enter the coordinates of live cell no. " << i + 1 << "\n";
		cout << "vertical (x), horizonatal (y) - separated by space\n";
		cin >> x_pos >> y_pos;
		grid[y_pos][x_pos] = 'X';
	}
	cout << "\n\nInitial state\n";
	prt(grid);
	Sleep(3000);
	system("cls");
	cout << "\nHow many iterations?\n";
	int iterations = 0;
	cin >> iterations;
	for (int n = 0; n < iterations; n++)
	{
		system("cls");
		int neighbors_distribution[GS][GS];
		for (int y = 3; y < GS; y++)
		{
			for (int x = 3; x < GS; x++)
			{
				neighbors_distribution[y][x] = neighbors(grid, x, y);
			}
		}
		for (int y = 3; y < GS; y++)
		{
			for (int x = 3; x < GS; x++)
			{
				fate(grid, neighbors_distribution[y][x], x, y);
			}
		}
		cout << "\nAfter iteration no. " << n + 1 << "\n";
		prt(grid);
		Sleep(500);
	}
}
