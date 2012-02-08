#pragma once
#ifndef __PAWN_H__
#define __PAWN_H__

#include "Piece.h"

class Pawn : public Piece
{
    private:
        int dir;
        bool moved;
        bool jumped;
    
    public:
        Pawn(const Color &c = (BLANK), const Loc &l = (Loc(0, 0)), const PieceType &t = (PAWN), const int &val = (0x1), const std::string &n = ("Pawn"), const unsigned int &tabs = (0))
            : Piece::Piece(c, l, t, val, n), dir(c == WHITE ? 1 : -1), moved(false), jumped(false)
        {}

        virtual ~Pawn()
        {}

        virtual std::set< Loc > MoveList()
        {
            std::set< Loc > move_list;
            bool check = dir > 0 ? (loc.row + dir) < ROW_SIZE : dir < 0 ? (loc.row + dir) >= 0 : false;

            if(check)
                move_list.insert(Loc(loc.row + dir, loc.col));

            return move_list;
        }

        virtual std::string str() const
        {
            std::stringstream pawn_str;
            
            pawn_str << Piece::str();

            pawn_str << "\n\t" << RepeatSymbol< char >('\t', ptab_total) << "moved = " << moved;
            pawn_str << "\n\t" << RepeatSymbol< char >('\t', ptab_total) << "jumped = " << jumped;
            
            return pawn_str.str();
        }
};

#endif //__PAWN_H__
