#pragma once
#ifndef __PIECE_TYPE_H__
#define __PIECE_TYPE_H__

#include <string>
#include <map>

enum PieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    UNKNOWN
};

// Stores how many pieces of a certain piece type a player starts with, elements in the array are indexed by the int value of the PieceType enum
const int PIECE_TYPE_NUMB[] = 
    {
        8,  // Number of pawns
        2,  // Number of knights
        2,  // Number of bishops
        2,  // Number of rooks
        1,  // Number of queens
        1   // Number of kings
    };

const char PIECE_LABEL[] = 
    {
        '\0',  // Pawn label
        'N',   // Knight label
        'B',   // Bishop label
        'R',   // Rook label
        'Q',   // Queen label
        'K'    // King label
    };

PieceType PieceLabel(const char &label)
{
    PieceType pt;

    switch(label)
    {
        case 'N'    :   pt = KNIGHT;
                        break;

        case 'B'    :   pt = BISHOP;
                        break;

        case 'R'    :   pt = ROOK;
                        break;

        case 'Q'    :   pt = QUEEN;
                        break;

        case 'K'    :   pt = KING;
                        break;

        default     :   break;
    }

    return pt;
}

std::string strPieceType(const PieceType &piece_type)
{
    std::string piece_str = "";

    switch(piece_type)
    {
        case PAWN     :     piece_str = "pawn";
                            break;
       
        case KNIGHT   :     piece_str = "knight";
                            break;

        case BISHOP   :     piece_str = "bishop";
                            break;

        case ROOK     :     piece_str = "rook";
                            break;

        case QUEEN    :     piece_str = "queen";
                            break;

        case KING     :     piece_str = "king";
                            break;

        default       :     piece_str = "none";
                            break;
    }

    return piece_str;
}

#endif //__PIECE_TYPE_H__
