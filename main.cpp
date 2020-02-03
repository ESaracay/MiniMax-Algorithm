/*Evan Saracay
 * CS106B
 * Extra Credit
 * This program utilizes the minimax algorithm in order to win a game of Tic-Tac-Toe.
 * */
#include "strlib.h"
#include "grid.h"
#include "string.h"
#include "console.h"
#include "simpio.h"
#include <iostream>
using namespace std;
void printGame(const array<string,9>&  board);
int evaluateScore(const array<string,9>& board, string compare);
int computeScore(const array<string,9>& board);
void printCoordinates(const array<string,9>& board);
void chooseMove(array<string,9>& myboard);
int arrayisEmpty(const array<string,9>& board);
int maxComputer(array<string,9> myboard);
int miniHuman(array<string,9> myboard);
int computerMove(array<string,9> myboard);
int main(){
    int num1 = getInteger("Press one to play game");
    if(num1 == 1){
        array<string,9> myboard = {" "," "," "," "," "," "," "," "," "};
        array<string,9> example = {"0","1","2","3","4","5","6","7","8"};
        printGame(example);
        while (computeScore(myboard)==0){
            chooseMove(myboard);
         }
    cout<<computeScore(myboard);
    }else{
        main();
    }
    return 1;
}
// miniHuman and maxComputer are my mutually recursive functions
// This recursive function models the moves that player would make
int miniHuman(array<string,9> myboard){
    int sum = 0;
    if(arrayisEmpty(myboard)){
        return computeScore(myboard);
    }else{
        for(int i =0; i<9;i++){
            if(myboard[i]==" "){
              myboard[i]="X";
              sum+= maxComputer(myboard);
              myboard[i]=" ";
            }
        }
        return sum;
    }
}
// This recursive Function models the moves that the computer could make
int maxComputer(array<string,9> myboard){
   int sum = 0;
    if(arrayisEmpty(myboard)){
        return computeScore(myboard);
    }else{
        for(int i =0; i<9;i++){
            if(myboard[i]==" "){
              myboard[i]="O";
              sum+= miniHuman(myboard);
              myboard[i]=" ";
            }
        }
        return sum;
    }
}
// This function asks user for move
void chooseMove(array<string,9>& myboard){
    int num1 = getInteger("Make your move and enter a number if you dare:");
    // make sure the number is realistic and the spot is empty
    if(num1 <= 8 && myboard[num1]!= "X" && myboard[num1]!="O"){
        myboard[num1]="X";
    }else{
        cout<<"That was not in Bounds"<<endl;
        chooseMove(myboard);
    }
    // here we let computer make move and then print the board
    if(computeScore(myboard)!=0){
        cout<<"Game Over!"<<endl;
    }
    myboard[computerMove(myboard)] = "O";
    printGame(myboard);
    if (computeScore(myboard)!=0){
        cout<<"computer:"<<"This is way to easy"<<"Humans are stupid"<<endl;
        main();
    }
    // game is over if all spaces are filled or score is not 0
    if(computeScore(myboard)!=0){
        cout<<"Game Over!"<<endl;
        main();
    }
}
// This function calls all the possible paths the computer can make
// and returns the path with the best outcome
int computerMove(array<string,9> myboard){
    // run maxcomputer on all emptyspots and take the path that returns the biggest number
    // maxvalue and possiblemax is negative just in case all the scenarios are a loss
    int maxValue =-100000;
    int maxIndex =0;
    int possibleMax = -100000;
    for(int i=0;i<9;i++){
        if(myboard[i]==" "){
           myboard[i]="O";
           possibleMax= miniHuman(myboard);
           cout<<"max val"<<miniHuman(myboard)<<endl;
           myboard[i]=" ";
        }
        if (possibleMax>maxValue){
            maxIndex = i;
            maxValue = possibleMax;
        }
    }
    return maxIndex;
}
// checks if the array no longer has a value
int arrayisEmpty(const array<string,9>& board){
    for(int i =0; i<9; i++){
        if (board[i]== " "){
            return false;
        }
    }
    return true;
}
void printGame(const array<string,9>& board){
    for(int i =0; i<3; i++){
        cout<< board[i*3]<<" | "<< board[i*3+1]<<" | "<<board[i*3+2]<<endl;
        if(i!=2){
        cout<<"-----------"<<endl;
        }
    }
}
// calls evaluate Score for both O and X and applies the utility/penalties
int computeScore(const array<string,9>& board){
    int scoreO= evaluateScore(board, "OOO");
    int scoreX= evaluateScore(board, "XXX");
    if (scoreO > scoreX){
        return 10;
    }else if (scoreX>scoreO){
        return -10;
    }else{
        return 0;
    }
}
// This is the function that evaluates if either O or X has won the game
int evaluateScore(const array<string,9>& board, string compare){
 // lets check rows for a score and columns and return 1 if we win
    string inARow = "";
    string inAColumn ="";
    for (int i = 0; i<3;i++){
        inARow =  board[i*3]+ board[i*3+1]+board[i*3+2];
        inAColumn= board[i]+ board[i+3]+board[i+6];
        if (inARow == compare){
            return 1;
        }else if (inAColumn == compare){
            return 1;
        }else{
            inARow ="";
            inAColumn ="";
        }
    }
    // check the diagnols for a win
    string diagnolOne ="";
    string diagnolTwo = "";
    diagnolOne = board[0]+board[4]+board[8];
    diagnolTwo = board[2]+board[4]+board[6];
    if (diagnolOne==compare){
        return 1;
    }
    else if (diagnolTwo==compare){
        return 1;
    }
    else{

        return 0;
    }
}
