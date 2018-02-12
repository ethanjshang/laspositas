#include <iostream>
#include <stack>
using namespace std;
const int SIZE = 15;
void printMaze(char[SIZE][SIZE]);
void findStart(char[SIZE][SIZE], int&, int&);
void move(char, int&, int&,stack<char>&,stack<int>&,stack<int>&, bool);
bool checkAndMove(char[SIZE][SIZE], int&, int&, stack<char>&,stack<int>&,stack<int>&, bool&);
void printDone(char[SIZE][SIZE], stack<char>&,stack<int>&,stack<int>&);
int main() {
    int curRow = 0, curCol = 0;
    bool unsolvable = true;
    stack<char> pathStackStatus;
    stack<int> pathStackRow;
    stack<int> pathStackCol;
    char arrMazePrint[SIZE][SIZE];
    char arrMaze[SIZE][SIZE] =
    {/*0*/ {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
        /*1*/ {'X','S','X','X','X','X',' ',' ',' ',' ','X','X','X','X','X'},
        /*2*/ {'X',' ',' ','X',' ',' ',' ','X','X',' ','X',' ',' ',' ','X'},
        /*3*/ {'X','X',' ','X','X',' ','X','X','X',' ',' ',' ','X',' ','X'},
        /*4*/ {'X',' ',' ','X','X',' ',' ',' ',' ','X',' ',' ',' ',' ','X'},
        /*5*/ {'X',' ','X','X','X','X','X',' ',' ','X','X','X',' ','X','X'},
        /*6*/ {'X',' ','X',' ','X','X','X',' ',' ','X',' ',' ',' ','X','X'},
        /*7*/ {'X',' ','X',' ',' ',' ',' ',' ','X',' ',' ','X','X','X','X'},
        /*8*/ {'X',' ',' ',' ','X','X','X',' ','X',' ','X',' ',' ',' ','X'},
        /*9*/ {'X','X',' ',' ','X','X','X',' ','X',' ','X',' ','X',' ','X'},
        /*0*/ {'X','X',' ','X',' ',' ',' ',' ','X',' ','X',' ','X',' ','X'},
        /*1*/ {'X','X',' ','X',' ',' ',' ','X','X',' ','X',' ','X',' ','X'},
        /*2*/ {'X','X',' ','X',' ',' ',' ',' ',' ',' ',' ',' ','X',' ','X'},
        /*3*/ {'X','X',' ','X','X','X','X','X','X','X','X',' ','X','E','X'},
        /*4*/ {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'}
    };
    for (int i = 0; i < SIZE; i++){
        for (int j =0; j < SIZE; j++){
            arrMazePrint[i][j] = arrMaze[i][j];
        }
    }
    cout << "Maze to be Solved" << endl;
    printMaze(arrMaze);
    cout << endl << endl << endl;
    findStart(arrMaze, curRow, curCol);
    checkAndMove(arrMaze, curRow, curCol, pathStackStatus, pathStackRow, pathStackCol, unsolvable);
    if (!unsolvable){
        cout << "Solution to maze" << endl;
        printDone(arrMazePrint, pathStackStatus, pathStackRow, pathStackCol);
    }
    else if (unsolvable){
        cout << "The maze cannot be solved" << endl;
    }
    return 0;
}
void printMaze(char arrMaze[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            cout << arrMaze[i][j] << " ";
        }
        cout << endl;
    }
}
void findStart(char arrMaze[SIZE][SIZE], int& startRow, int& startCol){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (arrMaze[i][j]=='S'){
                startRow = i;
                startCol = j;
            }
        }
    }
}

void move(char direction, int& curRow, int& curCol,
          stack<char>& status,stack<int>& row,stack<int>& col, bool record){
    switch (direction){
        case 'E':
        case 'e':
            curCol++;
            if (record){
                status.push('P');
                row.push(curRow);
                col.push(curCol);
            }
            break;
        case 'W':
        case 'w':
            curCol--;
            if (record){
                status.push('P');
                row.push(curRow);
                col.push(curCol);
            }
            break;
        case 'N':
        case 'n':
            curRow--;
            if (record){
                status.push('P');
                row.push(curRow);
                col.push(curCol);
            }
            break;
        case 'S':
        case 's':
            curRow++;
            if (record){
                status.push('P');
                row.push(curRow);
                col.push(curCol);
            }
            break;
    }
}

bool checkAndMove(char arrMaze[SIZE][SIZE], int& curRow, int& curCol,
                  stack<char>& status,stack<int>& row,stack<int>& col, bool& unsolvable){
    int east = curCol + 1;
    int west = curCol - 1;
    int south = curRow + 1;
    int north = curRow - 1;
    bool back = true;
    bool record = true;
    if (arrMaze[curRow][east] == 'E' or arrMaze[curRow][west] == 'E'
        or arrMaze[south][curCol] == 'E' or arrMaze[north][curCol] == 'E'){
        unsolvable = false;
        return true;
    }
    if (arrMaze[curRow][east] != 'X' and arrMaze[curRow][east] != 'M'){
        move('E', curRow, curCol, status, row, col, record);
        arrMaze[curRow][curCol] = 'M';
        back = false;
        checkAndMove(arrMaze, curRow, curCol, status, row, col, unsolvable);
    }
    else if (arrMaze[south][curCol] != 'X' and arrMaze[south][curCol] != 'M'){
        move('S', curRow, curCol, status, row, col, record);
        arrMaze[curRow][curCol] = 'M';
        back = false;
        checkAndMove(arrMaze, curRow, curCol, status, row, col, unsolvable);
    }
    else if (arrMaze[curRow][west] != 'X' and arrMaze[curRow][west] != 'M'){
        move('W', curRow, curCol, status, row, col, record);
        arrMaze[curRow][curCol] = 'M';
        back = false;
        checkAndMove(arrMaze, curRow, curCol, status, row, col, unsolvable);
    }
    else if (arrMaze[north][curCol] != 'X' and arrMaze[north][curCol] != 'M'){
        move('N', curRow, curCol, status, row, col, record);
        arrMaze[curRow][curCol] = 'M';
        back = false;
        checkAndMove(arrMaze, curRow, curCol, status, row, col, unsolvable);
    }
    if (back){
        status.pop();
        row.pop();
        col.pop();
        record = false;
        arrMaze[curRow][curCol] = 'X';
        if (arrMaze[curRow][east] != 'X'){
            move('E', curRow, curCol, status, row, col, record);
            checkAndMove(arrMaze, curRow, curCol, status, row, col, unsolvable);
        }
        else if (arrMaze[curRow][west] != 'X'){
            move('W', curRow, curCol, status, row, col, record);
            checkAndMove(arrMaze, curRow, curCol, status, row, col, unsolvable);
        }
        else if (arrMaze[south][curCol] != 'X'){
            move('S', curRow, curCol, status, row, col, record);
            checkAndMove(arrMaze, curRow, curCol, status, row, col, unsolvable);
        }
        else if (arrMaze[north][curCol] != 'X'){
            move('N', curRow, curCol, status, row, col, record);
            checkAndMove(arrMaze, curRow, curCol, status, row, col, unsolvable);
        }
    }
    if (arrMaze[curRow][east] == 'X' and arrMaze[curRow][west] == 'X'
        and arrMaze[south][curCol] == 'X' and arrMaze[north][curCol] == 'X'){
    }
    return false;
}
void printDone(char arrMaze[SIZE][SIZE], stack<char>& status,stack<int>& row,stack<int>& col){
    unsigned long increment = row.size();
    for (unsigned int i = 0; i < increment; i++){
        arrMaze[row.top()][col.top()] = 'P';
            row.pop();
        col.pop();
        status.pop();
    }
    
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            cout << arrMaze[i][j] << " ";
        }
        cout << endl;
    }
}
