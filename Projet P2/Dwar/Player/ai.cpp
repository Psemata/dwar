#include "ai.h"
#include <QtMath>

AI::AI() : Player() {

}

// Process the distance between two units
double AI::distance(Unit * unit1, Unit * unit2) {
    return (qSqrt(qPow(unit1->boundingRect().x() - unit2->boundingRect().x(), 2) + qPow(unit1->boundingRect().y() - unit2->boundingRect().y(), 2))/32);
}

// Get smallest distance between a selected unit and all the enemy units
double AI::getSmallestDistance(Unit* unit, QList<Unit *> playerList) {
    double min = distance(unit, playerList[0]);
    for(int i = 1; i < playerList.size(); i++){
        if(distance(unit, playerList[i]) < min){
            min = distance(unit, playerList[i]);
        }
    }
    return min;
}

// <<Quick Sort>> used to sort the IA units - a unit has a greater priority the nearer they are from an enemy unit
int AI::teamSort(Player * human, int start, int size) {

    if ((size - start) < 2) {
        return start;
    }
    double a0 = getSmallestDistance(this->getArmyList()[start], human->getArmyList());
    int index = start+1;

    while (index < size && getSmallestDistance(this->getArmyList()[index], human->getArmyList()) < a0) {
        index++;
    }

    for (int i = index + 1; i < size; i++) {
        if (getSmallestDistance(this->getArmyList()[i], human->getArmyList()) < a0) {
            this->armyList.swapItemsAt(index, i);
            index++;
        }
    }
    index--;
    this->armyList.swapItemsAt(start, index);

    teamSort(human, start, index+1);
    teamSort(human, index+1, size);

    return index;
}

// Get the closest enemy unit from a selected unit and set it as a target
void AI::target(Unit* unit, QList<Unit *> playerList) {
    Unit* target = playerList[0];
    double min = distance(unit, target);
    for(int i = 1; i < playerList.size(); i++){
        if(distance(unit, playerList[i]) < min){
            min = distance(unit, playerList[i]);
            target = playerList[i];
        }
    }

    unit->setTarget(target);
}


