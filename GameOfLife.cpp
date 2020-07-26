/*Conway's Game of Life rules:
1) live cell with 2 or 3 live neighbors survives
2) dead cell with 3 live neighbors becomes alive
3) all other cells remain in an unchanged state
(Wikipedia) CAUTION: program's behavior at the boundaries is not determined*/

#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;
constexpr int GS = 20; //short for Grid Size - set initially to 20
void prt(int t[][GS]) //printing the grid
{
	for (int y = 0; y < GS; y++)
	{
		for (int x = 0; x < GS; x++)
		{
			if (x == 0)
			{
				cout << t[y][x] << "\t";
			}
			if (x >= 1 && x < 9)
			{
				cout << t[y][x] << "  ";
			}
			if (x >= 9 && y == 0)
			{
				cout << t[y][x] << " ";
			}
			if (x >= 9 && y != 0)
			{
				cout << t[y][x] << "  ";
			}
		}
		cout << "\n";
	}
}
void init(int t[][GS]) //initializing the grid
{
	t[0][0] = 0;
	for (int x = 1; x < GS; x++) //labeling the grid
	{
		t[0][x] = x;
	}
	for (int y = 1; y < GS; y++) //labeling the grid
	{
		t[y][0] = y;
	}
	for (int y = 1; y < GS; y++) //initialize it with zeros
	{
		for (int x = 1; x < GS; x++)
		{
			t[y][x] = 0;
		}
	}
}
int neighbors(int t[][GS], int x, int y) //x and y indicate the pos. of current elem.
{
	int neighbor_cnt = 0;
	if (t[y - 1][x] == 1) neighbor_cnt++;
	if (t[y - 1][x + 1] == 1) neighbor_cnt++;
	if (t[y][x + 1] == 1) neighbor_cnt++;
	if (t[y + 1][x + 1] == 1) neighbor_cnt++;
	if (t[y + 1][x] == 1) neighbor_cnt++;
	if (t[y + 1][x - 1] == 1) neighbor_cnt++;
	if (t[y][x - 1] == 1) neighbor_cnt++;
	if (t[y - 1][x - 1] == 1) neighbor_cnt++;
	return neighbor_cnt;
}
void fate(int t[][GS], int neighbor_cnt, int x, int y)
{
	if (t[y][x] == 1) //if it's live, then...
	{
		if (neighbor_cnt < 2) t[y][x] = 0;
		if (neighbor_cnt == 2 || neighbor_cnt == 3) t[y][x] = 1;
		if (neighbor_cnt > 3) t[y][x] = 0;
	}
	if (t[y][x] == 0) //if it's dead, then...
	{
		if (neighbor_cnt == 3) t[y][x] = 1;
	}
}


int main()
{
	int grid[GS][GS]; //create a grid ((GS-1)x(GS-1) with one extra row and column)
	init(grid);
	cout << "*****Welcome to C++ implementation of Conway's Game of Life!*****\n";
	cout << "Live cells are marked by X\n";
	cout << "How many alive cells initially?\n";
	cout << "HINT: 97 activates a Glider!\n";
	int number_init = 0;
	cin >> number_init;
	int x_pos, y_pos;
	switch (number_init)
	{
	case 97: //little cheat :)
		cout << "This is Glider!\n";
		grid[5][6] = 1;
		grid[6][7] = 1;
		grid[7][7] = 1;
		grid[7][6] = 1;
		grid[7][5] = 1;
		break;
	default:
		for (int i = 0; i < number_init; i++)
		{
			cout << "Enter the coordinates of live cell no. " << i + 1 << "\n";
			cout << "vertical (x), ENTER, horizonatal (y)\n";
			cin >> x_pos >> y_pos;
			grid[y_pos][x_pos] = 1;
		}
		break;
	}
	cout << "\n\nInitial state\n";
	prt(grid);
	Sleep(4000);
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
