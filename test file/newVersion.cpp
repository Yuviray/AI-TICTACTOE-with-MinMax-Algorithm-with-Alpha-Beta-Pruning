#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <vector>

//definitions for max depth, X's eval function and O's eval function
#define deepEnough 9
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
int checkWinner(char **, char);
vector<char **> * moveGen(char *, char);
char opposite(char);

char player2 = 'O';
int determineEval(char);

bool draw;
vector<char **> *bestPath = NULL;
int iteration;

int main()
{
    iteration = 0;
    //bestPath = NULL;
    Pathway *finalPath;
    //wanted to minimize global variables
    //some of these may go away depending on how the minimax algo works
    char **board = new char*[3];
    for (int i = 0; i < 3; i++) {
        board[i] = new char[3];
        for (int j = 0; j < 3; j++)
            board[i][j] = 'A'+ 2*i - j;
    }


    draw = false;
    char player = 'X';

    cout<<"TicTacToe"<<endl;

    display_board(board);
    finalPath = miniMax(board, 0, player, 12, -10);
    finalPath->PATH->insert(finalPath->PATH->begin(), board);
    printf("final path value: %d\n", finalPath->value);
    printf("final path size: %d\n", finalPath->PATH->size());
    int lastBoard = finalPath->PATH->size() -1 ;
    for (int i = 0; i < finalPath->PATH->size(); i++) {
        display_board(finalPath->PATH->at(i));
    }
    int winner = checkWinner(finalPath->PATH->at(lastBoard),player);

    cout<<"___________________________"<<endl;
    if(winner == 1 )
        printf("Player X is the winner\n");
    else if(winner == 2 )
        printf("Player O is the winner\n");
    else
        printf("Draw");
    cout<<"___________________________\n"<<endl;


    /*if(player == 'O' && draw == false){
        cout<<"Player 'X' has won the game";
    }
    else if(player == 'X' && draw == false){
        cout<<"Player 'O' has won the game";
    }
    else
        cout<<"GAME DRAW";*/
}


int checkWinner(char **board, char player){
    for(int row =0; row<3; row++){
        if(board[row][0]== player && board[row][1]== player && board[row][2]== player){
            return 1;
        }
        if(board[row][0]== player2 && board[row][1]== player2 && board[row][2] == player2){
            return 2;
        }
    }
    for(int col =0; col<3; col++){
        if(board[0][col] == player && board[1][col] == player && board[2][col] == player){
            return 1;
        }
        if(board[0][col] == player2 && board[1][col] == player2 && board[2][col] == player2){
            return 2;
        }
    }
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player){
        return 1;
    }
    if(board[0][0] == player2 && board[1][1] == player2 && board[2][2] == player2){
        return 2;
    }
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player){
        return 1;
    }
    if(board[0][2]!= player2 && board[1][1]!= player2 && board[2][0]!= player2){
        return 2;
    }
    else{
        return 0;
    }
}

//tweaked this one a little bit. i felt like gameover should be true when the game ended
bool gameover(char **board) {
    //gameover true if either of the following if statements are satisfied

    for(int i=0; i<3; i++) {
        if ((board[i][0] == board[i][1] && board[i][0] == board[i][2]) || (board[0][i] == board[1][i] && board[0][i] == board[2][i]))
            return true;
    }
    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2]) || (board[0][2] == board[1][1] && board[0][2] == board[2][0])){
        return true;
    }

    //gameover is false if above is not satisfied and there is no draw
    for(int i=0; i<3; i++){
        for (int j = 0; j < 3; j++) {
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }

    printf("GAME IS A DRAW*********************\n\n");
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

    //if (gameover(board)) {
    //return 10;
    //}


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

Pathway *miniMax(char **board, int depth, char plyr, int UT, int PT) {
    vector<char **> *successors;
    Pathway *retStruct, *resultSucc;
    int newVal;
    int evalFunc = determineEval(plyr);
    bool boardIns = false;


    //display_board(board);

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
            iteration++;
            //step 4a
            resultSucc = miniMax(successors->at(i), depth+1, opposite(plyr), -PT, -UT);

            //if (resultSucc->PATH == NULL)
            //resultSucc->PATH = new vector<char **>;

            //step 4b
            newVal = -resultSucc->value;
            //step 4c
            //printf("PT BEFORE : %d at depth %d\n", PT, depth);
            //cout << "BEST PATH ADDY at " << depth << " : " << bestPath << endl;
            if (newVal > PT) {

                //step 4ci
                PT = newVal;
                //step 4cii
                //assign bestPath to pathway of resultSucc
                bestPath = resultSucc->PATH;
                // if (bestPath == NULL) {
                //     printf("best path is null\n");
                //     printf("UT : %d *** PT : %d\n", UT, PT);
                //     printf("depth is %d\n", depth);
                //     printf("i is : %d\n", i);
                //     printf("successor size is: %d\n", successors->size());
                //     printf("Successor board 0 is: \n");
                //     display_board(successors->at(0));
                //     printf("Successor board 1 is: \n");
                //     display_board(successors->at(1));
                //     printf("board is:\n");
                //     display_board(board);
                // }

                //append succ to bestPath

                bestPath->insert(bestPath->begin(), successors->at(i));

                bestPath->insert(bestPath->begin(), board);
            }
            //step 4d
            if (PT >= UT) {
                //printf("\nwe trimmed the hedges\n");
                //printf("UT : %d *** PT : %d\n", UT, PT);
                //display_board(board);
                break;
            }
        }
        //step 5


        retStruct = new Pathway;
        retStruct->value = PT;
        retStruct->PATH = bestPath;
        return retStruct;
    }
}