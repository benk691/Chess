#pragma once
#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <sstream>
#include <vector>
#include <cctype>
#include "Loc.h"

#define DEBUG 1

std::vector< std::vector< std::vector< Loc > > > initStartLoc();

// Number of players that can play game
const int PLAYER_NUMB = 2;

// Number of rows on board
const int ROW_SIZE = 8;

// Number of columns on board
const int COL_SIZE = 8;

// Number of pieces that a player has
const int PIECE_NUMB = 16;

// The number of unique piece types
const int PIECE_TYPE_SIZE = 6;

// [] : piece set for a certain color, index by the Color enum
// [][] : set of start locations for a certain piece type, index by the PieceType enum
// [][][] : The location of a piece, index by how many pieces of a certain type you have already placed
const std::vector< std::vector< std::vector< Loc > > > START_POS = initStartLoc();

std::vector< std::vector< std::vector< Loc > > > initStartLoc()
{
    std::vector< std::vector< std::vector< Loc > > > start_pos;

    // Black Pieces
    std::vector< std::vector< Loc > > bpt;

    // Pawns
    std::vector< Loc > b_pawn_pos;

    b_pawn_pos.push_back(Loc(6, 0));
    b_pawn_pos.push_back(Loc(6, 1));
    b_pawn_pos.push_back(Loc(6, 2));
    b_pawn_pos.push_back(Loc(6, 3));
    b_pawn_pos.push_back(Loc(6, 4));
    b_pawn_pos.push_back(Loc(6, 5));
    b_pawn_pos.push_back(Loc(6, 6));
    b_pawn_pos.push_back(Loc(6, 7));

    bpt.push_back(b_pawn_pos);

    // Knights
    std::vector< Loc > b_knight_pos;

    b_knight_pos.push_back(Loc(7, 1));
    b_knight_pos.push_back(Loc(7, 6));

    bpt.push_back(b_knight_pos);

    // Bishops
    std::vector< Loc > b_bishop_pos;

    b_bishop_pos.push_back(Loc(7, 2));
    b_bishop_pos.push_back(Loc(7, 5));

    bpt.push_back(b_bishop_pos);

    // Rooks
    std::vector< Loc > b_rook_pos;

    b_rook_pos.push_back(Loc(7, 0));
    b_rook_pos.push_back(Loc(7, 7));

    bpt.push_back(b_rook_pos);

    // Queens
    std::vector< Loc > b_queen_pos;

    b_queen_pos.push_back(Loc(7, 3));

    bpt.push_back(b_queen_pos);

    // Kings
    std::vector< Loc > b_king_pos;

    b_king_pos.push_back(Loc(7, 4));

    bpt.push_back(b_king_pos);

    start_pos.push_back(bpt);

    // White Pieces
    std::vector< std::vector< Loc > > wpt;

    // Pawns
    std::vector< Loc > w_pawn_pos;

    w_pawn_pos.push_back(Loc(1, 0));
    w_pawn_pos.push_back(Loc(1, 1));
    w_pawn_pos.push_back(Loc(1, 2));
    w_pawn_pos.push_back(Loc(1, 3));
    w_pawn_pos.push_back(Loc(1, 4));
    w_pawn_pos.push_back(Loc(1, 5));
    w_pawn_pos.push_back(Loc(1, 6));
    w_pawn_pos.push_back(Loc(1, 7));

    wpt.push_back(w_pawn_pos);

    // Knights
    std::vector< Loc > w_knight_pos;

    w_knight_pos.push_back(Loc(0, 1));
    w_knight_pos.push_back(Loc(0, 6));

    wpt.push_back(w_knight_pos);

    // Bishops
    std::vector< Loc > w_bishop_pos;

    w_bishop_pos.push_back(Loc(0, 2));
    w_bishop_pos.push_back(Loc(0, 5));

    wpt.push_back(w_bishop_pos);

    // Rooks
    std::vector< Loc > w_rook_pos;

    w_rook_pos.push_back(Loc(0, 0));
    w_rook_pos.push_back(Loc(0, 7));

    wpt.push_back(w_rook_pos);

    // Queens
    std::vector< Loc > w_queen_pos;

    w_queen_pos.push_back(Loc(0, 3));

    wpt.push_back(w_queen_pos);

    // Kings
    std::vector< Loc > w_king_pos;

    w_king_pos.push_back(Loc(0, 4));

    wpt.push_back(w_king_pos);

    start_pos.push_back(wpt);

    return start_pos;
}

void printStartPos()
{
    printf("\n\n%s: Line #%d: START_POS contents:", __FILE__, __LINE__);

    for(unsigned int color = 0; color < START_POS.size(); ++color)
    {
        for(unsigned int pt = 0; pt < START_POS[ color ].size(); ++pt)
        {
            for(unsigned int i = 0; i < START_POS[ color ][ pt ].size(); ++i)
                printf("\n\t%s: Line #%d: START_POS[ %d ][ %d ][ %d ] = Loc(row = %d, col = %d)", __FILE__, __LINE__, color, pt, i, START_POS[ color ][ pt ][ i ].row, START_POS[ color ][ pt ][ i ].col);
        }
    }

    printf("\n");
}

template< class T >
std::string RepeatSymbol(T symbol, const unsigned int &total)
{
    std::stringstream display;

    for(unsigned int count = 0; count < total; ++count)
        display << symbol;

    return display.str();
}

template< class T >
T lower(T content)
{
    return content;
}

template<>
char lower< char >(char content)
{
    return char(tolower(content));
}

template<>
std::string lower< std::string >(std::string content)
{
    std::string lc_content;

    for(unsigned int i = 0; i < content.size(); ++i)
        lc_content += lower( content[i] );

    return lc_content;
}

bool isDigit(const char &symbol)
{
    return (symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4' || symbol == '5' || symbol == '6' || symbol == '7' || symbol == '8' || symbol == '9');
}

#endif //__GENERAL_H__
