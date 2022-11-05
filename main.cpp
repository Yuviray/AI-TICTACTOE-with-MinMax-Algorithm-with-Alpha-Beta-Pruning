#include <iostream>
#include <stdlib.h>
using namespace std;

char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
int choice;
int row,column;
char turn = 'X';
char player = 'X';
char opponent = 'x';
bool draw = false;



int evaluate1(char board[3][3]){
    int maxi =0;
    int mini =0;

    for(int row =0; row<3; row++){
        if(board[row][0]!= opponent && board[row][1]!= opponent && board[row][2]!= opponent){
            maxi++;
        }
        if(board[row][0]!= player && board[row][1]!= player && board[row][2]!= player){
            mini++;
        }
    }
    for(int col =0; col<3; col++){
        if(board[0][col]!= opponent && board[1][col]!= opponent && board[2][col]!= opponent){
            maxi++;
        }
        if(board[0][col]!= player && board[1][col]!= player && board[2][col]!= player){
            mini++;
        }
    }
    if(board[0][0]!= opponent && board[1][1]!= opponent && board[2][2]!= opponent){
        maxi++;
    }
    if(board[0][0]!= player && board[1][1]!= player && board[2][2]!= player){
        mini++;
    }
    if(board[0][2]!= opponent && board[1][1]!= opponent && board[2][0]!= opponent){
        maxi++;
    }
    if(board[0][2]!= player && board[1][1]!= player && board[2][0]!= player){
        mini++;
    }

    return maxi-mini;
}


void display_board(){
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


void player_turn(){
    if(turn == 'X'){
        cout<<"Player -[X] turn : ";

    }
    else if(turn == 'O') {
        cout << "Player -[O] turn : ";
    }
    cin>> choice;
    cout<<endl;
    cout<<evaluate1(board);

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
        board[row][column] = 'X';
        turn = 'O';
    }else if(turn == 'O' && board[row][column] != 'X' && board[row][column] != 'O'){
        board[row][column] = 'O';
        turn = 'X';
    }else {

        cout<<"Box already filled!n Please choose another!!nn";
        player_turn();
    }

    display_board();
}



bool gameover(){
    for(int i=0; i<3; i++)
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return false;
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return false;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return true;

    draw = true;
    return false;
}

int main()
{
    cout<<"TicTacToe"<<endl;
    while(gameover()){
        display_board();
        player_turn();
        gameover();
    }
    if(turn == 'X' && draw == false){
        cout<<"Player 'X' has won the game";
    }
    else if(turn == 'O' && draw == false){
        cout<<"Player 'O' has won the game";
    }
    else
        cout<<"GAME DRAW";
}
