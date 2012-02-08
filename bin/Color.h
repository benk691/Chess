#pragma once
#ifndef __COLOR_H__
#define __COLOR_H__

#include <string>

enum Color
{
    BLACK,
    WHITE,
    BLANK
};

std::string strColor(const Color &color)
{
    std::string color_str = "";

    switch(color)
    {
        case WHITE  :   color_str = "white";
                        break;
        case BLACK  :   color_str = "black";
                        break;
        default     :   color_str = "none";
                        break;
    }

    return color_str;
}

#endif //__COLOR_H__
