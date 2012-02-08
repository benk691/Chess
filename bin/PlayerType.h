#pragma once
#ifndef __PLAYER_TYPE_H__
#define __PLAYER_TYPE_H__

#include <string>

enum PlayerType
{
    HUMAN,
    COMPUTER,
    NONE
};

std::string strPlayerType(const PlayerType &player_type)
{
    std::string player_str = "";

    switch(player_type)
    {
        case HUMAN      :   player_str = "human";
                            break;
        case COMPUTER   :   player_str = "computer";
                            break;
        default         :   player_str = "none";
                            break;
    }

    return player_str;
}

#endif //__PLAYER_TYPE_H__
