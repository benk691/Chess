/** \defgroup group1 Source
 *  This is the source code group.
 *  \{
 */

/*! \file main.cc
 *  \brief The soruce code that runs the chess program.
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

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Game.h"
#include "Debug.h"

#if DEBUG
    DEBUG_FUNCT( main ); /*!< Defines debugging for the main function. */
    DEBUG_FUNCT( playGame ); /*!< Defines debugging for the playGame function. */
    DEBUG_FUNCT( menu ); /*!< Defines debugging for the menu function. */
    DEBUG_FUNCT( startup ); /*!< Defines debugging for the startup function. */
#endif

/*****************************************************************************************************
 *  TODO:
 *      - Write Doxygen comments for the
 *      rest of the code files.
 *
 *****************************************************************************************************/

using namespace std;

//! Plays a game of chess
void playGame();

//! Menu for selecting the player colors
Game* menu();

//! Introduces the chess program
void startup();

int main(int argc, char** argv)
{
    //! Allows for new random numbers to be generated each run
    srand( time(NULL) );

    //! Start playing chess
    playGame();

#if DEBUG
    if( DEBUG_main )
    {
        printf("\n%s: %s: Line #%d: DONE!\n", __FILE__, __FUNCTION__, __LINE__);
    }
#endif

    return 0;
}

//! Plays a game of chess
void playGame()
{
    //! Gives the user an introduction to the program
    startup();

    //! Creates a game based off of the user's choices
    Game* game = menu();

    if(game != NULL)
    {
#if DEBUG
        if( DEBUG_playGame )
        {
            printf("\n%s: %s: Line #%d: game = %s\n", __FILE__, __FUNCTION__, __LINE__, game->str().c_str());
        }
#endif

        string move;
        Color turn = WHITE;
        int move_count = 0;

        while(!game->over())
        {
            if(turn == WHITE)
                move_count++;

            printf("\n\nMove #%d: Please enter %s's move: ", move_count, strColor(turn).c_str());

            cin >> move;

            if(cin.eof() || !cin.good())
                break;

            while(!game->validMove(turn, move))
            {
                printf("\nError: The move, %s, was not a legal chess move.\n\nMove #%d: Please enter in another move for %s: ", move.c_str(), move_count, strColor(turn).c_str());

                cin >> move;
            }

            game->move(turn, move);

            turn = Color(!turn);
        }

        delete game;
        game = NULL;
    }
}

Game* menu()
{
    Game* game = NULL;
    Player* w_player = NULL;
    Player* b_player = NULL;

    string name1;
    string name2;

    char play = '0';
    char choice = '0';
    char color = '0';

    int c = 0;

    while(play != '1' && play != '2')
    {
        printf("\n\nPlease choose one of the game options by entering in the option's corresponding number:");
        printf("\n\t(1.) Human vs. Human");
        printf("\n\t(2.) Human vs. Computer");
        printf("\n\nEnter your choice: ");

        cin >> play;

#if DEBUG
        if( DEBUG_menu )
        {
            printf("\n%s: %s: Line #%d: play = \'%c\'", __FILE__, __FUNCTION__, __LINE__, play);
        }
#endif

        if(play != '1' && play != '2')
            printf("\n\nError: Invalid choice, please only enter in the single digit number of your choice.");
    }

    while(choice != '1' && choice != '2')
    {
        printf("\n\nPlease choose one of the game options by entering in the option's corresponding number:");
        printf("\n\t(1.) Choose the color of each player");
        printf("\n\t(2.) Randomly assign colors to both players");
        printf("\n\nEnter your choice: ");

        cin >> choice;

#if DEBUG
        if( DEBUG_menu )
        {
            printf("\n%s: %s: Line #%d: choice = \'%c\'", __FILE__, __FUNCTION__, __LINE__, choice);
        }
#endif

        if(choice != '1' && choice != '2')
            printf("\n\nError: Invalid choice, please only enter in the single digit number of your choice.");
    }

    switch(play)
    {
        case '1'    :   printf("\n\nPlease enter the first name of a player: ");
                        cin >> name1;

                        printf("\nPlease enter the first name of the other player: ");
                        cin >> name2;

#if DEBUG
                        if( DEBUG_menu )
                        {
                            printf("\n%s: %s: Line #%d: name1 = \"%s\"", __FILE__, __FUNCTION__, __LINE__, name1.c_str());
                            printf("\n%s: %s: Line #%d: name2 = \"%s\"", __FILE__, __FUNCTION__, __LINE__, name2.c_str());
                        }
#endif

                        switch(choice)
                        {
                            case '1'    :   while(color != '1' && color != '2')
                                            {
                                                printf("\n\nEnter the color %s is going to play:", name1.c_str());
                                                printf("\n\t(1.) White");
                                                printf("\n\t(2.) Black");
                                                printf("\n\nEnter your choice: ");

                                                cin >> color;

#if DEBUG
                                                if( DEBUG_menu )
                                                {
                                                    printf("\n%s: %s: Line #%d: color = \'%c\'", __FILE__, __FUNCTION__, __LINE__, color);
                                                }
#endif

                                                if(choice != '1' && choice != '2')
                                                    printf("\n\nError: Invalid choice, please only enter in the single digit number of your choice.");
                                            }

                                            switch(color)
                                            {
                                                case '1'    :   w_player = new Human(name1, WHITE);
                                                                b_player = new Human(name2, BLACK);

                                                                break;

                                                case '2'    :   w_player = new Human(name2, WHITE);
                                                                b_player = new Human(name1, BLACK);

                                                                break;

                                                default     :   break;
                                            }

                                            break;

                            case '2'    :   c = rand() % 2;

                                            switch(c)
                                            {
                                                case 0  :   w_player = new Human(name2, WHITE);
                                                            b_player = new Human(name1, BLACK);

                                                            break;

                                                case 1  :   w_player = new Human(name1, WHITE);
                                                            b_player = new Human(name2, BLACK);
                                                            break;

                                                default :   break;
                                            }

                                            break;

                            default     :   break;
                        }

                        break;

        case '2'    :   printf("\n\nPlease enter the first name for the computer: ");
                        cin >> name1;

                        printf("\nPlease enter your first name: ");
                        cin >> name2;

#if DEBUG
                        if( DEBUG_menu )
                        {
                            printf("\n%s: %s: Line #%d: name1 = \"%s\"", __FILE__, __FUNCTION__, __LINE__, name1.c_str());
                            printf("\n%s: %s: Line #%d: name2 = \"%s\"", __FILE__, __FUNCTION__, __LINE__, name2.c_str());
                        }
#endif

                        switch(choice)
                        {
                            case '1'    :   while(color != '1' && color != '2')
                                            {
                                                printf("\n\nEnter the color %s is going to play:", name1.c_str());
                                                printf("\n\t(1.) White");
                                                printf("\n\t(2.) Black");
                                                printf("\n\nEnter your choice: ");

                                                cin >> color;

#if DEBUG
                                                if( DEBUG_menu )
                                                {
                                                    printf("\n%s: %s: Line #%d: color = \'%c\'", __FILE__, __FUNCTION__, __LINE__, color);
                                                }
#endif

                                                if(choice != '1' && choice != '2')
                                                    printf("\n\nError: Invalid choice, please only enter in the single digit number of your choice.");
                                            }

                                            switch(color)
                                            {
                                                case '1'    :   w_player = new Human(name2, WHITE);
                                                                b_player = new Computer(name1, BLACK);

                                                                break;

                                                case '2'    :   w_player = new Computer(name1, WHITE);
                                                                b_player = new Human(name2, BLACK);

                                                                break;

                                                default     :   break;
                                            }

                                            break;

                            case '2'    :   c = rand() % 2;

                                            switch(c)
                                            {
                                                case 0  :   w_player = new Human(name2, WHITE);
                                                            b_player = new Computer(name1, BLACK);

                                                            break;

                                                case 1  :   w_player = new Computer(name1, WHITE);
                                                            b_player = new Human(name2, BLACK);
                                                            break;

                                                default :   break;
                                            }

                                            break;

                            default     :   break;
                        }

                        break;

        default     :   break;
    }

    game = new Game(w_player, b_player);

    return game;
}

void startup()
{
    string title = " Chess ";
    unsigned int total = 30;

    printf("\n%s%s%s", RepeatSymbol< char >('-', total).c_str(), title.c_str(), RepeatSymbol< char >('-', total).c_str());

    printf("\n\tWelcome to chess, when you play a move it must be put\n\tinto algebraic chess notation.\n\t(ie: e4 <denotes white pawn move to e4>)\n\n\tGood Luck!");

    printf("\n%s", RepeatSymbol< char >('-', (2 * total + title.size())).c_str());
}

/** \} */
