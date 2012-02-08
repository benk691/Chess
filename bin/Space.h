#pragma once
#ifndef __SPACE_H__
#define __SPACE_H__

#include "General.h"
#include "Color.h"

class Space
{
    public:
        const Color scolor;
        bool soccupied;
        /*! Size = 3
         * Indicies:
         *      0 - color of piece
         *      1 - piece type
         *      2 - piece index
         *
         * -1 means not a valid value
         */
        int spiece[ 3 ];
        //! Indicates which player's are targeting the space, indexed by the Color enum
        bool spresence[ PLAYER_NUMB ];
        unsigned int stab_total;
    
    public:
        Space(const Color &c = (BLANK), const unsigned int &tabs = (0))
            : scolor(c), soccupied(false), stab_total(tabs)
        {
            for(int i = 0; i < 3; ++i)
                spiece[ i ] = -1;

            spresence[ WHITE ] = false;
            spresence[ BLACK ] = false;
        }

        Space(const Space &copy)
            : scolor(copy.scolor)
        {
            *this = copy;
        }

        ~Space()
        {}

        void occupy()
        {
            soccupied = true;
        }

        void unoccupy()
        {
            soccupied = false;
        }

        void setPieceInfo(const int &color, const int &pt, const int &index)
        {
            spiece[ 0 ] = color;
            spiece[ 1 ] = pt;
            spiece[ 2 ] = index;
        }

        void newPresence(const Color &color)
        {
            spresence[ color ] = true;
        }

        void delPresence(const Color &color)
        {
            spresence[ color ] = false;
        }
        
        void setTabTotal(const unsigned int &tabs)
        {
            stab_total = tabs;
        }

        bool occupied() const
        {
            return soccupied;
        }

        bool presence(const Color &color) const
        {
            return spresence[ color ];
        }

        const int* piece() const
        {
            return spiece;
        }

        Color color() const
        {
            return scolor;
        }

        unsigned int tab_total() const
        {
            return stab_total;
        }

        std::string str() const
        {
            std::stringstream space_str;

            space_str << std::endl << RepeatSymbol< char >('\t', stab_total) << "Space contents:";

            space_str << std::endl << "\t" << RepeatSymbol< char >('\t', stab_total) << "color = " << strColor(scolor);
            space_str << std::endl << "\t" << RepeatSymbol< char >('\t', stab_total) << "occupied = " << soccupied;
            space_str << std::endl << "\t" << RepeatSymbol< char >('\t', stab_total) << "presence[ white ] = " << spresence[ WHITE ];
            space_str << std::endl << "\t" << RepeatSymbol< char >('\t', stab_total) << "presence[ black ] = " << spresence[ BLACK ];

            return space_str.str();
        }

        Space& operator=(const Space &rhs)
        {
            if(this != &rhs)
            {
                soccupied = rhs.soccupied;
                stab_total = rhs.stab_total;

                for(int i = 0; i < 3; ++i)
                    spiece[ i ] = rhs.spiece[ i ];

                for(int i = 0; i < PLAYER_NUMB; ++i)
                    spresence[ i ] = rhs.spresence[ i ];
            }

            return *this;
        }
};

#endif //__SPACE_H__
