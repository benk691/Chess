#pragma once
#ifndef __PIECE_H__
#define __PIECE_H__

#include <set>
#include "General.h"
#include "Move.h"
#include "Color.h"
#include "PieceType.h"

class Piece
{
    public:
        const PieceType ptype;
        const Color pcolor;
        const int points;
        std::string name;
        Loc loc;
        unsigned int ptab_total;
 
    public:
        Piece(const Color &c = (BLANK), const Loc &l = (Loc(0, 0)), const PieceType &t = (UNKNOWN), const int &val = (0), const std::string &n = ("Piece"), const unsigned int &tabs = (0))
            : ptype(t), pcolor(c), points(val), name(n), loc(l), ptab_total(tabs)
        {}

        Piece(const Piece &copy)
            : ptype(copy.ptype), pcolor(copy.pcolor), points(copy.points)
        {
            *this = copy;
        }

        virtual ~Piece()
        {}

        virtual std::set< Move > MoveList() = 0;

        virtual PieceType type() const
        {
            return ptype;
        }

        virtual Color color() const
        {
            return pcolor;
        }

        virtual int value() const
        {
            return points;
        }

        virtual std::string str() const
        {
            std::stringstream piece_str;

            piece_str << std::endl << RepeatSymbol< char >('\t', ptab_total) << name << " contents:";
            piece_str << std::endl << "\t" << RepeatSymbol< char >('\t', ptab_total) << "type = " << strPieceType(ptype);
            piece_str << std::endl << "\t" << RepeatSymbol< char >('\t', ptab_total) << "color = " << strColor(pcolor);
            piece_str << std::endl << "\t" << RepeatSymbol< char >('\t', ptab_total) << "points = " << points;
            piece_str << std::endl << "\t" << RepeatSymbol< char >('\t', ptab_total) << "loc.row = " << loc.row;
            piece_str << std::endl << "\t" << RepeatSymbol< char >('\t', ptab_total) << "loc.col = " << loc.col;

            return piece_str.str();
        }

        virtual Piece& operator=(const Piece &rhs)
        {
            if(this != &rhs)
            {
                name = rhs.name;
                loc = rhs.loc;
                ptab_total = rhs.ptab_total;
            }

            return *this;
        }
};

#endif //__PIECE_H__
