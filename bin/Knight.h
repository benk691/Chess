#pragma once
#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "Piece.h"

class Knight : public Piece
{
    public:
        Knight(const Color &c = (BLANK), const Loc &l = (Loc(0, 0)), const PieceType &t = (KNIGHT), const int &val = (0x3), const std::string &n = ("Knight"), const unsigned int &tabs = (0))
            : Piece::Piece(c, l, t, val, n)
        {}

        virtual ~Knight()
        {}

        virtual std::set< Loc > MoveList()
        {
            std::set< Loc > move_list;

            if((loc.row + 1) < ROW_SIZE && (loc.col + 2) < COL_SIZE)
                move_list.insert(Loc(loc.row + 1, loc.col + 2));
            
            if((loc.row + 1) < ROW_SIZE && (loc.col - 2) >= 0)
                move_list.insert(Loc(loc.row + 1, loc.col - 2));

            if((loc.row - 1) >= 0 && (loc.col + 2) < COL_SIZE)
                move_list.insert(Loc(loc.row - 1, loc.col + 2));

            if((loc.row - 1) >= 0 && (loc.col - 2) >= 0)
                move_list.insert(Loc(loc.row - 1, loc.col - 2));

            if((loc.row + 2) < ROW_SIZE && (loc.col + 1) < COL_SIZE)
                move_list.insert(Loc(loc.row + 2, loc.col + 1));
            
            if((loc.row + 2) < ROW_SIZE && (loc.col - 1) >= 0)
                move_list.insert(Loc(loc.row + 2, loc.col - 1));

            if((loc.row - 2) >= 0 && (loc.col + 1) < COL_SIZE)
                move_list.insert(Loc(loc.row - 2, loc.col + 1));

            if((loc.row - 2) >= 0 && (loc.col - 1) >= 0)
                move_list.insert(Loc(loc.row - 2, loc.col - 1));

            return move_list;
        }
};

#endif //__KNIGHT_H__
