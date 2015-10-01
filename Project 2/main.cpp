#include "OthelloExceptions.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
int main(int argc, char* argv[]) {
   
   // Initialization
   OthelloBoard board; // the state of the game board
   OthelloView v(&board); // a View for outputting the board via operator<<
   string userInput; // a string to hold the user's command choice
   vector<OthelloMove *> possMoves; // a holder for possible moves


   do {
      
      string command1, command2;
      //Clearing possible moves and freeing memory
      for (OthelloMove *move : possMoves) {
         delete move;
      }
      possMoves.clear();

      istringstream iss;
      bool isValidMove = false;
      cout << v << endl;
      
      board.GetPossibleMoves(&possMoves);
      
      cout << "Possible moves for " << ((board.GetNextPlayer() == -1) ? "White: " : "Black: ") << endl;
      for (OthelloMove *move : possMoves) {
         cout << (string) *move << " ";
      }
      cout << endl;

      cout << "Enter a command" << endl;
   
      getline(cin, userInput);
      iss.str(userInput);
      iss >> command1;

      if (command1 == "move") {
         
         iss >> command2;
         
         OthelloMove *m = board.CreateMove();
         
         try {
            
            *m = command2;
         
            for (OthelloMove *move : possMoves) {
               if (*m == *move) {
                  isValidMove = true;
               }
            }
            
            if (isValidMove){
               board.ApplyMove(m);
            }
            else {
               cout << "Not a valid move." << endl;
               delete m;
               continue;
            }
         }
         catch (OthelloException e) {
            cout << e.what() << endl;
            delete m;
         }
         
      }
      else if (command1 == "undo") {
         int times;
         
         iss >> times;
         
         for (int i = times; i > 0; i --) {
            if (board.GetMoveHistory()->size() == 0)
               break;
            else
               board.UndoLastMove();
         }
      }
      else if (command1 == "showValue") {
         cout << "Board value: " << board.GetValue() << endl << endl;
      }
      else if (command1 == "showHistory") {
         vector<OthelloMove *> hist = *board.GetMoveHistory();
         int player = board.GetNextPlayer() * -1;
         
         vector<OthelloMove *>::reverse_iterator rItr = hist.rbegin();

         for (int i = 0; i < hist.size(); i++) {
            cout << ((player == -1) ? "White: " : "Black: ") <<
             (string) *(*rItr) << endl;
            
            player = -1 * player;
            rItr++;
         }
      }
      else if (command1 == "quit") {
         break;
      }
      
      if (board.IsFinished())
         delete possMoves.back();
      

   } while (!board.IsFinished());
   
   if (board.GetValue() > 0) {
      cout << "Black wins!" << endl;
   }
   else if (board.GetValue() < 0) {
      cout << "White wins!" << endl;
   }
   else {
      cout << "It's a tie! :(" << endl;
   }
}