#pragma once
#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "Piece.h"

class Bishop : public Piece
{
    public:
        Bishop(const Color &c = (BLANK), const Loc &l = (Loc(0, 0)), const PieceType &t = (BISHOP), const int &val = (0x3), const std::string &n = ("Bishop"), const unsigned int &tabs = (0))
            : Piece::Piece(c, l, t, val, n)
        {}

        virtual ~Bishop()
        {}

        virtual std::set< Loc > MoveList()
        {
            std::set< Loc > move_list;

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

            return move_list;
        }
};

#endif //__BISHOP_H__
