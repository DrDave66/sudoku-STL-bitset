//
//  RowCol.cpp
//  sudoku-STL
//
//  Created by Dave Landis on 11/28/21.
//  Copyright © 2021 Dave Landis. All rights reserved.
//

#include "RowCol.h"
RowCol::RowCol() {
    row = 15;
    col = 15;
}

RowCol::RowCol(uint8_t r, uint8_t c) {
    row = r;
    col = c;
}

RowCol::RowCol(const RowCol& rc) {
    row = rc.row;
    col = rc.col;

}

RowCol& RowCol::operator=(RowCol cpy) {
//    std::swap(*this, cpy);  // trade our resources for cpy's
    row = cpy.row;
    col = cpy.col;
    return *this;    // our (old) resources get destroyed with cpyb
}

void RowCol::set(uint8_t r, uint8_t c) {
    row = r;
    col = c;
}

string RowCol::toString() {
    static string retval = "";
    retval = "";
    retval += (char)('A' + row);
    retval += (char)('1' + col);
    return retval;
}

//inline int16_t RowCol::r() {return row;}
//inline int16_t RowCol::c() {return col;}

ostream& operator<< (ostream& os, const RowCol& rc) {
    RowCol rr(rc);
    os << rr.toString();
    return os;
}

