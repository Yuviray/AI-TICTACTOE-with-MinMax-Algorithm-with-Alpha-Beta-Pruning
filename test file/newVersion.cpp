#include <iostream>
#include <stdlib.h>
#include <limits>
#include <vector>

//definitions for max depth, X's eval function and O's eval function
#define deepEnough 2
#define plyrX 1
#define plyrO 2

using namespace std;

//structure used in the minimax function
struct Pathway {
    int value;
    vector<char *> PATH;
} path;

bool gameover(char *, bool &);
Pathway miniMax(char *, int , char, int, int);
void player_turn();
void display_board(char *);
int evaluate1(char *, char);
int evaluate2(char *, char);
int evaluate3(char *, char);
int evaluate4(char *, char);
vector<char *> moveGen(char *, char);
char opposite(char);
int determineEval(char);



//best path calculated so far
vector<char *> bestPath;

int main()
{
    //wanted to minimize global variables
    //some of these may go away depending on how the minimax algo works
    char *board = new char[9];
    for (int i = 0; i < 9; i++)
        board[i] = 'A'+i;
    int choice;
    int row,column;
    char turn = 'X';
    char player = 'X';
    bool draw = false;

    cout<<"TicTacToe"<<endl;

    while(!gameover(board, draw)){
        display_board(board);
        miniMax(board, 0, 'X', -(numeric_limits<int>::max()), numeric_limits<int>::max());
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
bool gameover(char *board, bool &draw) {
    for(int i=0; i<3; i++) {
        if(board[i] == board[i+3] == board[i+6])
            return true;
        if(board[(3*i)] == board[(3*i)+1] == board[(3*i)+2])
            return true;
        if(board[0] == board[4] == board[8] || board[2] == board[4] == board[6])
            return true;
    }

    for(int i=0; i<9; i++)
        if(board[i] != 'X' && board[i] != 'O')
            return false;

    draw = true;
    return true;
}

//returns a vector that is the list of board positions in the next ply of the tree
vector<char *> moveGen(char *board, char plyr) {
    vector<char *> moves;
    if (plyr == 'X') {
        for (int i = 0; i < 9; i++)
		{
			 if (board[i] == 'A') {
                board[i] = 'X';
				moves.push_back(board);
				board[i] = 'A';
			 }
		}
    }
    else {
        for (int i = 0; i < 9; i++)
		{
			 if (board[i] == 'A') {
                board[i] = 'O';
				moves.push_back(board);
				board[i] = 'A';
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

void display_board(char *board){
    cout<<"PLAYER - 1 [X] PLAYER - 2 [O]"<<endl;
    cout<<"     |     |     "<<endl;
    cout<<"  "<<board[0]<<"  | " <<board[1]<<"   |  "<<board[2]<<endl;
    cout<<"_____|_____|_____"<<endl;
    cout<<"     |     |     "<<endl;
    cout<<"  "<<board[3]<<"  | " <<board[4]<<"   |  "<<board[5]<<endl;
    cout<<"_____|_____|_____"<<endl;
    cout<<"     |     |     "<<endl;
    cout<<"  "<<board[6]<<"  | " <<board[7]<<"   |  "<<board[8]<<endl;
    cout<<"     |     |     "<<endl;
}


int evaluate1(char *board, char player){
    /*int maxi =0;
    int mini =0;

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
    */
    return 0;
}

int evaluate2(char *board, char player) {
    return 0;
}

int evaluate3(char *board, char player) {
    return 0;
}

int evaluate4(char *board, char player) {
    return 0;
}

//returns a Pathway structure. The structure could probably use a better name
Pathway miniMax(char *board, int depth, char plyr, int useThr, int passThr) {
    vector<char *> successors;
    int resultSucc, newValue;
    int evalFunc = determineEval(plyr);

    //if depth is deep enough, returns value of the current node back up the tree
    //not sure how to handle PATH=nil that is stated in the pseudocode yet, or what he means by that
    if (depth == deepEnough){
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
        if (successors.size() == 0) {
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
        for (char *succ : successors) {
            resultSucc = miniMax(succ, depth + 1, opposite(plyr), -passThr, -useThr).value;
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
