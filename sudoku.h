//Austin Ahne
//Project 3, Data Structures - Doderer

#include <iostream>
using namespace std;

class sudoku 
{
public:
	sudoku();
	void print();
	void solve();
private:
	int grid[9][9];

	bool solveRecur(int r, int c);
	void printRecur(int r, int c);
	bool checkRow(int r, int c, int i);
	bool checkCol(int r, int c, int i);
	bool checkSquare(int r, int c, int i, int sr, int sc);
	int squareRow(int r);
	int squareCol(int c);
	bool findEmpty(int &r, int &c);
	bool checkElement(int r, int c, int i);
};

sudoku::sudoku() //loads sudokuArray into grid
{							/* 0  1  2    3  4  5    6  7  8 */
	int sudokuArray[] = /*0*/{ 5, 3, 0,	  0, 7, 0,   0, 0, 0,
						/*1*/  6, 0, 0,	  1, 9, 5,   0, 0, 0,
						/*2*/  0, 9, 8,	  0, 0, 0,   0, 6, 0,
//
						/*3*/  8, 0, 0,	  0, 6, 0,   0, 0, 3,
						/*4*/  4, 0, 0,	  8, 0, 3,   0, 0, 1,
						/*5*/  7, 0, 0,	  0, 2, 0,   0, 0, 6,
//
						/*6*/  0, 6, 0,	  0, 0, 0,   2, 8, 0,
						/*7*/  0, 0, 0,   4, 1, 9,   0, 0, 5,
						/*8*/  0, 0, 0,   0, 8, 0,   0, 7, 9	};
	int sudokuCounter = 0;
	for(int r=0; r<9; r++)
	{
		for(int c=0; c<9; c++)
		{
			grid[r][c]=sudokuArray[sudokuCounter];
			sudokuCounter++;
		}	
	}
}

bool sudoku::findEmpty(int &r, int &c)
{
	for(int r=0; r<9; r++)
		for(int c=0; c<9; c++)
			if(grid[r][c]==0)
			{

				return false;
			}
	return true;
}

bool sudoku::checkRow(int r, int c, int i)
{
	//cout << "-In checkRow-" << endl;
	//cout << "Row: " << r << "	Column: " << c << "	i: " << i << endl;
	for(int c=0; c<9; c++)
		if(grid[r][c]==i)
			return false;
	return true;
	//if(c>8)				//if you reach the end of the row and the number you're checking for isn't there
	//{
	//	cout << "c>8 == true" << endl;
	//	//checkCol(r,c,i);	//or call checkCol
	//	return true;
	//}
	//if(grid[r][c]==i)	//if current element is the same as the one you're checking
	//	return false;
	//else
	//	return checkRow(r,c+1,i);	//else, check the next element in the row
}

bool sudoku::checkCol(int r, int c, int i) 
{
	//cout << "-In checkCol-" << endl;
	//cout << "Row: " << r << "	Column: " << c << "	i: " << i << endl;
	for(int r=0; r<9; r++)
		if(grid[r][c]==i)
			return false;
	return true;
	//if(r>8)
	//{
	//	return true;
	//}
	//if(grid[r][c]==i)
	//	return false;
	//return checkCol(r+1,c,i);
}

//int sudoku::squareRow(int r)
//{
//	if(r<3)
//		return 0;
//	if(r<6)
//		return 3;
//	return 6;
//}
//
//int sudoku::squareCol(int c)
//{
//	if(c<3)
//		return 0;
//	if(c<6)
//		return 3;
//	return 6;
//}

bool sudoku::checkSquare(int r, int c, int i, int sr, int sc) 
{
	//cout << "-In checkSquare-" << endl;
	//cout << "Row: " << r << "	Column: " << c << "	i: " << i << endl;

	for(int row=0; row<3; row++)
		for(int col=0; col<3; col++)
			if(grid[row+sr][col+sc]==i)
				return false;
	return true;

	//if(r>=sr+2 && c>sc+2)			//checked the whole square, no conflicts
	//{
	//	return true; //square is valid
	//}
	//if(c>sc+2)
	//{
	//	return checkSquare(r+1,sc,i,sr,sc);//move to next row,first column
	//}
	//if(grid[r][c]==i)
	//	return false;
	//checkSquare(r,c+1,i,sr,sc);
}

bool sudoku::checkElement(int r, int c, int i)
{
	//if(checkRow(r,c,i))
	//	if(checkCol(r,c,i))
	//		if(checkSquare(r,c,i,r-r%3,c-c%3))
	//			return true;
	//return false;
	return checkRow(r,c,i) &&
		   checkCol(r,c,i) &&
		   checkSquare(r, c, i, r-(r%3), c-(c%3)); //took me forever to figure out what to pass and how to pass it
}
void sudoku::printRecur(int r, int c) 
{
	if (r >= 9)
		return;
	if (c >= 9) {
		cout << endl;
		printRecur(r + 1, 0);
		return;
	}
	cout << grid[r][c] << " ";
	printRecur(r, c + 1);
}

void sudoku::print()
{
	printRecur(0, 0);
	cout << endl;
	cout << endl;
}

bool sudoku::solveRecur(int r, int c) //might try passing i
{	
	//int sr, sc;						//used in checkSquare
	//int tempr, tempc;				//^

	if(findEmpty(r,c))
		return true;

	if(r>8)
		return solveRecur(0,0);		//go back to beginning(solveRecur(0,0))/puzzle solved(return true)
	if(c>8)							//if at end of row
		return solveRecur(r+1,0);
	//cout << "Number at Coordinates: " << grid[r][c] << endl;
	if(grid[r][c]!=0)				//if element != 0, move to next element
		return solveRecur(r,c+1);

	for(int i=1; i<=9; i++)
	{
		//cout << "-In the for loop in solveRecur-" << endl;
		//cout << "Row: " << r << "	Column: " << c << "	i: " << i << endl;
		if(checkElement(r,c,i))
		{
			grid[r][c]=i;			//inserts number

			if(solveRecur(r,c))
				return true;

			grid[r][c]=0;	//failed, reset and retry
		}
	}
	return false;//backtracks

		//sr = squareRow(r);		//makes sr/sc = the top-left r/c of current square
		//sc = squareCol(c);		//used in checkSquare
		//tempr = sr;				//^
		//tempc = sc;

		//if(checkRow(r,0,i))
		//{
		//	if(checkCol(0,c,i))
		//	{
		//		if(checkSquare(tempr,tempc,i,sr,sc))
		//		{
		//			grid[r][c]=i;			//inserts number
		//			if(solveRecur(r,c))
		//				return true;
		//			grid[r][c]=0;	//failed, reset and retry
		//		}
		//		grid[r][c]=0;
		//	}
		//	grid[r][c]=0;
		//}
		//grid[r][c]=0;
	//}
	//return false;
}

void sudoku::solve()
{
	if (solveRecur(0, 0)) 
	{
		cout << "The solution is: " << endl;
		print();
	}
	else 
	{
		cout << "no solution was determined" << endl;
	}
}
