// Tic Tac Toe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "user.h"
#include "computer.h"
#include <cmath>
#include <ctime>

struct Board {
   int size;
   int **board;
};

int GetBoardSize();
bool IsPieceThere(Board &board, int spot);
void exit();
int VerifyInteger(int input, int minInput, int maxInput);

int main()
{
   cout << "\nWelcome!";
   while (PlayGame());

   exit();

   cout << "\n\n";
   return 0;
}

void exit() {
   cout << "\n\n\n\n\n\n\n";
   for (int j = 0; j < 55; j++) {
      cout << endl;
      for (int i = 0; i < 17; i++) {
         cout << "Bye";
      }
   }
}
bool PlayAgain() {
   cout << "\nWould you like to play again?";
   cout << "\n1. Yes\n2. No\n" << endl;
   cout << "Type the number associated with your choice: ";
   int choice;
   cin >> choice;
   VerifyInteger(choice, 1, 2);
   if (choice == 2) {
      return false;
   }
   else if (choice == 1) {
      return true;
   }
}

void PrintBoard(Board &board, char characters[]) {
   int spot = 0;
   for (int row = 0; row < board.size; row++) {
      cout << "\n";
      for (int col = 0; col < board.size; col++) {
         cout << "\t";
         int piece = board.board[col][row];
         if (piece == 1) {
            cout << characters[0];
         }
         else if (piece == 2) {
            cout << characters[1];
         }
         else {
            cout << spot;
         }
         spot++;
      }
      cout << "\n\n\n";
   }
}

void OutputWinner(int winner) {
   cout << "\n\n\n";
   if (winner == 1) {
      for (int i = 0; i < 6; i++) {
         cout << "User has won!\n";
      }
   }
   else if (winner == 2) {
      for (int i = 0; i < 6; i++) {
         cout << "Computer has won!\n";
      }
   }
   else {
      cout << "Nobody has won!\nKeep playing!\n";
   }
}
bool IsThereWinner(Board &board, int winRequirement) {
   int winnerH;
   int winnerV;
   int winnerD1;
   int winnerD2;
   int numberConnectedH;
   int numberConnectedV;
   int numberConnectedD1;
   int numberConnectedD2;

   for (int i = 0; i < board.size; i++) {
      cout << endl;
      winnerH = board.board[i][0];   //winnerH is actually vertical
      winnerV = board.board[0][i]; //winnerV is actually horizontal
      winnerD1 = board.board[0][0];
      winnerD2 = board.board[board.size - 1][0];
      numberConnectedD1 = 0;
      numberConnectedD2 = 0;
      numberConnectedH = 0; //Vertical
      numberConnectedV = 0; //Horizontal
      for (int j = 0; j < board.size; j++) {
         if (winnerH == board.board[i][j]) {
            numberConnectedH++;
         }
         else {
            winnerH = board.board[i][j];
            numberConnectedH = 0;
         }

         if (winnerV == board.board[j][i]) {
            numberConnectedV++;
         }
         else {
            winnerV = board.board[j][i];
            numberConnectedV = 0;
         }

         if (i + j < board.size) {
            if (winnerD1 == board.board[j][j + i]) {
               numberConnectedD1++;
            }
            else {
               winnerD1 = board.board[j][j + i];
               numberConnectedD1 = 0;
            }
         }
         if (i + j < board.size) {
            if (winnerD2 == board.board[board.size - j - 1][j + i]) {
               numberConnectedD2++;
            }
            else {
               winnerD2 = board.board[board.size - j - 1][j + i];
               numberConnectedD2 = 0;
            }
         }

         /*
         cout << "winnerD1: " << winnerD1;
         cout << " winnerD2: " << winnerD2;
         cout << " winnerH: " << winnerH;
         cout << " winnerV: " << winnerV << endl;

         cout << "numberConnectedD1: " << numberConnectedD1;
         cout << " numberConnectedD2: " << numberConnectedD1;
         cout << " numberConnectedH: " << numberConnectedD1;
         cout << " numberConnectedV: " << numberConnectedD1;
         */


         if (numberConnectedD1 >= winRequirement && winnerD1 != 0) {
            OutputWinner(winnerD1);
            return true;
         }
         else if (numberConnectedD2 >= winRequirement && winnerD2 != 0) {
            OutputWinner(winnerD2);
            return true;
         }
         else if (numberConnectedH >= winRequirement && winnerH != 0) {
            OutputWinner(winnerH);
            return true;
         }
         else if (numberConnectedV >= winRequirement && winnerV != 0) {
            OutputWinner(winnerV);
            return true;
         }
      }
   }
   return false;
}
int VerifyInteger(int input, int minInput, int maxInput) {
   if (cin.fail()) {
      cout << "That's not a number.";
      cout << "\nPlease enter a whole number: ";
      cin.clear();
      cin.ignore(99999, '\n');
      cin >> input;
      return VerifyInteger(input, minInput, maxInput);
   }
   if (input < minInput) {
      cout << "\nInput is too small.";
      cout << "\nEnter a number greater than or equal to " << minInput << ": ";
      cin >> input;
      return VerifyInteger(input, minInput, maxInput);
   }
   if (input > maxInput) {
      cout << "\nInput is too large.";
      cout << "\nEnter a number smaller than or equal to " << maxInput << ": ";
      cin >> input;
      return VerifyInteger(input, minInput, maxInput);
   }
   return input;
}

void MakeBoard(Board &board) {
   board.size = GetBoardSize();
   board.board = new int *[board.size];

   for (int col = 0; col < board.size; col++) {
      board.board[col] = new int[board.size];
      for (int row = 0; row < board.size; row++) {
         board.board[col][row] = 0;
         //cout << board.board[col][row];
      }
   }
}
int GetWinRequirement(int boardSize) {
   cout << "\n\nYou now get to choose how many 'in a row' are needed to claim victory.";
   cout << "\n\nPlease enter how many connected spots are needed to win: ";
   int spots;
   cin >> spots;
   spots = VerifyInteger(spots, 1, boardSize);
   return spots;
}
int GetBoardSize() {
   cout << "\n\nThe Tic Tac Toe board can have any number of rows.\n";
   //   cout << "You will get to choose how many in a line you need to win.\n";
   cout << "\nPlease enter the number of rows on the board: ";
   int boardSize;
   cin >> boardSize;
   boardSize = VerifyInteger(boardSize, 1, 11111);
   if (boardSize > 9) {
      cout << "That's a lot. Are you sure?";
      cout << "\n1. Yes\n2. No, enter a different number" << endl;
      cout << "\nEnter your choice: ";
      int choice;
      cin >> choice;
      choice = VerifyInteger(choice, 1, 2);
      if (choice == 2) {
         return GetBoardSize();
      }
   }

   return boardSize;
}

bool PlayGame() {
   char characters[] = { ChooseYourCharacter(), ChooseComputerCharacter(userLetter) };
   //userLetter = ChooseYourCharacter();
   //computerLetter = ChooseComputerCharacter(userLetter);

   Board theBoard;

   Board &board = theBoard; //Make a reference to the board so that we don't have to keep passing it around.
   MakeBoard(board);
   int winRequirement = GetWinRequirement(board.size);
   //MakeBoard(board.size);

   while (!IsThereWinner(board, winRequirement)) {
      PrintBoard(board, characters);
      PlayUser(board);
      if (IsThereWinner(board, winRequirement)) {
         break;
      }
      PlayComputer(board);
   }

   if (board.size < 5) {
      PrintBoard(board, characters);
   }

   return PlayAgain();

   return false;
}

void PutPiece(bool isUser, Board &board, int spot) {
   int row = spot / board.size;
   int col = spot % board.size;
   int player; //1 is user, 2 is computer

   if (isUser) {
      player = 1;
   }
   else if (!isUser) {
      player = 2;
   }
   else {
      cout << "\n\n\n\n\nOh crap, something went wrong.";
      exit(EXIT_FAILURE);
   }

   board.board[col][row] = player;
}

void PlayUser(Board &board) {
   cout << "\nYour move: ";
   int userMove;
   cin >> userMove;
   userMove = VerifyInteger(userMove, 0, (board.size * board.size));
   while (IsPieceThere(board, userMove)) {
      cout << "\nPiece already there.";
      cout << "\nChoose other spot: ";
      cin.clear();
      cin.ignore(9999, '\n');
      cin >> userMove;
      userMove = VerifyInteger(userMove, 1, (board.size * board.size));
   }
   PutPiece(true, board, userMove);
}
void PlayComputer(Board &board) {
   int randomSpot;
   srand(time(NULL));
   do {
      randomSpot = rand() % (board.size * board.size);
   } while (IsPieceThere(board, randomSpot));
   cout << "\n\n\nComputer placed a piece on ";
   cout << randomSpot << ".";
   PutPiece(false, board, randomSpot);
}

char ChooseYourCharacter() {
   cout << endl << "\nYou get to choose what character you place on the board!\nType your character of choice: ";
   char character;
   cin >> character;
   cin.clear();
   cin.ignore(9999999, '\n');
   cout << "Your character is \"" << character << "\"";
   while (static_cast<int>(character) >= 48 && static_cast<int>(character) <= 57) {
      cout << "\n\nPlease choose something that isn't a number.\n";
      return ChooseYourCharacter(); //Doing this recursivley just because. It's not efficient and will use more RAM than necessary.
   }

   return character;
}
char ChooseComputerCharacter(char userLetter) {
   do {
      srand(time(NULL));
      computerLetter = char(rand() % 67 + 58);
   } while (computerLetter == userLetter);   //Not working, fix this
   cout << "\n\nComputer is: \"" << computerLetter << "\"";
   return computerLetter;
}

bool IsPieceThere(Board &board, int spot) {
   int row = spot / board.size;//  cout << "\nrow: " << row;
   int col = spot % board.size;//  cout << "\ncol: " << col << endl;

   if (board.board[col][row] != 0) {
      //cout << "\nPiece there is: " << board.board[col][row];
      return true;
   }
   else {
      return false;
   }
}
