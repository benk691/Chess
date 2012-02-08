#pragma once
#ifndef __ROOK_H__
#define __ROOK_H__

#include "Piece.h"

class Rook : public Piece
{
    private:
        bool moved;
    
    public:
        Rook(const Color &c = (BLANK), const Loc &l = (Loc(0, 0)), const PieceType &t = (ROOK), const int &val = (0x5), const std::string &n = ("Rook"), const unsigned int &tabs = (0))
            : Piece::Piece(c, l, t, val, n), moved(false)
        {}

        virtual ~Rook()
        {}

        virtual std::set< Loc > MoveList()
        {
            std::set< Loc > move_list;

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

        virtual std::string str() const
        {
            std::stringstream rook_str;
            
            rook_str << Piece::str();

            rook_str << "\n\t" << RepeatSymbol< char >('\t', ptab_total) << "moved = " << moved;
            
            return rook_str.str();
        }
};

#endif //__ROOK_H__
