#include <vector>
#include <iostream>
#include <set>
#include <unordered_set>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;
void sudokuPrint(vector<vector<int>>& sudokuBoard) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << sudokuBoard[i][j]<< " ";
		}
		cout << endl;
	}
	cout << endl;
}
bool fullBoardCheck(int y, int x, int num, vector<vector<int>>& sudokuBoard, vector<vector<unordered_set<int>>>& solStrg) {
	if (solStrg[y][x].find(num) != solStrg[y][x].end()) { return true; }
	return false; 
}
void updateSolutionStrg(int y, int x, vector<vector<int>>& sudokuBoard, vector<vector<unordered_set<int>>>& solStrg) {
	
	for (int i = 0; i < 9; i++) {
		if ((i != y)&&(sudokuBoard[i][x] != 0)) { solStrg[y][x].insert(sudokuBoard[i][x]); }
	}
	for (int j = 0; j < 9; j++) {
		if ((j != x)&&(sudokuBoard[y][j] != 0)) { solStrg[y][x].insert(sudokuBoard[y][j]); }
	}
	int divisionY = y / 3;
	int divisionX = x / 3;
	for (int i = divisionY * 3; i < divisionY * 3 + 3; i++) {
		for (int j = divisionX * 3; j < divisionX * 3 + 3; j++) {
			if ((i != y)&&(j != x)&&(sudokuBoard[i][j] != 0)) { solStrg[y][x].insert(sudokuBoard[i][j]); }
		}
	}

	
}

unordered_set<int> getSolutions(int y, int x, vector<vector<unordered_set<int>>>& solStrg) {
	unordered_set<int> result;
	unordered_set<int> repeat;
	while (repeat.size() < 9) {
		int num = rand() % 9 + 1;
		repeat.insert(num);
		if (solStrg[y][x].find(num) == solStrg[y][x].end()) { result.insert(num); }
	}
	return result;
}

void genNumFillY(int y, int x, vector<vector<int>>& sudokuBoard, vector<vector<unordered_set<int>>>& solStrg, bool& filled, int& iteration) {

	if (x <= 8) {
		if (solStrg[y][x].empty()) { updateSolutionStrg(y, x, sudokuBoard, solStrg); }
		unordered_set<int> solutions = getSolutions(y, x, solStrg);
		for (int num : solutions) {
			if (!filled) {
				solStrg[y][x].insert(num);
				sudokuBoard[y][x] = num;
				system("cls");
				iteration++;
				sudokuPrint(sudokuBoard);
				/*std::this_thread::sleep_for(std::chrono::milliseconds(10));*/
				if (y >= 8) { genNumFillY(0, x + 1 , sudokuBoard, solStrg, filled, iteration); }
				else { genNumFillY(y + 1, x, sudokuBoard, solStrg, filled, iteration); }
			}
		}
		if (!filled) {
			sudokuBoard[y][x] = 0;
			solStrg[y][x].clear();
		}
	}
	else {
		filled = true;
	}
}

void genNumFillX(int y, int x, vector<vector<int>>& sudokuBoard, vector<vector<unordered_set<int>>>& solStrg, bool& filled, int& iteration,vector<vector<int>>& restriction) {

	if (y <= 8) {
			if (restriction[y][x] == 1) { 
				if (x >= 8) { genNumFillX(y + 1, 0, sudokuBoard, solStrg, filled, iteration, restriction); }
				else { genNumFillX(y, x + 1, sudokuBoard, solStrg, filled, iteration, restriction); }
			}
			else {
				if (solStrg[y][x].empty()) { updateSolutionStrg(y, x, sudokuBoard, solStrg); }
				unordered_set<int> solutions = getSolutions(y, x, solStrg);
				for (int num : solutions) {
					if (!filled) {
						solStrg[y][x].insert(num);
						sudokuBoard[y][x] = num;
						//system("cls");
						iteration++;
						//sudokuPrint(sudokuBoard);
						///*std::this_thread::sleep_for(std::chrono::milliseconds(100));*/
						if (x >= 8) { genNumFillX(y + 1, 0, sudokuBoard, solStrg, filled, iteration, restriction); }
						else { genNumFillX(y, x + 1, sudokuBoard, solStrg, filled, iteration, restriction); }
					}
				}
				if (!filled) {
					sudokuBoard[y][x] = 0;
					solStrg[y][x].clear();
				}
			}

	}
	else {
		filled = true;
	}
}

void genNumFillXY(int y, int x, vector<vector<int>>& sudokuBoard, vector<vector<unordered_set<int>>>& solStrg, bool& filled, int& iteration) {

	if (y >= 0 || x <= 8 || y <=8 ) {
		if (solStrg[y][x].empty()) { updateSolutionStrg(y, x, sudokuBoard, solStrg); }
		unordered_set<int> solutions = getSolutions(y, x, solStrg);
		for (int num : solutions) {
			if (!filled) {
				solStrg[y][x].insert(num);
				sudokuBoard[y][x] = num;
				system("cls");
				iteration++;
				sudokuPrint(sudokuBoard);
				/*std::this_thread::sleep_for(std::chrono::milliseconds(10));*/
				if (y >= 8) { 
					genNumFillXY(y - 1, 0, sudokuBoard, solStrg, filled, iteration);
				}
				else {
					genNumFillXY(y + 1, x + 1, sudokuBoard, solStrg, filled, iteration);
				
				}
			}
		}
		if (!filled) {
			sudokuBoard[y][x] = 0;
			solStrg[y][x].clear();
		}
	}
	else {
		filled = true;
	}
}


void sudokuGen(vector<vector<int>>& sudokuBoard, vector<vector<unordered_set<int>>>& solStrg, int& iteration,vector<vector<int>>& restriction) {

	bool filled = false;
	bool valid = false;
	

	genNumFillX(0, 0, sudokuBoard, solStrg, filled, iteration,restriction);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			solStrg[i][j].clear();
			updateSolutionStrg(i, j, sudokuBoard, solStrg);
			if (fullBoardCheck(i, j, sudokuBoard[i][j], sudokuBoard, solStrg)) {
				cout << "Not good position: y: " << i << " x: "<<j << endl;
				valid = true;
				break;
			}
		}
	}
	if (valid) { cout << "Sudoku not valid" << endl; }
}
void readBoard(string filename, vector<vector<int>>& sudokuBoard, vector<vector<int>>& restriction) {
	//Write an open file function to read the board
	std::ifstream file(filename);
	if (file.is_open()) {
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				file >> sudokuBoard[i][j];
				if (sudokuBoard[i][j] != 0) { restriction[i][j] = 1; }
			}
		}
		file.close();
	}
	else {
		std::cout << "Unable to open file";
	}

}	
int main(string arg) {
	auto start = std::chrono::high_resolution_clock::now();
	int iteration = 0;

	srand(static_cast<unsigned int>(time(0)));
	vector<vector<int>> sudokuBoard;
	vector<vector<int>> restriction;
	for (int i = 0; i < 9; i++) {
		vector<int> sudokuRow;
		sudokuBoard.push_back(sudokuRow);
		restriction.push_back(sudokuRow);
		for (int j = 0; j < 9; j++) {
			sudokuBoard[i].push_back(0);
			restriction[i].push_back(0);
		}
	}

	readBoard("sudokuTest.txt", sudokuBoard, restriction);
	sudokuPrint(sudokuBoard);
	sudokuPrint(restriction); 

	vector<vector<unordered_set<int>>> solStrg;
	for (int i = 0; i < 9; i++) {
		vector<unordered_set<int>> solRow;
		solStrg.push_back(solRow);
		for (int j = 0; j < 9; j++) {
			unordered_set<int> solSet;
			solStrg[i].push_back(solSet);
		}
	}

	sudokuGen(sudokuBoard,solStrg,iteration,restriction);
	sudokuPrint(sudokuBoard);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Time to execute: " << diff.count() << " s\n";
	std::cout << "Iteration times: " << iteration << endl;

}