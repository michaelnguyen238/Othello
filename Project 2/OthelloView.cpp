//
//  OthelloView.cpp
//  Project 2
//
//  Created by Michael Nguyen on 4/17/15.
//  Copyright (c) 2015 Michael Nguyen. All rights reserved.
//

#include <stdio.h>
#include "OthelloView.h"
#include <iostream>

using namespace std;

void OthelloView::PrintBoard(std::ostream &s) const{
   cout << "- 0 1 2 3 4 5 6 7";
   
   for ( int i = LOWER_BOUND; i < BOARD_SIZE; i++) {
      cout << "\n" << i << " ";
      for( int j = LOWER_BOUND; j < BOARD_SIZE; j++) {
         char temp = mOthelloBoard->mBoard[i][j];
         if (temp == 0)
            cout << ". ";
         
         else if (temp == 1)
            cout << "B ";
         
         else if (temp == -1)
            cout << "W ";
      }
   }
   cout << endl;
}

std::ostream& operator<< (std::ostream &lhs, const OthelloView &rhs) {
   rhs.PrintBoard(lhs);
   
   return lhs;
}