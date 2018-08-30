//
// Created by Rob on 7/16/2018.
//

#include "GameData.h"


std::ostream &operator<<(std::ostream &os, const GameData &game_data) {
    game_data.print(os);
    return os;
}
