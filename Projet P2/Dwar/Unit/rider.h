#pragma once

#include "Unit/unit.h"

class Rider : public Unit
{
public:
    Rider(QString color);
    bool Attack(Unit * u);
};

