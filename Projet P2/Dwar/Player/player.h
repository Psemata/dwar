#pragma once

#include "Unit/unit.h"

class Player {
public:
    Player();
    bool addUnit(Unit * u);
    bool removeUnit(Unit * u);
    bool removeUnit(int index);
    int getGold();
    QList<Unit*> getArmyList();
    QList<Unit*> armyList;

private:
    int golds;

};

