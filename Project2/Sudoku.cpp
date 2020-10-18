#include"Sudoku.h"

Sudoku::Sudoku(){
	for(int i=0; i<sudokuSize; ++i)
		map[i] = 0;
}
Sudoku::Sudoku(const int init_map[]){
	for(int i=0; i<sudokuSize; ++i)
		map[i] = init_map[i];
}
void Sudoku::setMap(const int set_map[]){
	for(int i=0; i<sudokuSize; ++i)
		map[i] = set_map[i];
}
int Sudoku::getNumber(const int index){
	return map[index];
}
void Sudoku::setNumber(int index, int value){
	map[index] = value;
}
int Sudoku::getZeros_index(){
	for(int i=0; i<sudokuSize; ++i)
		if(map[i] == 0)
			return i;
	return -1;
}
bool Sudoku::fortyfive_rule(const int *numbers){
	int sum = 0;

	for(int i=0; i<9; ++i)
		sum += numbers[i];
	if(sum == 45)
		return true;
	return false;
}
bool Sudoku::check_answer(){
	int numbers[9], cell;
	bool result;
	for(int i=0; i<81; i+=9){ // check rows
		for(int j=0; j<9; ++j)
			numbers[j] = map[i+j];
		result = fortyfive_rule(numbers);
		if(result == false)
			return false;
	}
	for(int i=0; i<9; ++i){ // check columns
		for(int j=0; j<9; ++j)
			numbers[j] = map[i+9*j];
		result = fortyfive_rule(numbers);
		if(result == false)
			return false;
	}
	for(int i=0; i<9; ++i){ // check cells
		for(int j=0; j<9; ++j){
			cell = 27*(i/3) + 3*(i%3) + 9*(j/3) + (j%3);
			numbers[j] = map[cell];
		}
		result = fortyfive_rule(numbers);
		if(result == false)
			return false;
	}
	return true;
}

void Sudoku::setPossibles(int index){
	int rro, rco;
	int rce, x, y, xx, yy;
	poss_num = 0;
	for(int i=0; i<9; ++i){ //initialize possibles
		possibles[i] = 0;
		chooses[i] = 0;
	}
	
	rro = 9*(index/9);
	for(int i=0;  i<9; ++i) // record rows
    	if(map[rro+i] != 0)
           	++possibles[map[rro+i]-1];

    rco = index%9;
	for(int i=0; i<81; i+=9) // record columns
     	if(map[rco+i] != 0)
			++possibles[map[rco+i]-1];
    
	x = index%9; // set cells
	y = index/9;
	xx = x/3;
	yy = y/3;
	rce = xx*3 + yy*27;
	   	 
	for(int i=0; i<27; i+=9) // record cells
		for(int j=0; j<3; ++j)
	 		if(map[rce+i+j] != 0)
				++possibles[map[rce+i+j]-1];
	int k = 0;
	for(int i=0; i<9; ++i) // find possibles
		if(possibles[i] == 0){
			++poss_num;
			chooses[k] = i + 1;
			k++;
		}
}
