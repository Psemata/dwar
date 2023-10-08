#include "archer.h"

//Damage, HP, MP, Cost, Name, Range
Archer::Archer(QString color) : Unit(7, 18, 2, 450, "Archer", 3, nullptr)
{    
    fightSprite = QPixmap(":classes/Images/"+color+"/Archer/sprite_archer_fight_"+color+"_1.png");
    idle1Sprite = QPixmap(":classes/Images/"+color+"/Archer/sprite_archer_idle_"+color+"_1.png");
    idle2Sprite = QPixmap(":classes/Images/"+color+"/Archer/sprite_archer_idle_"+color+"_2.png");
    wastedSprite = QPixmap(":classes/Images/blue/Archer/sprite_archer_wasted_blue_1.png");
    currentSprite = idle1Sprite;
}

bool Archer::Attack(Unit * u){
    if(canAttack()){
        //Set attack at false because we can only attack once
        setAttack(false);
        //If unit is a Saber then we do 1.5 damage
        if(strcasecmp(u->getClassName().toStdString().c_str(),"Saber")){
            return u->ReceiveDamage(this->getDamage() * 1.5);
        }else{
            return u->ReceiveDamage(this->getDamage());
        }
    }
    return false;
}
