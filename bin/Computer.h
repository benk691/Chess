#pragma once
#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "Player.h"

class Computer : public Player
{
    public:
        Computer(const std::string &n = ("Computer"), const Color &c = (BLANK), const PlayerType &t = (COMPUTER), const std::string &cn = ("Computer"), const unsigned int &tabs = (0))
            : Player::Player(n, c, t, cn, tabs)
        {}

        virtual ~Computer()
        {
            clear();
        }

        virtual void move(const std::string &pos)
        {}
};

#endif //__COMPUTER_H__
