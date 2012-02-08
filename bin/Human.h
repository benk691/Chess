#pragma once
#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "Player.h"

class Human : public Player
{
    public:
        Human(const std::string &n = ("Human"), const Color &c = (BLANK), const PlayerType &t = (HUMAN), const std::string &cn = ("Human"), const unsigned int &tabs = (0))
            : Player::Player(n, c, t, cn, tabs)
        {}

        virtual ~Human()
        {
            clear();
        }

        virtual void move(const std::string &pos)
        {}
};

#endif //__HUMAN_H__
