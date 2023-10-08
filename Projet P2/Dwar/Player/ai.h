#pragma once

#include "player.h"

class AI : public Player {
private:
    // Function used to get the distance between two units
    double distance(Unit * unit1, Unit * unit2);
    // Function get the smallest distance between a unit and a list of units
    double getSmallestDistance(Unit* unit, QList<Unit *> playerList);
public:
    AI();
    // An algorithm used to sort the unit list due to their distance with the
    int teamSort(Player * human, int start, int size);
    // Function used to target the nearest enemy unit from the AI unit
    void target(Unit* unit, QList<Unit *> playerList);
};
