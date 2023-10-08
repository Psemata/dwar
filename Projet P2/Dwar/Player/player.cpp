#include "player.h"

Player::Player()
{
    golds = 10000;
}

bool Player::addUnit(Unit * u){
    if(golds >= u->getCost()){
        armyList.append(u);
        golds -= u->getCost();
        return true;
    }
    return false;
}

bool Player::removeUnit(Unit * u){
    if(armyList.contains(u)){
        golds += armyList.at(armyList.indexOf(u))->getCost();
        armyList.removeOne(u);
        return true;
    }
    return false;
}

bool Player::removeUnit(int index){
    if(index >= 0 && index <= armyList.size()){
        if(armyList.at(index) != nullptr){
            golds += armyList.at(index)->getCost();
            armyList.removeAt(index);
            return true;
        }
    }
    return false;
}

int Player::getGold(){
    return golds;
}

QList<Unit*> Player::getArmyList()
{
    return armyList;
}
