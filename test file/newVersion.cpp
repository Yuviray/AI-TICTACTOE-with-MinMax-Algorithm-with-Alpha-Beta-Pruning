#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <vector>

//definitions for max depth, X's eval function and O's eval function
#define deepEnough 2
#define plyrX 1
#define plyrO 1

using namespace std;

//structure used in the minimax function
struct Pathway {
    int value;
    vector<char **> * PATH;
};

bool gameover(char **);
Pathway *miniMax(char **, int , char, int, int);
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
vector<char **> *bestPath;

int main()
{
    Pathway *finalPath;
    bestPath = new vector<char **>;
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
    finalPath = miniMax(board, 0, player, 10, -12);
    printf("\n\n\n********************************\n\n\n");
    printf("%d\n", finalPath->value);
    for (int i = 0; i < finalPath->PATH->size(); i++) {
        display_board(finalPath->PATH->at(i));
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
    printf("\nEval for player %c\n", player);

    if (gameover(board)) {
        printf("%d\n", 10);
        return 10;
    }


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

    printf("%d\n", maxi-mini);
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

Pathway *miniMax(char **board, int depth, char plyr, int UT, int PT) {
    vector<char **> *successors;
    Pathway *retStruct, *resultSucc;
    int newVal;
    int evalFunc = determineEval(plyr);


    //step 1 in pseudocode
    if(depth == deepEnough || gameover(board)) {
        switch (evalFunc) {
            case 1:
                retStruct = new Pathway;
                retStruct->PATH = new vector<char **>;
                retStruct->value = evaluate1(board, plyr);
                return retStruct;
            case 2:
                retStruct = new Pathway;
                retStruct->PATH = new vector<char **>;
                retStruct->value = evaluate2(board, plyr);
                return retStruct;
            case 3:
                retStruct = new Pathway;
                retStruct->PATH = new vector<char **>;
                retStruct->value = evaluate3(board, plyr);
                return retStruct;
            case 4:
                retStruct = new Pathway;
                retStruct->PATH = new vector<char **>;
                retStruct->value = evaluate4(board, plyr);
                return retStruct;
        }
    }

    //step 2 in pseudocode
    else {
        successors = moveGen(board, plyr);

        //step 3 in pseudocode
        if (successors->size() == 0) {
            switch (evalFunc) {
                case 1:
                    retStruct = new Pathway;
                    retStruct->PATH = new vector<char **>;
                    retStruct->value = evaluate1(board, plyr);
                    return retStruct;
                case 2:
                    retStruct = new Pathway;
                    retStruct->PATH = new vector<char **>;
                    retStruct->value = evaluate2(board, plyr);
                    return retStruct;
                case 3:
                    retStruct = new Pathway;
                    retStruct->PATH = new vector<char **>;
                    retStruct->value = evaluate3(board, plyr);
                    return retStruct;
                case 4:
                    retStruct = new Pathway;
                    retStruct->PATH = new vector<char **>;
                    retStruct->value = evaluate4(board, plyr);
                    return retStruct;
            }
        }

        //step 4 in pseudocode
        for(int i = 0; i < successors->size(); i++) {
            //step 4a
            resultSucc = miniMax(successors->at(i), depth+1, opposite(plyr), -PT, -UT);
            //step 4b
            newVal = -resultSucc->value;
            //step 4c
            if (newVal > PT) {
                //step 4ci
                PT = newVal;
                //step 4cii
                //erase bestPath to start fresh
                bestPath->erase(bestPath->begin(), bestPath->end());
                //copy successor to tempBoard and append to bestPath
                char **tempBoard = new char*[3];
                for (int j = 0; j < 3; j++) {
                    tempBoard[j] = new char[3];
                    for (int k = 0; k < 3; k++) {
                        tempBoard[j][k] = successors->at(i)[j][k];
                    }
                }
                bestPath->push_back(tempBoard);
                delete tempBoard;
                //copy each element of resultSucc->PATH to tempBoard and append to bestPath
                if (resultSucc->PATH->size() > 0) {
                    for (int j = 0; j < resultSucc->PATH->size(); j++) {
                        char **tempBoard = new char*[3];
                        for (int k = 0; k < 3; k++) {
                            tempBoard[k] = new char[3];
                            for (int l = 0; l < 3; l++) {
                                tempBoard[k][l] = resultSucc->PATH->at(j)[k][l];
                            }
                        }
                        bestPath->push_back(tempBoard);
                        delete tempBoard;
                    }
                }
            }
            //step 4d
            else {
                retStruct->value = PT;
                retStruct->PATH = bestPath;
                return retStruct;
            }
        }
        //step 5
        retStruct->value = PT;
        retStruct->PATH = bestPath;
        return retStruct;
    }
}
