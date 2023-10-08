#pragma once

#include "Unit/unit.h"

class Archer : public Unit
{
public:
    Archer(QString color);
    bool Attack(Unit * u);
};
