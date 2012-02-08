#pragma once
#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "Piece.h"

class Queen : public Piece
{
    public:
        Queen(const Color &c = (BLANK), const Loc &l = (Loc(0, 0)), const PieceType &t = (QUEEN), const int &val = (0x9), const std::string &n = ("Queen"), const unsigned int &tabs = (0))
            : Piece::Piece(c, l, t, val, n)
        {}

        virtual ~Queen()
        {}

        virtual std::set< Loc > MoveList()
        {
            std::set< Loc > move_list;
            
            // Bishop Movement
            // Move towards row 8 col h
            for(int row_pos = loc.row + 1, col_pos = loc.col + 1; (row_pos + 1) < ROW_SIZE && (col_pos + 1) < COL_SIZE; ++row_pos, ++col_pos)
                move_list.insert(Loc(row_pos, loc.col));

            // Move towards row 8 col a
            for(int row_pos = loc.row + 1, col_pos = loc.col - 1; (row_pos + 1) < ROW_SIZE && (col_pos - 1) >= 0; ++row_pos, --col_pos)
                move_list.insert(Loc(row_pos, loc.col));

            // Move towards row 1 col h
            for(int row_pos = loc.row - 1, col_pos = loc.col + 1; (row_pos - 1) >= 0 && (col_pos + 1) < COL_SIZE; --row_pos, ++col_pos)
                move_list.insert(Loc(row_pos, loc.col));

            // Move towards row 1 col a
            for(int row_pos = loc.row - 1, col_pos = loc.col - 1; (row_pos - 1) >= 0 && (col_pos - 1) >= 0; --row_pos, --col_pos)
                move_list.insert(Loc(row_pos, loc.col));

            // Rook Movement
            // Move towards row 8
            for(int row_pos = loc.row + 1; (row_pos + 1) < ROW_SIZE; ++row_pos)
                move_list.insert(Loc(row_pos, loc.col));

            // Move towards row 1
            for(int row_pos = loc.row - 1; (row_pos - 1) >= 0; --row_pos)
                move_list.insert(Loc(row_pos, loc.col));

            // Move towards col h
            for(int col_pos = loc.col + 1; (col_pos + 1) < COL_SIZE; ++col_pos)
                move_list.insert(Loc(loc.row, col_pos));

            // Move towards col a
            for(int col_pos = loc.col - 1; (col_pos - 1) >= 0; --col_pos)
                move_list.insert(Loc(loc.row, col_pos));

            return move_list;
        }
};

#endif //__QUEEN_H__
