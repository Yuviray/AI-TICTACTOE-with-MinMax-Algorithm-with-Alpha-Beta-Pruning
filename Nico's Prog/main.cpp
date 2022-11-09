#include <iostream>
#include <cstdlib>
using namespace std;
//Array for the board
char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
//Variable Declaration
int choice;
int row,column;
char turn = 'X';
bool draw = false;

int miniMax(char board[3][3], int depth, char player, int alpha, int beta);
int bestRow= 0;
int bestCol = 0;
int allTries = 0;
bool xWin = false;
bool oWin = false;
bool gameover();
//Function to show the current status of the gaming board

void display_board(){

    //Rander Game Board LAYOUT

    cout<<"PLAYER - 1 [X] PLAYER - 2 [O]"<< endl;
    cout<<"     |     |     " << endl;
    cout<<"  "<<board[0][0]<<"  | "<<board[0][1]<<"  |  "<<board[0][2]<<" " << endl;
    cout<<"_____|_____|_____" << endl;
    cout<<"     |     |     " << endl;
    cout<<"  "<<board[1][0]<<"  | "<<board[1][1]<<"  |  "<<board[1][2]<<" " << endl;
    cout<<"_____|_____|_____" << endl;
    cout<<"     |     |     " << endl;
    cout<<"  "<<board[2][0]<<"  | "<<board[2][1]<<"  |  "<<board[2][2]<<" " << endl;
    cout<<"     |     |     " << endl;
}

//Function to get the player input and update the board
void bestMove();
void player_turn(){
    if(turn == 'X'){
        cout<<"Player - 1 [X] turn : ";
        bestMove();
        cout << allTries << " tries" << endl;
        allTries = 0;
    }
    else if(turn == 'O'){
        cout<<"Player - 2 [O] turn : ";
        bestMove();
        cout << allTries << " tries" << endl;
        allTries = 0;
    }
}



void bestMove(){
    int bestScore = -INT_MAX;
    int score = 0;
    if(turn == 'X') {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'X';
                    score = miniMax(board, 0, 'O', INT_MIN, INT_MAX);
                    board[i][j] = temp;
                    if (score > bestScore) {
                        bestScore = score;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
        }
        cout << bestScore << endl;
        board[bestRow][bestCol] = 'X';
        turn = 'O';
    }else if(turn == 'O'){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'O';
                    score = miniMax(board, 0, 'X', INT_MIN, INT_MAX);
                    board[i][j] = temp;
                    if (score > bestScore) {
                        bestScore = score;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
        }
        cout << bestScore << endl;
        board[bestRow][bestCol] = 'O';
        turn = 'X';
    }
    xWin =false;
    oWin = false;
    draw = false;
}

int evaluate1(char board[3][3], char player, char opp){
    int maxi =0;
    int mini =0;

    char opponent = opp;
    for(int row =0; row < 3; row++){
        if(board[row][0]!= opponent   && board[row][1]!= opponent  && board[row][2]!= opponent ){
            maxi++;
        }
        if(board[row][0]!= player && board[row][1]!= player && board[row][2]!= player){
            mini++;
        }
    }
    for(int col =0; col<3; col++){
        if(board[0][col]!= opponent  && board[1][col]!= opponent  && board[2][col]!= opponent ){
            maxi++;
        }
        if(board[0][col]!= player && board[1][col]!= player && board[2][col]!= player){
            mini++;
        }
    }
    if(board[0][0]!= opponent  && board[1][1]!= opponent  && board[2][2]!= opponent ){
        maxi++;
    }
    if(board[0][0]!= player && board[1][1]!= player && board[2][2]!= player){
        mini++;
    }
    if(board[0][2]!= opponent  && board[1][1]!= opponent  && board[2][0]!= opponent ){
        maxi++;
    }
    if(board[0][2]!= player && board[1][1]!= player && board[2][0]!= player){
        mini++;
    }

    return maxi-mini;
}

int evaluation2(){
    if (xWin) {
        xWin = false;
        return -1;
    } else if (oWin) {
        oWin = false;
        return 1;
    } else {
        return 0;
    }
}

int miniMax(char board[3][3], int depth, char player, int use, int pass){
    int score;
    int bestScore;
    if(turn == 'X') {
        if(!gameover()) {
            return evaluate1(board, 'X', 'O');
        }
        if (player == 'X') {
            bestScore = -INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] != 'X' && board[i][j] != 'O') {
                        char temp = board[i][j];
                        board[i][j] = 'X';
                        score = miniMax(board, depth + 1, 'O', -pass, -use);
                        board[i][j] = temp;
                        if (score > bestScore) {
                            bestScore = score;
                        }
                        if (score > use) {
                            use = score;
                        }
                        if (pass <= use) {
                            break;
                        }
                        allTries++;
                    }
                }
            }
            return bestScore;
        } else {
            bestScore = INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] != 'X' && board[i][j] != 'O') {
                        char temp = board[i][j];
                        board[i][j] = 'O';
                        score = miniMax(board, depth + 1, 'X', -use, -pass);
                        board[i][j] = temp;
                        if (score < bestScore) {
                            bestScore = score;
                        }
                        if (score < pass) {
                            use = score;
                        }
                        if (pass <= use) {
                            break;
                        }
                        allTries++;
                    }
                }
            }
            return bestScore;
        }
    }else if (turn == 'O'){
        if (!gameover()) {
           return evaluate1(board, 'O', 'X');
        }
        if (player == 'O') {
            bestScore = -INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] != 'X' && board[i][j] != 'O') {
                        char temp = board[i][j];
                        board[i][j] = 'O';
                        score = miniMax(board, depth + 1, 'X', -pass, -use);
                        board[i][j] = temp;
                        if (score > bestScore) {
                            bestScore = score;
                        }
                        if (score > use) {
                            use = score;
                        }
                        if (pass <= use) {
                            break;
                        }
                        allTries++;
                    }
                }
            }
            return bestScore;
        } else {
            bestScore = INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] != 'X' && board[i][j] != 'O') {
                        char temp = board[i][j];
                        board[i][j] = 'X';
                        score = miniMax(board, depth + 1, 'O', -use, -pass);
                        board[i][j] = temp;
                        if (score < bestScore) {
                            bestScore = score;
                        }
                        if (score < pass) {
                            use = score;
                        }
                        if (pass <= use) {
                            break;
                        }
                        allTries++;
                    }
                }
            }
            return bestScore;
        }
    }
}
//Function to get the game status e.g. GAME WON, GAME DRAW GAME IN CONTINUE MODE

bool gameover(){
    //checking the win for Simple Rows and Simple Column

    if ((board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X') || (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
        || (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')) {
        xWin = true;
        return false;
    } else if ((board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O') || (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
               || (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')) {
        oWin = true;
        return false;
    }

    if ((board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X') || (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
        || (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')) {
        xWin = true;
        return false;
    } else if ((board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O') || (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')
               || (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')) {
        oWin = true;
        return false;
    }

    //checking the win for both diagonal
    if ((board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') || (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')){
        xWin = true;
        return false;
    } else if ((board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') || (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')) {
        oWin = true;
        return false;
    }else{
        int count = 0;
        for(int i = 0; i<3;i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == 'X' || board[i][j] == 'O')
                    count++;
            }
        }
        if(count == 9) {
            draw = true;
            return false;
        }
    }
    return true;
}

//Program Main Method

int main()
{
    cout<<"T I C K -- T A C -- T O E -- G A M E" << endl;
    cout<<"FOR 2 PLAYERS" << endl;
    while(gameover()){
        display_board();
        player_turn();
        gameover();
    }
    if(xWin){
        cout<<"Congratulations!Player with 'X' has won the game" << endl;
        display_board();
    }
    else if(oWin){
        cout<<"Congratulations!Player with 'O' has won the game" << endl;
        display_board();
    }
    else if(draw)
    {
        cout << "GAME DRAW!!!" << endl;
        display_board();
    }
}