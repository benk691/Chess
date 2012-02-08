#pragma once
#ifndef __LOC_H__
#define __LOC_H__

#include <string>
#include <sstream>

struct Loc
{
    int row;
    int col;

    Loc(const int &r = (-1), const int &c = (-1))
        : row(r), col(c)
    {}

    Loc(const Loc &copy)
        : row(0), col(0)
    {
        *this = copy;
    }

    ~Loc()
    {}

    std::string str() const
    {
        std::stringstream display;
        
        display << "Loc(row = " << row << ", col = " << col << ")";

        return display.str();
    }

    Loc& operator=(const Loc &rhs)
    {
        if(this != &rhs)
        {
            row = rhs.row;
            col = rhs.col;
        }

        return *this;
    }

    bool operator==(const Loc &rhs) const
    {
        return row == rhs.row && col == rhs.col;
    }

    bool operator!=(const Loc &rhs) const
    {
        return row != rhs.row || col != rhs.col;
    }

    bool operator<(const Loc &rhs) const
    {
        return row == rhs.row ? col < rhs.col : row < rhs.row;
    }

    bool operator<=(const Loc &rhs) const
    {
        return row <= rhs.row;
    }

    bool operator>(const Loc &rhs) const
    {
        return row == rhs.row ? col > rhs.col : row > rhs.row;
    }

    bool operator>=(const Loc &rhs) const
    {
        return row >= rhs.row;
    }
};

#endif //__LOC_H__
