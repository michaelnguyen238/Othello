//
//  OthelloMove.cpp
//  Project 2
//
//  Created by Michael Nguyen on 4/17/15.
//  Copyright (c) 2015 Michael Nguyen. All rights reserved.
//

#include <stdio.h>
#include "OthelloMove.h"
#include "OthelloExceptions.h"
#include <sstream>
#include <string>

using namespace std;

int OthelloMove::mOnHeap = 0;
int BOARD_SIZE = 8;
int LOWER_BOUND = 0;

OthelloMove::OthelloMove() {
   mRow = -1;
   mCol = -1;
}

OthelloMove::OthelloMove(int row, int col) : mRow(row), mCol(col) {}

OthelloMove& OthelloMove::operator=(const std::string &rhs) {
   
   istringstream iss(rhs);
   
   if (rhs == "pass") {
      mRow = -1;
      mCol = -1;
      return *this;
   }
   
   char buffer;
   
   iss >> buffer >> mRow >> buffer >> mCol >> buffer;
   
   if (mRow >= BOARD_SIZE || mRow < LOWER_BOUND
       || mCol >= BOARD_SIZE || mCol < LOWER_BOUND) {
      throw OthelloException("Move is out of bounds");
   }
   
   return *this;
}

bool operator==(const OthelloMove &lhs, const OthelloMove &rhs) {
   return (lhs.mRow == rhs.mRow) && (lhs.mCol == rhs.mCol);
}

OthelloMove::operator std::string() const {
   if (IsPass()) {
      return "pass";
   }
   ostringstream oss;
   oss << "(" << mRow << "," << mCol << ")";
   
   return oss.str();
}