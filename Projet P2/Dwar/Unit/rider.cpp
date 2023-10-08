#include "rider.h"

//Damage, HP, MP, Cost, Name, Range
Rider::Rider(QString color) : Unit(4, 35, 5, 600, "Rider", 1, nullptr)
{
    fightSprite = QPixmap(":classes/Images/"+color+"/Rider/sprite_rider_fight_"+color+"_1.png");
    idle1Sprite = QPixmap(":classes/Images/"+color+"/Rider/sprite_rider_idle_"+color+"_1.png");
    idle2Sprite = QPixmap(":classes/Images/"+color+"/Rider/sprite_rider_idle_"+color+"_2.png");
    wastedSprite = QPixmap(":classes/Images/blue/Rider/sprite_rider_wasted_blue_1.png");
    currentSprite = idle1Sprite;
}

bool Rider::Attack(Unit* u){
    if(canAttack()){
        //Set attack at false because we can only attack once
        setAttack(false);
        //If unit is an Archer then we do 1.5 damage
        if(strcasecmp(u->getClassName().toStdString().c_str(),"Archer")){
            return u->ReceiveDamage(this->getDamage() * 1.5);
        }else{
            return u->ReceiveDamage(this->getDamage());
        }
    }
    return false;
}
