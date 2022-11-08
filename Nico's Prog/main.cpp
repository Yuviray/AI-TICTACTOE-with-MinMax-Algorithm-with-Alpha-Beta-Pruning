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
    if(turn == 'O'){
        cout<<"Player - 1 [O] turn : ";
        cin>> choice;
        switch(choice){
            case 1: row=0; column=0; break;
            case 2: row=0; column=1; break;
            case 3: row=0; column=2; break;
            case 4: row=1; column=0; break;
            case 5: row=1; column=1; break;
            case 6: row=1; column=2; break;
            case 7: row=2; column=0; break;
            case 8: row=2; column=1; break;
            case 9: row=2; column=2; break;
            default:
                cout<<"Invalid Move";
        }
        if(turn == 'X' && board[row][column] != 'X' && board[row][column] != 'O'){
            //updating the position for 'X' symbol if
            //it is not already occupied
            board[row][column] = 'X';
            turn = 'O';
        }else if(turn == 'O' && board[row][column] != 'X' && board[row][column] != 'O'){
            //updating the position for 'O' symbol if
            //it is not already occupied
            board[row][column] = 'O';
            turn = 'X';
        }else {
            //if input position already filled
            cout<<"Box already filled! Please choose another!!";
            player_turn();
        }
    }
    else if(turn == 'X'){
        cout<<"Player - 2 [X] turn : ";
        bestMove();
        cout << allTries << " tries" << endl;
        allTries = 0;
    }
}



void bestMove(){
    int bestScore = -INT_MAX;
    int score = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] != 'X' && board[i][j] != 'O')
            {
                char temp = board[i][j];
                board[i][j] = 'X';
                score = miniMax(board,0,'O', INT_MIN, INT_MAX);
                board[i][j] = temp;
                if(score > bestScore){
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
}

int miniMax(char board[3][3], int depth, char player, int use, int pass){
    int score;
    int bestScore;
    if(!gameover()) {
        if (xWin) {
            xWin = false;
            return 1;
        } else if (oWin) {
            oWin = false;
            return -1;
        } else{
            return 0;
        }
    }
    if(player == 'X'){
        bestScore = -INT_MAX;
        for(int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(board[i][j] != 'X' && board[i][j] != 'O')
                {
                    char temp = board[i][j];
                    board[i][j] = 'X';
                    score = miniMax(board,depth+1, 'O', -pass,-use);
                    board[i][j] = temp;
                    if(score > bestScore){
                        bestScore = score;
                    }
                    if(score > use){
                        use = score;
                    }
                    if(pass <= use){
                        break;
                    }
                    allTries++;
                }
            }
        }
        return bestScore;
    }else{
        bestScore = INT_MAX;
        for(int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(board[i][j] != 'X' && board[i][j] != 'O')
                {
                    char temp = board[i][j];
                    board[i][j] = 'O';
                    score = miniMax(board, depth+1, 'X', -use, -pass);
                    board[i][j] = temp;
                    if(score < bestScore){
                        bestScore = score;
                    }
                    if(score < pass){
                        use = score;
                    }
                    if(pass <= use){
                        break;
                    }
                    allTries++;
                }
            }
        }
        return bestScore;
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