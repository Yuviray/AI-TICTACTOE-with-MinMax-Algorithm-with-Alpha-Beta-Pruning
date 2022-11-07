#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <vector>

//definitions for max depth, X's eval function and O's eval function
#define deepEnough 3
#define plyrX 1
#define plyrO 1

using namespace std;

//structure used in the minimax function
struct Pathway {
    int value;
    vector<char **> * PATH;
};

Pathway path;

bool gameover(char **);
Pathway miniMax(char **, int , char, int, int);
void player_turn();
void display_board(char **);
int evaluate1(char **, char);
int evaluate2(char **, char);
int evaluate3(char **, char);
int evaluate4(char **, char);
vector<char **> * moveGen(char *, char);
char opposite(char);
int determineEval(char);

bool draw;

int main()
{

    path.value = 0;
    path.PATH = new vector<char **>;
    //wanted to minimize global variables
    //some of these may go away depending on how the minimax algo works
    char **board = new char*[3];
    for (int i = 0; i < 3; i++) {
        board[i] = new char[3];
        for (int j = 0; j < 3; j++)
            board[i][j] = 'A'+ 2*i - j;
    }

    char player = 'X';
    draw = false;

    cout<<"TicTacToe"<<endl;

    display_board(board);
    miniMax(board, 0, player, numeric_limits<int>::max(), -(numeric_limits<int>::max()));
    printf("\n\n\n********************************\n\n\n");
    printf("%d\n", path.value);
    for (int i = 0; i < path.PATH->size(); i++) {
        display_board(path.PATH->at(i));
    }


    /*if(player == 'O' && draw == false){
        cout<<"Player 'X' has won the game";
    }
    else if(player == 'X' && draw == false){
        cout<<"Player 'O' has won the game";
    }
    else
        cout<<"GAME DRAW";*/
}

//tweaked this one a little bit. i felt like gameover should be true when the game ended
bool gameover(char **board) {
    //gameover true if either of the following if statements are satisfied
    for(int i=0; i<3; i++) {
        if ((board[i][0] == board[i][1] == board[i][2]) || (board[0][i] == board[1][i] == board[2][i]))
            return true;
        if ((board[0][0] == board[1][1] == board[2][2]) || (board[0][2] == board[1][1] == board[2][0]))
            return true;
    }

    //gameover is false if above is not satisfied and there is no draw
    for(int i=0; i<3; i++){
        for (int j = 0; j < 3; j++) {
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }

    draw = true;
    return true;
}

//returns a vector that is the list of board positions in the next ply of the tree
vector<char **> * moveGen(char **board, char plyr) {
    vector<char **> * moves = new vector<char **>;

    if (plyr == 'X') {
        for (int i = 0; i < 3; i++) {
			 for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char **tempBoard = new char*[3];
                    char tempVal = board[i][j];
                    board[i][j] = 'X';
                    for (int k = 0; k < 3; k++) {
                        tempBoard[k] = new char[3];
                        for (int l = 0; l < 3; l++)
                            tempBoard[k][l] = board[k][l];
                    }
                    moves->push_back(tempBoard);
                    board[i][j] = tempVal;
                }
             }
		}
    }
    else {
        for (int i = 0; i < 3; i++)
		{
			 for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char **tempBoard = new char*[3];
                    char tempVal = board[i][j];
                    board[i][j] = 'O';
                    for (int k = 0; k < 3; k++) {
                        tempBoard[k] = new char[3];
                        for (int l = 0; l < 3; l++)
                            tempBoard[k][l] = board[k][l];
                    }
                    moves->push_back(tempBoard);
                    board[i][j] = tempVal;
                }
             }
		}
    }

    return moves;
}


//determines which evaluation function to use according to the player
int determineEval(char plyr) {
    if (plyr == 'X') return plyrX;
    else return plyrO;
}

//returns the opposite player
char opposite(char plyr) {
    if (plyr == 'X') return 'O';
    else return 'X';
}

void display_board(char **board){
    cout<<"PLAYER - 1 [X] PLAYER - 2 [O]"<<endl;
    cout<<"     |     |     "<<endl;
    cout<<"  "<<board[0][0]<<"  | " <<board[0][1]<<"   |  "<<board[0][2]<<endl;
    cout<<"_____|_____|_____"<<endl;
    cout<<"     |     |     "<<endl;
    cout<<"  "<<board[1][0]<<"  | " <<board[1][1]<<"   |  "<<board[1][2]<<endl;
    cout<<"_____|_____|_____"<<endl;
    cout<<"     |     |     "<<endl;
    cout<<"  "<<board[2][0]<<"  | " <<board[2][1]<<"   |  "<<board[2][2]<<endl;
    cout<<"     |     |     "<<endl;
}


int evaluate1(char **board, char player){
    int maxi =0;
    int mini =0;

    if (gameover(board))
        return 100000000;

    for(int row =0; row<3; row++){
        if(board[row][0]!= opposite(player) && board[row][1]!= opposite(player) && board[row][2]!= opposite(player)){
            maxi++;
        }
        if(board[row][0]!= player && board[row][1]!= player && board[row][2]!= player){
            mini++;
        }
    }
    for(int col =0; col<3; col++){
        if(board[0][col]!= opposite(player) && board[1][col]!= opposite(player) && board[2][col]!= opposite(player)){
            maxi++;
        }
        if(board[0][col]!= player && board[1][col]!= player && board[2][col]!= player){
            mini++;
        }
    }
    if(board[0][0]!= opposite(player) && board[1][1]!= opposite(player) && board[2][2]!= opposite(player)){
        maxi++;
    }
    if(board[0][0]!= player && board[1][1]!= player && board[2][2]!= player){
        mini++;
    }
    if(board[0][2]!= opposite(player) && board[1][1]!= opposite(player) && board[2][0]!= opposite(player)){
        maxi++;
    }
    if(board[0][2]!= player && board[1][1]!= player && board[2][0]!= player){
        mini++;
    }

    return maxi-mini;
}

int evaluate2(char **board, char player) {
    return 2;
}

int evaluate3(char **board, char player) {
    return 0;
}

int evaluate4(char **board, char player) {
    return 2;
}

//returns a Pathway structure. The structure could probably use a better name
Pathway miniMax(char **board, int depth, char plyr, int useThr, int passThr) {
    vector<char **> * successors;
    int resultSucc, newValue;
    int evalFunc = determineEval(plyr);

    // cout << "*****************************" << endl << endl;
    // cout << "board at depth :::::::: " << depth << endl << endl;
    // display_board(board);
    // cout << endl << endl;

    //if depth is deep enough, returns value of the current node back up the tree
    //not sure how to handle PATH=nil that is stated in the pseudocode yet, or what he means by that
    if (depth == deepEnough || gameover(board)){
        switch (evalFunc) {
            case 1:
                path.value = evaluate1(board, plyr);
                return path;
            case 2:
                path.value = evaluate2(board, plyr);
                return path;
            case 3:
                path.value = evaluate3(board, plyr);
                return path;
            case 4:
                path.value = evaluate4(board, plyr);
                return path;
        }
    }
    //step 2 in the psuedocode
    else {
        successors = moveGen(board, plyr);

        //step 3 in the pseudocode
        if (successors->size() == 0) {
            switch (evalFunc) {
                case 1:
                    path.value = evaluate1(board, plyr);
                    return path;
                case 2:
                    path.value = evaluate2(board, plyr);
                    return path;
                case 3:
                    path.value = evaluate3(board, plyr);
                    return path;
                case 4:
                    path.value = evaluate4(board, plyr);
                    return path;
            }
        }

        //step 4 in the pseudocode
        for (unsigned int i = 0; i < successors->size(); i++) {
            newValue = -miniMax(successors->at(i), depth + 1, opposite(plyr), -passThr, -useThr).value;
            if (newValue > passThr) {
                passThr = newValue;
                vector<char **> *bestPath = new vector<char **>;
                //copy the successor to a temporary board
                char **tempBoard = new char*[3];
                for (int k = 0; k < 3; k++) {
                    tempBoard[k] = new char[3];
                    for (int l = 0; l < 3; l++)
                        tempBoard[k][l] = successors->at(i)[k][l];
                }
                //push the temporary board to bestPath
                bestPath->push_back(tempBoard);
                delete tempBoard;
                //copy the path it took to get here to bestPath
                for (int j = 0; j < path.PATH->size(); j++) {
                    char **tempBoard = new char*[3];
                    for (int k = 0; k < 3; k++) {
                        tempBoard[k] = new char[3];
                        for (int l = 0; l < 3; l++)
                            tempBoard[k][l] = path.PATH->at(j)[k][l];
                    }
                    bestPath->push_back(tempBoard);
                    delete tempBoard;
                }

                printf("\n\n\nBest Path Size:::::::: %d\n\n\n", bestPath->size());

                if (passThr >= useThr) {
                    path.value = passThr;
                    path.PATH->erase(path.PATH->begin(), path.PATH->end());
                    for (int m = 0; m < bestPath->size(); m++) {
                        path.PATH->push_back(bestPath->at(m));
                    }
                    delete bestPath;
                    return path;
                }
                delete bestPath;

            }

        }
        //step 5 in the pseudocode
        return path;
    }
}
