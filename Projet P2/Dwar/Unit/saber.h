#pragma once

#include "Unit/unit.h"

class Saber : public Unit
{
public:
    Saber(QString color);
    bool Attack(Unit * u);
};

