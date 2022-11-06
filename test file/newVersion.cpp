#include <iostream>
#include <stdlib.h>
#include <limits>
#include <vector>

//definitions for max depth, X's eval function and O's eval function
#define deepEnough 2
#define plyrX 1
#define plyrO 2

using namespace std;

bool gameover(bool &);
int miniMax(char **, int , char, int, int, int);
void player_turn();
void display_board();
int evaluate1(char **);
vector<char [9]> moveGen(char **, char);
char opposite(char);
int determineEval(char);

//structure used in the minimax function
struct Pathway {
    int value;
    vector<char **> PATH;
}

//structure containing value of the lowest node and the path to get there
Pathway path;
//best path calculated so far
vector<char **> bestPath;

int main()
{
    //wanted to minimize global variables
    //some of these may go away depending on how the minimax algo works
    char board[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = 'A';
    int choice;
    int row,column;
    char turn = 'X';
    char player = 'X';
    char opponent = 'O';
    bool draw = false;

    cout<<"TicTacToe"<<endl;

    while(!gameover()){
        display_board();
        player_turn();
        gameover();
    }
    if(turn == 'O' && draw == false){
        cout<<"Player 'X' has won the game";
    }
    else if(turn == 'X' && draw == false){
        cout<<"Player 'O' has won the game";
    }
    else
        cout<<"GAME DRAW";
}

//tweaked this one a little bit. i felt like gameover should be true when the game ended
bool gameover(bool &draw) {
    for(int i=0; i<3; i++) {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return true;
        if(board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
            return true;
    }

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return false;

    draw = true;
    return true;        
}

//returns a vector that is the list of board positions in the next ply of the tree
vector<char **> moveGen(char **pos, char plyr) {
    vector<char **> moves;
    if (plyr == 'X') {
        for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++) {
                if (board[i][j] == 'A') {
				board[i][j] = 'X';
				moves.push_back(board);
				board[i][j] = 'A';
			}
            }
            
		}
    }
    else {
        for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++) {
                if (board[i][j] == 'A') {
				board[i][j] = 'O';
				moves.push_back(board);
				board[i][j] = 'A';
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

//returns a Pathway structure. The structure could probably use a better name
Pathway miniMax(char **pos, int depth, char plyr, int useThr, int passThr) {
    vector<char **> successors;
    int resultSucc, newValue;
    int evalFunc = determineEval(plyr);

    //if depth is deep enough, returns value of the current node back up the tree
    //not sure how to handle PATH=nil that is stated in the pseudocode yet, or what he means by that
    if (depth == deepEnough){
        switch (evalFunc) {
            case 1:
                path.value = evaluate1(pos);
                return path;
            case 2:
                path.value = evaluate(pos);
                return path;
            case 3:
                path.value = evaluate3(pos);
                return path;
            case 4:
                path.value = evaluate4(pos);
                return path;
        }
    }
    //step 2 in the psuedocode
    else {
        successors = moveGen(pos, plyr);
        //step 3 in the pseudocode
        if (successors.size() == 0) {
            switch (evalFunc) {
                case 1:
                    path.value = evaluate1(pos);
                    return path;
                case 2:
                    path.value = evaluate(pos);
                    return path;
                case 3:
                    path.value = evaluate3(pos);
                    return path;
                case 4:
                    path.value = evaluate4(pos);
                    return path;
            }
        }
        //step 4 in the pseudocode
        for (char **succ : successors) {
            resultSucc = miniMax(succ, depth + 1, opposite(plyr), -passThr, -useThr);
            newValue = -resultSucc;
            if (newValue > passThr) {
                passThr = resultSucc;
                bestPath = path.PATH;
                bestPath.push_back(succ);
            }
            if (passThr >= useThr) {
                path.PATH = bestPath;
                return path;
            }
        }
        //step 5 in the pseudocode
        return path;
    }
        
}