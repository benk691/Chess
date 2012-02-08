/** \defgroup group3 Game Play
 *  This is the game play group.
 *  \{
 */

/*! \file Game.h
 *  \brief The code that makes up the chess game.
 *  \author Benjamin Kellogg
 *  \details
 *  E-Mail Address:     benk691@gmail.com
 *
 *  Comments:           This code uses Doxygen styled comments.
 *
 *  Copyright ©2011-2012 Benjamin Kellogg all rights are reserved.
 *  \version 1.0
 *  \date October 25, 2011
 */

#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <boost/tokenizer.hpp>
#include "Human.h"
#include "Computer.h"
#include "Board.h"
#include "Move.h"
#include "Debug.h"

#if DEBUG
    DEBUG_CLASS( Game ); /*!< Defines debugging for the Game class. */
    DEBUG_FUNCT( Game_construct ); /*!< Defines debugging for the Game constructor. */
    DEBUG_FUNCT( Game_destruct ); /*!< Defines debugging for the Game destructor. */
    DEBUG_FUNCT( Game_validMove ); /*!< Defines debugging for the validMove function. */
    DEBUG_FUNCT( Game_move ); /*!< Defines debugging for the move function. */
    DEBUG_FUNCT( Game_clear ); /*!< Defines debugging for the clear function. */
    DEBUG_FUNCT( Game_over ); /*!< Defines debugging for the over function. */
    DEBUG_FUNCT( Game_str ); /*!< Defines debugging for the str function. */
    DEBUG_FUNCT( Game_eq ); /*!< Defines debugging for the operator= function. */
    DEBUG_FUNCT( Game_simulateMove ); /*!< Defines debugging for the simulateMove function. */
    DEBUG_FUNCT( Game_tokenizeMove ); /*!< Defines debugging for the tokenizeMove function. */
    DEBUG_FUNCT( Game_initPieces ); /*!< Defines debugging for the initPieces function. */
    DEBUG_FUNCT( Game_PieceCount ); /*!< Defines debugging for the PieceCount function. */
    DEBUG_FUNCT( Game_clearPieceCount ); /*!< Defines debugging for the clearPieceCount function. */
    DEBUG_FUNCT( Game_inLabels ); /*!< Defines debugging for the inLabels function. */
#endif

/*****************************************************************************************************
 *  TODO:
 *      - When generating the move list
 *        from the piece, you will need
 *        to query the board to know if
 *        another piece is blocking the
 *        moves.
 *     - Update the move generating lists
 *       to have sets of Move objects instead
 *       of sets of Loc objects. The reason
 *       this change is being done is because
 *       the game needs to know which way the
 *       piece is generating the move so that
 *       it can determine whether the piece
 *       has a presence on a space or not,
 *       especially when the move generation
 *       collides with a piece of the same color
 *       or the opponent's piece.
 *
 *****************************************************************************************************/

class Game
{
    private:
        Player* white_player;
        Player* black_player;
        Board* board;
        Move* cur_move;
        const int start;
        const int end;
        const Loc inv_loc;
        bool gover;
        unsigned int tab_total;

    public:
        Game(Player* wp = (NULL), Player* bp = (NULL), const unsigned int &tabs = (0))
            : white_player(wp), black_player(bp), board(new Board), cur_move(new Move), start(0), end(1), gover(false), tab_total(tabs)
        {
#if DEBUG
            if(DEBUG_Game_construct)
            {
                printStartPos();
            }
#endif

            white_player->setPieces(initPieces(WHITE));

            black_player->setPieces(initPieces(BLACK));

            updatePresences(WHITE, white_player->piece);
            updatePresences(BLACK, black_player->piece);
        }

        Game(const Game &copy)
            : white_player(NULL), black_player(NULL), board(NULL), cur_move(NULL), start(0), end(1), gover(false), tab_total(0)
        {
            *this = copy;
        }

        ~Game()
        {
            clear();
        }

        bool validMove(const Color &turn, const std::string &mov)
        {
            if(mov.size() > 0)
            {
                if(lower(mov) != "resign" && lower(mov) != "0.5-0.5")
                {
                    std::string move_str = (mov.size() > 0 && inLabels(toupper(mov[0]))) ? (char(toupper(mov[0])) + lower(mov.substr(1))) : lower(mov);

#if DEBUG
                    if(DEBUG_Game_validMove)
                    {
                        printf("\n%s: %s: Line #%d: mov = \"%s\"\n", __FILE__, __FUNCTION__, __LINE__, mov.c_str());
                        printf("\n%s: %s: Line #%d: move_str = \"%s\"\n", __FILE__, __FUNCTION__, __LINE__, move_str.c_str());
                    }
#endif

                    Loc* pos = tokenizeMove(move_str);

                    PieceType pt;

                    char label = move_str[0];

                    if(inLabels(label))
                        pt = PieceLabel(label);

                    else
                        pt = PAWN;

                    cur_move->piece_type = pt;
                    cur_move->move_str = move_str;

#if DEBUG
                    if(DEBUG_Game_validMove)
                    {
                        printf("\n%s: %s: Line #%d: pt = %s", __FILE__, __FUNCTION__, __LINE__, strPieceType(pt).c_str());
                    }
#endif

                    Piece*** white_piece = white_player->getPieces();

                    Piece*** black_piece = black_player->getPieces();

                    bool valid_move = turn == WHITE ? simulateMove(WHITE, white_piece, mov, pt, pos) : simulateMove(BLACK, black_piece, mov, pt, pos);

                    cur_move->valid = valid_move;

                    if(valid_move)
                    {
                        cur_move->start_loc = pos[ start ];
                        cur_move->end_loc = pos[ end ];
                    }

                    else
                    {
                        cur_move->start_loc = inv_loc;
                        cur_move->end_loc = inv_loc;
                    }

                    if(pos != NULL)
                    {
                        delete [] pos;
                        pos = NULL;
                    }

                    return valid_move;
                }

                else
                    return true;
            }

            return false;
        }

        void move(const Color &turn, const std::string &pos)
        {
#if DEBUG
            if(DEBUG_Game_move)
            {
                if(cur_move != NULL)
                    printf("\n\n%s: %s: Line #%d: cur_move = \"%s\"", __FILE__, __FUNCTION__, __LINE__, cur_move->str().c_str());

                else
                    printf("\n\n%s: %s: Line #%d: cur_move = NULL", __FILE__, __FUNCTION__, __LINE__);
            }
#endif
        }

        void clear()
        {
            if(white_player != NULL)
            {
                delete white_player;
                white_player = NULL;
            }

            if(black_player != NULL)
            {
                delete black_player;
                black_player = NULL;
            }

            if(board != NULL)
            {
                delete board;
                board = NULL;
            }

            if(cur_move != NULL)
            {
                delete cur_move;
                cur_move = NULL;
            }
        }

        bool over() const
        {
            return gover;
        }

        std::string str() const
        {
            std::stringstream game_str;

            game_str << std::endl << RepeatSymbol< char >('\t', tab_total) << "Game contents:";

            game_str << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "white_player = ";

            if(white_player != NULL)
            {
                white_player->tab_total = tab_total + 2;
                game_str << white_player->str();
            }

            else
                game_str << "NULL";

            game_str << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "black_player = ";

            if(black_player != NULL)
            {
                black_player->tab_total = tab_total + 2;
                game_str << black_player->str();
            }

            else
                game_str << "NULL";

            game_str << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "board = ";

            if(board != NULL)
            {
                board->setTabTotal(tab_total + 2);
                game_str << board->str();
            }

            else
                game_str << "NULL";


            game_str << std::endl << "\t" << RepeatSymbol< char >('\t', tab_total) << "cur_move = ";

           if(cur_move != NULL)
           {
               cur_move->tab_total = tab_total + 2;
               game_str << cur_move->str();
           }

           else
               game_str << "NULL";

            return game_str.str();
        }

        Game& operator=(const Game &rhs)
        {
            if(this != &rhs)
            {
                clear();

                white_player = rhs.white_player;
                black_player = rhs.black_player;
                board = rhs.board;
                cur_move = rhs.cur_move;
                gover = rhs.gover;
                tab_total = rhs.tab_total;
            }

            return *this;
        }

    private:
        bool simulateMove(const Color &color, Piece*** piece, const std::string &mov, const PieceType &pt, Loc* pos)
        {
#if DEBUG
            if(DEBUG_Game_simulateMove)
            {
                printf("\n\n%s: %s: Line #%d: pos[ 0 ] = Loc(row = %d, col = %d)", __FILE__, __FUNCTION__, __LINE__, pos[ 0 ].row, pos[ 0 ].col);
                printf("\n%s: %s: Line #%d: pos[ 1 ] = Loc(row = %d, col = %d)", __FILE__, __FUNCTION__, __LINE__, pos[ 1 ].row, pos[ 1 ].col);
            }
#endif

            if(piece != NULL && pos != NULL)
            {
                if(piece[ pt ] != NULL)
                {
                    /*! Keeps track of the number of pieces, of a certain type,
                     that have the move specified by the user.
                     */
                    int pieces_w_move = 0;

                    for(int i = 0; i < PIECE_TYPE_NUMB[ pt ]; ++i)
                    {
                        std::set< Loc > mv_list = piece[ pt ][ i ]->MoveList();

#if DEBUG
                        if(DEBUG_Game_simulateMove)
                        {
                            printf("\n\n%s: %s: Line #%d: mv_list contents:", __FILE__, __FUNCTION__, __LINE__);

                            for(std::set< Loc >::iterator mv = mv_list.begin(); mv != mv_list.end(); ++mv)
                                printf("\n\t%s: %s: Line #%d: mv = Loc(row = %d, col = %d)", __FILE__, __FUNCTION__, __LINE__, mv->row, mv->col);
                        }
#endif

                        if( piece[ pt ][ i ] != NULL && 
                            ( ( ( pos[ start ].row != -1 && pos[ start ].col != -1 && pos[ start ] == piece[ pt ][ i ]->loc ) || 
                                ( pos[ start ].row != -1 && pos[ start ].row == piece[ pt ][ i ]->loc.row ) || 
                                ( pos[ start ].col != -1 && pos[ start ].col == piece[ pt ][ i ]->loc.col ) || 
                                ( pos[ start ].row == -1 && pos[ start ].col == -1 ) ) && 
                              piece[ pt ][ i ]->MoveList().count(pos[ end ]) > 0 ) )
                        {
                            cur_move->start_loc = piece[ pt ][ i ]->loc;
                            pieces_w_move++;
                        }
                    }

                    cur_move->end_loc = pos[ end ];

                    if(pieces_w_move > 1)
                    {
                        printf("\n\nError: The move entered was ambiguous, there is more than one %s that can move to the space specified, please specify the row or column or both, in the move.", strPieceType(pt).c_str());

                        return false;
                    }

                    else if(pieces_w_move <= 0)
                    {
                        printf("\n\nError: There were no %ss that can move to the space specified, please specify a valid move.", strPieceType(pt).c_str());

                        return false;
                    }
                }

                return true;
            }

            return false;
        }

        Loc* tokenizeMove(std::string mov)
        {
            Loc* pos = new Loc[2];

            boost::char_separator< char > special_syms("x+#!?");
            boost::tokenizer< boost::char_separator< char > > toks(mov, special_syms);

            std::string mv;

#if DEBUG
            if(DEBUG_Game_tokenizeMove)
            {
                printf("\n%s: %s: Line #%d: tokens:", __FILE__, __FUNCTION__, __LINE__);
            }
#endif

            for(boost::tokenizer< boost::char_separator< char > >::iterator tok = toks.begin(); tok != toks.end(); ++tok)
            {
#if DEBUG
                if(DEBUG_Game_tokenizeMove)
                {
                    printf("\n\t%s: %s: Line #%d: tok = \"%s\"", __FILE__, __FUNCTION__, __LINE__, tok->c_str());
                }
#endif
                mv += tok->c_str();
            }

#if DEBUG
            if(DEBUG_Game_tokenizeMove)
            {
                printf("\n\n%s: %s: Line #%d: mv = \"%s\"", __FILE__, __FUNCTION__, __LINE__, mv.c_str());
            }
#endif

            Loc start_loc;
            Loc end_loc;

            int col_count = 0;
            int row_count = 0;

#if DEBUG
            unsigned int i = inLabels(mv[0]) ? 1 : 0;
            if(DEBUG_Game_tokenizeMove)
            {
                printf("\n%s: %s: Line #%d: i = %d", __FILE__, __FUNCTION__, __LINE__, i);
            }

            for(; i < mv.size(); ++i)
#else
            for(unsigned int i = inLabels(mv[0]) ? 1 : 0; i < mv.size(); ++i)
#endif
            {
                if(isDigit(mv[ i ]))
                {
                    if(row_count == 0)
                        end_loc.row = int(mv[ i ]) % int('1');

                    else
                    {
                        start_loc.row = end_loc.row;
                        end_loc.row = int(mv[ i ]) % int('1');
                    }

                    row_count++;
                }

                else
                {
                    if(col_count == 0)
                        end_loc.col = int(mv[ i ]) % int('a');

                    else
                    {
                        start_loc.col = end_loc.col;
                        end_loc.col = int(mv[ i ]) % int('a');
                    }

                    col_count++;
                }
            }

            pos[0] = start_loc;
            pos[1] = end_loc;

#if DEBUG
            if(DEBUG_Game_tokenizeMove)
            {
                printf("\n%s: %s: Line #%d: mv = \"%s\"", __FILE__, __FUNCTION__, __LINE__,  mv.c_str());
                printf("\n%s: %s: Line #%d: start_loc = Loc(row = %d, col = %d)", __FILE__, __FUNCTION__, __LINE__,  start_loc.row, start_loc.col);
                printf("\n%s: %s: Line #%d: end_loc = Loc(row = %d, col = %d)", __FILE__, __FUNCTION__, __LINE__,  end_loc.row, end_loc.col);
            }
#endif

            return pos;
        }

        Piece*** initPieces(const Color &pcolor)
        {
            //! PIECE_TYPE_NUMB, PIECE_TYPE_NUMB, START_POS in General.h
            Piece*** piece;
            int* count = PieceCount();
            piece = new Piece**[ PIECE_TYPE_SIZE ];

            //! pt: piece type, corresponds to the int value of an enum name in PieceType
            for(int pt = 0; pt < PIECE_TYPE_SIZE; ++pt)
            {
                piece[ pt ] = new Piece*[ PIECE_TYPE_NUMB[ pt ] ];

                for(int index = 0; index < PIECE_TYPE_NUMB[ pt ]; ++index)
                {
                    (*board)[ START_POS[ pcolor ][ pt ][ count[ pt ] ] ]->setPieceInfo(pcolor, pt, count[ pt ]);

                    switch(PieceType(pt))
                    {
                        case PAWN   :   piece[ pt ][ index ] = new Pawn(pcolor, START_POS[ pcolor ][ pt ][ count[ pt ] ]);
                                        count[ pt ]++;
                                        break;

                        case KNIGHT :   piece[ pt ][ index ] = new Knight(pcolor, START_POS[ pcolor ][ pt ][ count[ pt ] ]);
                                        count[ pt ]++;
                                        break;

                        case BISHOP :   piece[ pt ][ index ] = new Bishop(pcolor, START_POS[ pcolor ][ pt ][ count[ pt ] ]);
                                        count[ pt ]++;
                                        break;

                        case ROOK   :   piece[ pt ][ index ] = new Rook(pcolor, START_POS[ pcolor ][ pt ][ count[ pt ] ]);
                                        count[ pt ]++;
                                        break;

                        case QUEEN  :   piece[ pt ][ index ] = new Queen(pcolor, START_POS[ pcolor ][ pt ][ count[ pt ] ]);
                                        count[ pt ]++;
                                        break;

                        case KING   :   piece[ pt ][ index ] = new King(pcolor, START_POS[ pcolor ][ pt ][ count[ pt ] ]);
                                        count[ pt ]++;
                                        break;

                        default     :   piece[ pt ][ index ] = NULL;
                                        break;
                    }

#if 0
                    if(piece[ pt ][ index ] != NULL)
                    {
                        (*board)[ piece[ pt ][ index ]->loc ]->newPresence(pcolor);

                        std::set< Loc > mv_list = piece[ pt ][ index ]->MoveList();

                        for(std::set< Loc >::iterator mv = mv_list.begin(); mv != mv_list.end(); ++mv)
                            (*board)[ (*mv) ]->newPresence(pcolor);
                    }
#endif
                }
            }

            clearPieceCount(count);

            return piece;
        }

        //! pcolor: the color of the opposing person
        //! piece: the other set of pieces
        void updatePresences(const Color &pcolor, Piece*** &piece)
        {
            //! PIECE_TYPE_NUMB, PIECE_TYPE_NUMB, START_POS in General.h

            //! pt: piece type, corresponds to the int value of an enum name in PieceType
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
                                (*board)[ piece[ pt ][ index ]->loc ]->newPresence(pcolor);

                                std::set< Move > mv_list = piece[ pt ][ index ]->MoveList();

                                for(std::set< Move >::iterator mv = mv_list.begin(); mv != mv_list.end(); ++mv)
                                {
                                    if(!(*board)[ (*mv) ]->occupied())
                                        (*board)[ (*mv) ]->newPresence(pcolor);

                                    else 
                                    {
                                        if((*board)[ (*mv) ]->piece()[ 0 ] != pcolor)
                                            (*board)[ (*mv) ]->newPresence(pcolor);

                                        if(pt != KNIGHT)
                                            break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        int* PieceCount()
        {
            int* count = new int[ PIECE_TYPE_SIZE ];

            //! pt: piece type, corresponds to the int value of an enum name in PieceType
            for(int pt = 0; pt < PIECE_TYPE_SIZE; ++pt)
                count[ pt ] = 0;

            return count;
        }

        void clearPieceCount(int* count)
        {
            if(count != NULL)
            {
                delete [] count;
                count = NULL;
            }
        }

        bool inLabels(const char &sym) const
        {
            bool found = false;

            for(int i = 0; !found && i < PIECE_TYPE_SIZE; ++i)
                found = sym == PIECE_LABEL[ i ];

            return found;
        }
};

#endif //__GAME_H__

/** \} */
