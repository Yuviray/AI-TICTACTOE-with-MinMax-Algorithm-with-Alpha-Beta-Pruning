// Artificial Intelligence  CS 4346.001
// Project 2 MinMax algorithm with alpha beta pruning
// Team Members: Yuvanesh Rajamani, Nico Maldonado, John Edwards.
#include <iostream>
#include <cstdlib>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>
#include <vector>


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
int allTriesP = 0;
int totalTries = 0;
int totalTriesP = 0;
int totalTriesX = 0;// nodes generated after pruning for x
int totalTriesO = 0;// nodes generated after pruning for x
int totalTriesXbP = 0; // nodes generated before pruning for x
int totalTriesObP = 0;// nodes generated before pruning for o
bool xWin = false;
bool oWin = false;
bool gameover();
int totalTime1 = 0;
int totalTime2 = 0;
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
        int start_s = clock();
        bestMove();
        int stop_s = clock();
        totalTime1 += (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
        cout << allTries << " Nodes Generated" << endl;
        totalTries += allTries;
        totalTriesXbP += allTries;
        allTries = 0;
        cout << allTriesP << " Nodes Generated after Prune" << endl;
        totalTriesP += allTriesP;
        totalTriesX +=allTriesP;
        allTriesP = 0;


    }
    else if(turn == 'O'){
        cout<<"Player - 2 [O] turn : ";
        int start_s = clock();
        bestMove();
        int stop_s = clock();
        totalTime2 += (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
        cout << allTries << " Nodes Generated" << endl;
        totalTries += allTries;
        totalTriesObP += allTries;
        allTries = 0;
        cout << allTriesP << " Nodes Generated after Prune" << endl;
        totalTriesP += allTriesP;
        totalTriesO +=allTriesP;
        allTriesP = 0;
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

// base evaluation shown in class
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

// Nicos practice evaluation
int evaluate(char player){
    if(player == 'X') {
        if (xWin) {
            xWin = false;
            return 1;
        } else if (oWin) {
            oWin = false;
            return -1;
        } else {
            return 0;
        }
    }else if(player == 'O'){
        if (oWin) {
            oWin = false;
            return 1;
        } else if (xWin) {
            xWin = false;
            return -1;
        } else {
            return 0;
        }
    }
}

// Nicos  evaluation
int evaluate2(char board[3][3], char player, int depth){
    if(player == 'X') {
        if (xWin) {
            xWin = false;
            for (int i = 0; i < 9; i++) {
                if (depth == i) {
                    return 11 + i;
                }
            }
        } else if (oWin) {
            oWin = false;
            for (int i = 0; i < 9; i++) {
                if (depth == i) {
                    return -11 - i;
                }
            }
        } else {
            return 0;
        }
    }else if(player == 'O'){
        if (oWin) {
            oWin = false;
            for (int i = 0; i < 9; i++) {
                if (depth == i) {
                    return 11 + i;
                }
            }
        } else if (xWin) {
            xWin = false;
            for (int i = 0; i < 9; i++) {
                if (depth == i) {
                    return -11 - i;
                }
            }
        } else {
            return 0;
        }
    }
}
 // Johns evaluation
int evaluate3(char board[3][3], char player, char opp) {
    int MS_board[3][3] = {{8, 3, 4}, {1, 5, 9}, {6, 7, 2}};
    vector<int> moves_p, moves_o, winMoves, lossMoves;

    //accumulating the values for each player's moves
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == player) {
                moves_p.push_back(MS_board[i][j]);
            }
            if (board[i][j] == opp) {
                moves_o.push_back(MS_board[i][j]);
            }
        }
    }

    //accumlating winning moves
    if (moves_p.size() > 2) {
        for (int i = 0; i < moves_p.size()-1; i++) {
            for (int j = i+1; j < moves_p.size(); j++) {
                int m = 15 - (moves_p[i] + moves_p[j]);
                if (m > 0 && m < 10) {
                    winMoves.push_back(m);
                }
            }
        }
    }
    //accumulating losing moves
    if (moves_o.size() > 2) {
        for (int i = 0; i < moves_o.size()-1; i++) {
            for (int j = i+1; j < moves_o.size(); j++) {
                int m = 15 - (moves_o[i] + moves_o[j]);
                if (m > 0 && m < 10) {
                    lossMoves.push_back(m);
                }
            }
        }
    }
    //evaluating the accumulated moves
    //check for wins
    if (winMoves.size() > 0) {
        for (int i = 0; i < winMoves.size(); i++) {
            for (int j = 0; j < moves_p.size(); j++) {
                if (winMoves[i] == moves_p[j]) {
                    return 1;
                }
            }
        }
    }
    //check for losses
    if (lossMoves.size() > 0) {
        for (int i = 0; i < lossMoves.size(); i++) {
            for (int j = 0; j < moves_o.size(); j++) {
                if (lossMoves[i] == moves_o[j]) {
                    return -1;
                }
            }
        }
    }
    //return 0 if no win or loss
    return 0;
}

// Yuvanesh evaluation
// this function evaluated the board by count the win possibilities for 2 of the same pieces in a row/col/diagonal
// and also for 1 piece in a row/col/diagonal
// this is also static
int evaluate4(char board[3][3], char player, char opp){
    int x2 =0;
    int o2 =0;
    int x1=0;
    int o1 =0;

    char opponent = opp;
    for(int row =0; row < 3; row++){
        // checks for win possibilities for 2 pieces on board
        if(board[row][0]== player   && board[row][1]== player  && board[row][2]!= (opponent||player) ){
            x2++;
        }
        if(board[row][1]== player   && board[row][2]== player  && board[row][0]!= (opponent||player) ){
            x2++;
        }
        if(board[row][0]== player   && board[row][2]== player  && board[row][1]!= (opponent||player) ){
            x2++;
        }
        if(board[row][0]== opponent   && board[row][1]== opponent  && board[row][2]!= (opponent||player) ){
            o2++;
        }
        if(board[row][1]== opponent   && board[row][2]== opponent  && board[row][0]!= (opponent||player) ){
            o2++;
        }
        if(board[row][0]== opponent   && board[row][2]== opponent  && board[row][1]!= (opponent||player) ){
            o2++;
        }

        // checks for win possibilities for 1 piece on board
        if(board[row][0]== player   && board[row][1]!= (opponent||player)  && board[row][2]!= (opponent||player) ){
            x1++;
        }
        if(board[row][1]== player  && board[row][0]!= (opponent||player)  && board[row][2]!= (opponent||player) ) {
            x1++;
        }
        if(board[row][2]== player   && board[row][1]!= (opponent||player)  && board[row][0]!= (opponent||player) ) {
            x1++;
        }
        if(board[row][0]== opponent   && board[row][1]!= (opponent||player)  && board[row][2]!= (opponent||player) ){
            o1++;
        }
        if(board[row][1]== opponent  && board[row][0]!= (opponent||player)  && board[row][2]!= (opponent||player) ) {
            o1++;
        }
        if(board[row][2]== opponent   && board[row][1]!= (opponent||player)  && board[row][0]!= (opponent||player) ) {
            o1++;
        }
    }
    for(int col =0; col<3; col++){
        // checks for win possibilities for 2 pieces on board
        if(board[0][col] == player  && board[1][col]== player  && board[2][col]!= (opponent||player) ){
            x2++;
        }
        if(board[1][col] == player  && board[2][col]== player  && board[0][col]!= (opponent||player) ){
            x2++;
        }
        if(board[2][col] == player  && board[0][col]== player  && board[1][col]!= (opponent||player) ){
            x2++;
        }
        if(board[0][col] == opponent  && board[1][col]== opponent  && board[2][col]!= (opponent||player) ){
            o2++;
        }
        if(board[0][col] == opponent  && board[2][col]== opponent  && board[1][col]!= (opponent||player) ){
            o2++;
        }
        if(board[2][col] == opponent  && board[1][col]== opponent  && board[0][col]!= (opponent||player) ){
            o2++;
        }
        // checks for win possibilities for 1 piece on board
        if(board[0][col] == player  && board[1][col]!= (opponent||player) && board[2][col]!= (opponent||player) ){
            x2++;
        }
        if(board[1][col] == player  && board[2][col]!= (opponent||player)  && board[1][col]!= (opponent||player) ){
            x2++;
        }
        if(board[2][col] == player  && board[1][col]!= (opponent||player)  && board[0][col]!= (opponent||player) ){
            x2++;
        }
        if(board[0][col] == opponent  && board[1][col]!= (opponent||player)  && board[2][col]!= (opponent||player) ){
            o2++;
        }
        if(board[1][col] == opponent  && board[2][col]!= (opponent||player)  && board[0][col]!= (opponent||player) ){
            o2++;
        }
        if(board[2][col] == opponent  && board[1][col]!= (opponent||player) && board[0][col]!= (opponent||player) ){
            o2++;
        }
    }
    // checks for win possibilities for 2 pieces on board
    if(board[2][2] == player  && board[1][1]== player && board[0][0]!= (opponent||player) ){
        x2++;
    }
    if(board[0][0] == player  && board[2][2]== player && board[1][1]!= (opponent||player) ){
        x2++;
    }
    if(board[0][0] == player  && board[1][1]== player && board[2][2]!= (opponent||player) ){
        x2++;
    }
    if(board[2][2] == opponent  && board[1][1]== opponent && board[0][0]!= (opponent||player) ){
        o2++;
    }
    if(board[0][0] == opponent  && board[2][2]== opponent && board[1][1]!= (opponent||player) ){
        o2++;
    }
    if(board[0][0] == opponent  && board[1][1]== opponent && board[2][2]!= (opponent||player) ){
        o2++;
    }
    //other diagonal

    if(board[2][0] == player  && board[1][1]== player && board[0][2]!= (opponent||player) ){
        x2++;
    }
    if(board[0][2] == player  && board[2][0]== player && board[1][1]!= (opponent||player) ){
        x2++;
    }
    if(board[0][2] == player  && board[1][1]== player && board[2][0]!= (opponent||player) ){
        x2++;
    }
    if(board[2][0] == opponent  && board[1][1]== opponent && board[0][2]!= (opponent||player) ){
        o2++;
    }
    if(board[0][2] == opponent  && board[2][0]== opponent && board[1][1]!= (opponent||player) ){
        o2++;
    }
    if(board[0][2] == opponent  && board[1][1]== opponent && board[2][0]!= (opponent||player) ){
        o2++;
    }

    // checks for win possibilities for 1 piece on board
    if(board[2][2] == player  && board[1][1]!= (opponent||player) && board[0][0]!= (opponent||player) ){
        x1++;
    }
    if(board[0][0] == player  && board[2][2]!= (opponent||player) && board[1][1]!= (opponent||player) ){
        x1++;
    }
    if(board[1][1] == player  && board[0][0]!= (opponent||player) && board[2][2]!= (opponent||player) ){
        x1++;
    }
    if(board[2][2] == opponent  && board[1][1]!= (opponent||player) && board[0][0]!= (opponent||player) ){
        o1++;
    }
    if(board[0][0] == opponent  && board[2][2]!= (opponent||player) && board[1][1]!= (opponent||player) ){
        o1++;
    }
    if(board[1][1] == opponent  && board[0][0]!= (opponent||player) && board[2][2]!= (opponent||player) ){
        o1++;
    }
    //other diagonal

    if(board[2][0] == player  && board[1][1]!= (opponent||player) && board[0][2]!= (opponent||player) ){
        x1++;
    }
    if(board[0][2] == player  && board[2][0]!= (opponent||player)&& board[1][1]!= (opponent||player) ){
        x1++;
    }
    if(board[1][1] == player  && board[0][2]!= (opponent||player) && board[2][0]!= (opponent||player) ){
        x1++;
    }
    if(board[2][0] == opponent  && board[1][1]!= (opponent||player) && board[0][2]!= (opponent||player) ){
        o1++;
    }
    if(board[0][2] == opponent  && board[2][0]!= (opponent||player) && board[1][1]!= (opponent||player) ){
        o1++;
    }
    if(board[1][1] == opponent  && board[0][2]!= (opponent||player) && board[2][0]!= (opponent||player) ){
        o1++;
    }
    return 2*x2+x1-2*o2-o1;
}



int miniMax(char board[3][3], int depth, char player, int use, int pass){
    int score;
    int bestScore;
    if(turn == 'X') {
        if(!gameover()) { // uncomment the return statement depending on which evaluation
            return evaluate1(board, 'X','O');
            // return evaluate('X');
            // return evaluate2(board,'X',depth);
            // return evaluate3(board, 'X','O');
            // return evaluate4(board,'X','O');

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
                        allTries++;
                        if (score > bestScore) {
                            bestScore = score;
                        }
                        if (score > use) {
                            use = score;
                        }
                        if (pass <= use) {
                            break;
                        }
                        allTriesP++;
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
                        allTries++;
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
                        allTriesP++;

                    }
                }
            }
            return bestScore;
        }
    }else if (turn == 'O'){
        if (!gameover()) {// uncomment the return statement depending on which evaluation
            return evaluate1(board, 'X','O');
           // return evaluate('O');
           // return evaluate2(board,'O',depth);
           // return evaluate3(board, 'X','O');
           // return evaluate4(board,'X','O');

        }
        if (player == 'O') {
            bestScore = -INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] != 'X' && board[i][j] != 'O') {
                        char temp = board[i][j];
                        board[i][j] = 'O';
                        score = miniMax(board, depth + 1, 'X', -pass, -use);
                        allTries++;
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
                        allTriesP++;

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
                        allTries++;
                        if (score < bestScore) {
                            bestScore = score;
                        }
                        if (score < pass) {
                            use = score;
                        }
                        if (pass <= use) {
                            break;
                        }
                        allTriesP++;
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

    if ((board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
        || (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
        || (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')) {
        xWin = true;
        return false;
    } else if ((board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O')
        || (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
        || (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')) {
        oWin = true;
        return false;
    }

    if ((board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')
        || (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
        || (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')) {
        xWin = true;
        return false;
    } else if ((board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O')
        || (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')
        || (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')) {
        oWin = true;
        return false;
    }

    //checking the win for both diagonal
    if ((board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
        || (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')){
        xWin = true;
        return false;
    } else if ((board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
        || (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')) {
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
    pid_t pid;
    pid = getpid();
    cout<<"T I C K -- T A C -- T O E -- G A M E" << endl;
    cout<<"FOR 2 PLAYERS" << endl;
    int start_s = clock();
    while(gameover()){
        display_board();
        player_turn();
        gameover();
    }
    int stop_s = clock();
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

    cout << "Total Nodes Generated for both players: " << totalTries << endl;
    cout << "Total Nodes Generated for player X: " << totalTriesXbP << endl;
    cout << "Total Nodes Generated for player O: " << totalTriesObP << endl;
    cout << "Total memory used for player X: " << (totalTriesXbP*9)/1000 << " kbs" << endl;
    cout << "Total memory used for player O: " << (totalTriesObP*9)/1000 << " kbs" << endl;

    cout << "______________________________________________________________" << endl;

    cout << "Total Nodes Generated after Pruning for both players: " << totalTriesP << endl;
    cout << "Total Nodes Expanded after Pruning for player X: " << totalTriesX << endl;
    cout << "Total Nodes Expanded after Pruning for player O: " << totalTriesO << endl;
    cout << "Total memory used after Pruning for player X: " << (totalTriesX*9)/1000 << " kbs" << endl;
    cout << "Total memory used after Pruning for player O: " << (totalTriesO*9)/1000 << " kbs" << endl;
    cout << "______________________________________________________________" << endl;
    //cout << "Process ID for this program: " << pid << endl;
    cout << "Program took " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << " ms\n";
    cout << "Time for player X : " << totalTime1 << " ms" << endl;
    cout << "Time for player O : " << totalTime2 << " ms" << endl;

    //system("ps u");
    return 0;
}
