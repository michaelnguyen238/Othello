//
//  OthelloBoard.cpp
//  Project 2
//
//  Created by Michael Nguyen on 4/17/15.
//  Copyright (c) 2015 Michael Nguyen. All rights reserved.
//

#include <stdio.h>
#include "OthelloBoard.h"
#include <iostream>

using namespace std;

OthelloBoard::OthelloBoard() {
   
   mNextPlayer = OthelloBoard::Player::BLACK;
   mValue = 0;
   mPassCount = 0;
   
   mBoard[3][3] = -1;
   mBoard[3][4] = 1;
   mBoard[4][3] = 1;
   mBoard[4][4] = -1;
 

}

//Traverses the board. checks all directions, if it sees ENEMY piece, traverses
//in that direction until a friendly piece or an empty space is found
//if friendly piece found, the original spot is added as a possible move
//if no friendly piece found, continues on.
//30 Lines
void OthelloBoard::GetPossibleMoves(std::vector<OthelloMove *> *list) const {
   
   int rowIncrement, colIncrement, rowItr, colItr, r, c;
   
   for (rowItr = LOWER_BOUND; rowItr < BOARD_SIZE; rowItr++) {
      for (colItr = LOWER_BOUND; colItr < BOARD_SIZE; colItr++) {
         
         OthelloMove move(rowItr, colItr);
         
         if (mBoard[rowItr][colItr] != 0)
            continue;
         
         for (rowIncrement = -1; rowIncrement <= 1; rowIncrement++) {
            for (colIncrement = -1; colIncrement <= 1; colIncrement++) {

               r = move.mRow + rowIncrement;
               c = move.mCol + colIncrement;
               
               if (!InBounds(r, c))
                  continue;
               
               if (mBoard[r][c] == GetNextPlayer() * -1) {
                  while (InBounds(r, c) && mBoard[r][c] != 0 && mBoard[r][c]
                         != GetNextPlayer()) {
                     
                     if (rowIncrement == 0 && colIncrement == 0)
                        break;
                     
                     r += rowIncrement;
                     c += colIncrement;
                  }
               }

               /*
                If looking at current player and at a place that is in bounds,
                if we have move more than one space in either direction create
                a new move and point it at the current move.
                */
               if (mBoard[r][c] == GetNextPlayer() && InBounds(r, c)) {
                  if (abs(move.mRow - r) > 1 || abs(move.mCol - c) > 1) {
                     
                     if (list->size() > 0) {
                        if ((string)*list->back() == (string) move) {
                           continue;
                        }
                     }
                     list->push_back(new OthelloMove(move));
                  }
               }
            }
         }
      }
   }
   if (list->size() == 0)
      list->push_back(OthelloBoard::CreateMove());
}

//30 lines
void OthelloBoard::ApplyMove(OthelloMove *move) {
   
   if (!move->IsPass()) {
   
      mPassCount = 0;
      
      int rowIncrement, colIncrement, r, c;
   
      mBoard[move->mRow][move->mCol] = GetNextPlayer();
      mValue += GetNextPlayer();

      move->AddFlipSet(OthelloMove::FlipSet(GetNextPlayer(),0,0));
   
      for (rowIncrement = -1; rowIncrement <= 1; rowIncrement++) {
         for (colIncrement = -1; colIncrement <= 1; colIncrement++) {
            r = move->mRow + rowIncrement;
            c = move->mCol + colIncrement;
         
            while (InBounds(r, c) && mBoard[r][c] != 0 &&
                   mBoard[r][c] != GetNextPlayer()) {
            
               r += rowIncrement;
               c += colIncrement;
            }
         
            //If you are at a friendly piece and not where you started
            if ((int) mBoard[r][c] == GetNextPlayer() &&
                (r != move->mRow || c != move->mCol )) {
               
               /*
                While you are not where you started and you have moved more than
                one space in either direction and you are in bounds
                */
               while (!(r == move->mRow && c == move->mCol) &&
                      (abs(move->mRow - r) > 1 || abs(move->mCol - c) > 1) &&
                      InBounds(r, c)) {
                  
                  r -= rowIncrement;
                  c -= colIncrement;
                  move->AddFlipSet(OthelloMove::FlipSet
                                   (GetNextPlayer() * -1, r, c));
            
                  mBoard[r][c] = GetNextPlayer();
                  mValue += 2 * GetNextPlayer();
               }
            }
         }
      }
   }
   else {
      mPassCount++;
   }
   mNextPlayer = GetNextPlayer() * -1;
   mHistory.push_back(move);
}

/*
 Gets the move at the end of the mHistory vector. Reads that move's flipset 
 vector and flips them.
 */
void OthelloBoard::UndoLastMove() {
      
   OthelloMove *m = mHistory.back();
   int row = m->mRow;
   int col = m->mCol;
   int r, c;
   
   for (OthelloMove::FlipSet flip : m->mFlips) {

      
      r = flip.rowDelta;
      c = flip.colDelta;

      if (flip.rowDelta == 0 && flip.colDelta == 0) {
         mBoard[row][col] = 0;
         mValue += -flip.switched;
      }else {
      mBoard[r][c] = flip.switched;
      mValue += 2 * flip.switched;
      }
   }
   mNextPlayer = GetNextPlayer() * -1;
   delete mHistory.back();
   mHistory.pop_back();
}
