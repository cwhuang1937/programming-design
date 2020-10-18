#include<iostream>
#include<vector>
using namespace std;

class Sudoku{
public:
	Sudoku();
	Sudoku(const int init_map[]);
	void setMap(const int set_map[]);
	int getNumber(const int index);
    bool check_answer(); // Validaoter
	static const int sudokuSize = 81; // the size of map
	void setNumber(int index, int value);
	int  getZeros_index();
	void setPossibles(int index);
	int possibles[9];
	int poss_num;
	int chooses[9];

private:
	bool fortyfive_rule(const int *number);
	int map[sudokuSize];
};
