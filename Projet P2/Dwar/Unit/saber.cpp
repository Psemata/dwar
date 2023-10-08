#include "saber.h"

//Damage, HP, MP, Cost, Name, Range
Saber::Saber(QString color) : Unit(10, 25, 3, 500, "Saber", 1 ,nullptr)
{
    fightSprite = QPixmap(":classes/Images/"+color+"/Saber/sprite_saber_fight_"+color+"_1.png");
    idle1Sprite = QPixmap(":classes/Images/"+color+"/Saber/sprite_saber_idle_"+color+"_1.png");
    idle2Sprite = QPixmap(":classes/Images/"+color+"/Saber/sprite_saber_idle_"+color+"_2.png");
    wastedSprite = QPixmap(":classes/Images/blue/Saber/sprite_saber_wasted_blue_1.png");
    currentSprite = idle1Sprite;
}

bool Saber::Attack(Unit * u){
    if(canAttack()){
        //Set attack at false because we can only attack once
        setAttack(false);
        //If unit is a Rider then we do 1.5 damage
        if(strcasecmp(u->getClassName().toStdString().c_str(),"Rider")){
            return u->ReceiveDamage(this->getDamage() * 1.5);
        }else{
            return u->ReceiveDamage(this->getDamage());
        }
    }
    return false;
}
