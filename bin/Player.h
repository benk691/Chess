#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "General.h"
#include "Color.h"
#include "PlayerType.h"
#include "PieceDefs.h"

class Player
{
    public:
        /*! For i, j >= 0
         * Piece[i] : pointer, pointer that represents the piece type which is indexed by the PieceType enum
         * Piece[i][j] : pointer that represents the pointer to the piece
         * A pointer is needed to the piece so that const values can be constructed correctly.
         */
        Piece*** piece;
        const PlayerType ptype;
        const Color pcolor;
        std::string name;
        std::string class_name;

    public:
        unsigned int tab_total;

    public:
        Player(const std::string &n = ("Player"), const Color &c = (BLANK), const PlayerType &t = (NONE), const std::string &cn = ("Player"), const unsigned int &tabs = (0))
            : piece(NULL), ptype(t), pcolor(c), name(n), class_name(cn), tab_total(tabs)
        {}

        Player(const Player &copy)
            : piece(NULL), ptype(copy.type()), pcolor(copy.color()), name("Player"), class_name("Player"), tab_total(0)
        {
            *this = copy;
        }

        virtual ~Player()
        {
            clear();
        }
        
        virtual void move(const std::string &pos) = 0;

        virtual void setPieces(Piece*** p)
        {
            clearPieces();

            piece = p;
        }

        virtual void clear()
        {
            clearPieces();
        }

        virtual Piece*** getPieces() const
        {
            return piece;
        }

        virtual PlayerType type() const
        {
            return ptype;
        }

        virtual Color color() const
        {
            return pcolor;
        }

        virtual std::string str() const
        {
            std::stringstream player_str;

            player_str << std::endl << RepeatSymbol< char >('\t', tab_total) << class_name << " contents:";
            player_str << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "name = " << name;
            player_str << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "type = " << strPlayerType(ptype);
            player_str << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "color = " << strColor(pcolor);
            player_str << displayPieces();

            return player_str.str();
        }

        virtual Player& operator=(const Player &rhs)
        {
            if(this != &rhs)
            {
                clear();

                piece = rhs.piece;
                name = rhs.name;
                class_name = rhs.class_name;
                tab_total = rhs.tab_total;
            }

            return *this;
        }

    private:
        virtual void clearPieces()
        {
            if(piece != NULL)
            {
                for(int pt = 0; pt < PIECE_TYPE_SIZE; ++pt)
                {
                    if(piece[ pt ] != NULL)
                    {
                        for(int index = 0; index < PIECE_TYPE_NUMB[ pt ]; ++index)
                        {
                            if(piece[ pt ][ index ] != NULL)
                            {
                                delete piece[ pt ][ index ];
                                piece[ pt ][ index ] = NULL;
                            }
                        }

                        delete [] piece[ pt ];
                        piece[ pt ] = NULL;
                    }
                }

                delete [] piece;
                piece = NULL;
            }
        }

        std::string displayPieces() const
        {
            std::stringstream piece_str;

            piece_str << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "piece = ";

            if(piece != NULL)
            {
                for(int pt = 0; pt < PIECE_TYPE_SIZE; ++pt)
                {
                    if(piece[ pt ] != NULL)
                    {
                        for(int index = 0; index < PIECE_TYPE_NUMB[ pt ]; ++index)
                        {
                            if(piece[ pt ][ index ] != NULL)
                            {
                                piece[ pt ][ index ]->ptab_total = tab_total + 3;
                                piece_str << std::endl << "\t\t" << RepeatSymbol< char >('\t', tab_total) << "piece[" << pt << "][" << index << "] = " << piece[ pt ][ index ]->str();
                            }

                            else
                                piece_str << std::endl << "\t\t" << RepeatSymbol< char >('\t', tab_total) << "piece[" << pt << "][" << index << "] = NULL";
                        }
                    }

                    else
                        piece_str << std::endl << "\t\t" << RepeatSymbol< char >('\t', tab_total) << "piece[" << pt << "] = NULL";
                }
            }

            else
                piece_str << "NULL";

            return piece_str.str();
        }
};

#endif //__PLAYER_H__
