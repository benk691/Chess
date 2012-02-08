#pragma once
#ifndef __MOVE_H__
#define __MOVE_H__

#include "PieceType.h"

/* Compass:
 *
 *                N (0, 1)
 *                ^
 *                |
 * W (-1, 0) <----.----> E (1, 0)
 *                |
 *                Y
 *                S
 */

struct Move
{
    Loc start_loc;
    Loc end_loc;
    int x_dir;
    int y_dir;
    PieceType piece_type;
    std::string move_str;
    bool valid;
    unsigned int tab_total;

    Move(const Loc &sl = (Loc()), const Loc &el = (Loc()), const int x = (0), const int y = (0), const PieceType &pt = (UNKNOWN), const std::string &mv = (""), const bool &v = (false))
        : start_loc(sl), end_loc(el), piece_type(pt), move_str(mv), valid(v), tab_total(0)
    {}

    Move(const Move &copy)
    {
        *this = copy;
    }

    std::string str() const
    {
        std::stringstream buf;

        buf << std::endl << RepeatSymbol< char >('\t', tab_total) << "Move contents:";

        buf << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "start_loc = " << start_loc.str();

        buf << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "end_loc = " << end_loc.str();

        buf << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "piece_type = " << strPieceType(piece_type);

        buf << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "move_str = \"" << move_str << "\"";

        buf << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "valid = " << valid;

        return buf.str();
    }

    Move& operator=(const Move &rhs)
    {
        if(this != &rhs)
        {
            start_loc = rhs.start_loc;
            end_loc = rhs.end_loc;
            piece_type = rhs.piece_type;
            move_str = rhs.move_str;
            valid = rhs.valid;
            tab_total = rhs.tab_total;
        }

        return *this;
    }
};

#endif //__MOVE_H__
