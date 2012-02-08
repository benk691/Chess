#pragma once
#ifndef __KING_H__
#define __KING_H__

#include "Piece.h"

class King : public Piece
{
    private:
        bool moved;
    
    public:
        King(const Color &c = (BLANK), const Loc &l = (Loc(0, 0)), const PieceType &t = (KING), const int &val = (0xF), const std::string &n = ("King"), const unsigned int &tabs = (0))
            : Piece::Piece(c, l, t, val, n), moved(false)
        {}

        virtual ~King()
        {}

        virtual std::set< Loc > MoveList()
        {
            std::set< Loc > move_list;

            if((loc.row + 1) < ROW_SIZE)
                move_list.insert(Loc(loc.row + 1, loc.col));
            
            if((loc.row - 1) >= 0)
                move_list.insert(Loc(loc.row - 1, loc.col));
            
            if((loc.col + 1) < COL_SIZE)
                move_list.insert(Loc(loc.row, loc.col + 1));
            
            if((loc.col - 1) >= 0)
                move_list.insert(Loc(loc.row, loc.col - 1));

            if((loc.row + 1) < ROW_SIZE && (loc.col + 1) < COL_SIZE)
                move_list.insert(Loc(loc.row + 1, loc.col + 1));

            if((loc.row - 1) >= 0 && (loc.col + 1) < COL_SIZE)
                move_list.insert(Loc(loc.row - 1, loc.col + 1));

            if((loc.row + 1) < ROW_SIZE && (loc.col - 1) >= 0)
                move_list.insert(Loc(loc.row + 1, loc.col - 1));

            if((loc.row - 1) >= 0 && (loc.col - 1) >= 0)
                move_list.insert(Loc(loc.row - 1, loc.col - 1));

            return move_list;
        }

        virtual std::string str() const
        {
            std::stringstream king_str;
            
            king_str << Piece::str();

            king_str << "\n\t" << RepeatSymbol< char >('\t', ptab_total) << "moved = " << moved;
            
            return king_str.str();
        }
};

#endif //__KING_H__
