#include <iostream>
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
		 	exit(0);      ////////////Exit Success is indicated by exit(0) statement 
			              ////////////which means successful termination of the program, 
					      ////////////i.e. program has been executed without any error or interrupt.
		}				  
		                  ////////////Exit Failure is indicated by exit(1) which means the abnormal 
		                  ////////////termination of the program, i.e. some error or interrupt has occurred.
						  //////////// We can use different integer other than 1 to indicate different types of errors.
		else if (isDraw(board)) {
		 	cout << "No winner" << endl;
		 	exit(0);
		}

		//The second player makes a move
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

void makeAMove(char board[][3], char marker){

	int rowNum;
	int colNum;
	bool validInput = false;

	while(!validInput){
		cout << "Enter a row (0, 1, 2) for player " << marker << " : ";
		cin >> rowNum;
		cout << "Enter a column (0, 1, 2) for player " << marker << " : ";
		cin >> colNum;

		if(board[rowNum][colNum] == ' ' && (rowNum == 0 || rowNum == 1 || rowNum == 2) && (colNum == 0 || colNum == 1 || colNum == 2)){
			board[rowNum][colNum] = marker;
			validInput = true;
		}else if(board[rowNum][colNum] != ' '){
			cout << "This cell is already occupied. Try a different cell" << endl;
		}else{
			cout << "Invalid row/column input" << endl;
		}
	}
}

void displayBoard(char board[][3]){

	for(int i = 0; i < 3; i++){
		cout << "-------------" << endl;
		cout << "| " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " |" << endl;
	}
	cout << "-------------" << endl;

}

bool isWon(char marker, char board[][3]){
	//check rows
	for(int i = 0; i < 3; i++ ){
		if ((board[i][0] == marker) && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2])) {
            return true; 
        }
	}
	//Check columns
    for (int i = 0; i < 3; i++) {
        if ((board[0][i] == marker) && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i])) {
            return true; 
        }
    }
	//Check top left diagonal
    if ((board[0][0] == marker) && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) {
        return true; 
    }
	//Check top right diagonal
    if ((board[2][0] == marker) && (board[2][0] == board[1][1]) && (board[1][1] == board[0][2])) {
        return true;
    }

	return false;
}

bool isDraw(char board[][3]){
    for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] == ' '){
				return false;
			}
		}
	}
	return true;
}