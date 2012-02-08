#pragma once
#ifndef __BOARD_H__
#define __BOARD_H__

#include "Space.h"
#include "PieceDefs.h"
#include "Player.h"

class Board
{
    private:
        // Need triple pointer so that const color of the space can be set correctly, and not be set to BLANK.
        Space*** space;
        unsigned int btab_total;
    
    public:
        Board(const unsigned int &tabs = (0))
            : btab_total(tabs)
        {
            initSpaces();
        }

        Board(const Board &copy)
            : space(NULL), btab_total(0)
        {
            *this = copy;
        }

        ~Board()
        {
            clear();
        }

        void clear()
        {
            clearSpaces();
        }

        void setTabTotal(const unsigned int tabs)
        {
            btab_total = tabs;
        }

        unsigned int tab_total() const
        {
            return btab_total;
        }

        std::string str() const
        {
            std::stringstream board_str;

            board_str << std::endl << RepeatSymbol< char >('\t', btab_total) << "Board contents:";

            board_str << std::endl << "\t" << RepeatSymbol< char >('\t', btab_total) << "space[ row ][ col ] = ";

            if(space != NULL)
            {
                for(int row = 0; row < ROW_SIZE; ++row)
                {
                    if(space[ row ] != NULL)
                    {
                        for(int col = 0; col < COL_SIZE; ++col)
                        {
                            if(space[ row ][ col ] != NULL)
                            {
                                space[ row ][ col ]->setTabTotal(btab_total + 3);

                                board_str << std::endl << "\t\t" << RepeatSymbol< char >('\t', btab_total) << "space[" << row << "][" << col << "] = " << space[ row ][ col ]->str();
                            }

                            else
                                board_str << std::endl << "\t\t" << RepeatSymbol< char >('\t', btab_total) << "space[" << row << "][" << col << "] = NULL";
                        }
                    }

                    else
                        board_str << std::endl << "\t\t" << RepeatSymbol< char >('\t', btab_total) << "space[" << row << "] = NULL";
                }
            }

            else
                board_str << "NULL";

            return board_str.str();
        }

        Space* operator[](const Loc &pos)
        {
            if(space != NULL && (pos.row >= 0 && pos.row < ROW_SIZE) && (pos.col >= 0 && pos.col < COL_SIZE))
            {
                if(space[ pos.row ] != NULL)
                    return space[ pos.row ][ pos.col ];
            }

            return NULL;
        }

        Board& operator=(const Board &rhs)
        {
            if(this != &rhs)
            {
                clear();

                space = rhs.space;
                btab_total = rhs.btab_total;
            }

            return *this;
        }

    private:
        void initSpaces()
        {
            space = new Space**[ ROW_SIZE ];

            for(int row = 0; row < ROW_SIZE; ++row)
                space[ row ] = new Space*[ COL_SIZE ];
            
            Color color;

            for(int row = 0; row < ROW_SIZE; ++row)
            {
                for(int col = 0; col < COL_SIZE; ++col)
                {
                    color = Color((!(row & 0x1) & (col & 0x1)) | ((row & 0x1) & !(col & 0x1)));

                    space[ row ][ col ] = new Space(color);
                }
            }
        }

        void clearSpaces()
        {
            if(space != NULL)
            {
                for(int row = 0; row < ROW_SIZE; ++row)
                {
                    if(space[ row ] != NULL)
                    {
                        for(int col = 0; col < COL_SIZE; ++col)
                        {
                            if(space[ row ][ col ] != NULL)
                            {
                                delete space[ row ][ col ];
                                space[ row ][ col ] = NULL;
                            }
                        }

                        delete [] space[ row ];
                        space[ row ] = NULL;
                    }
                }

                delete [] space;
                space = NULL;
            }
        }
};

#endif //__BOARD_H__
