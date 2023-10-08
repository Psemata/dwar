#pragma once

#include <string>
#include <strings.h>
#include <QPixmap>
#include <QGraphicsItem>
#include <QPainter>
#include "Map/cell.h"
#include <QRectF>

class Unit : public QGraphicsItem
{
public:
    Unit(int dmg, int hp, int mp, int cost, QString name, int r, Cell* cell);
    bool Attack(Unit * u);
    bool ReceiveDamage(int hitDamage);
    int getMovements();
    int getCost();
    int getDamage();
    int getHP();
    QPixmap getSprite();
    QString getClassName();
    int getRange();
    Cell* getCell();
    bool isEquals(Unit * u);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setCell(Cell* cell);
    void setSelected(bool selection);
    void setAttack(bool attacked);
    void moveBy(int m);
    bool canMove();
    void resetMove();
    bool isCell();
    bool isSelected();
    bool canAttack();    
    int type() const;

    void setIdle();
    void setState(int state);

    Unit* getTarget();
    void setTarget(Unit* target);

private:
    int ID;
    int cost;
    int health;
    int damage;
    //Base movements, never change
    int movements;
    //Movements left
    int movementsLeft;
    //counter for changing sprites when movement
    int idleFrame;
    bool attack;
    int range;
    //If unit is selected
    bool selection;
    //State of unit for sprites
    int state;
    QString className;
    //Cell where the unit is
    Cell* cell;
    //Target of unit, used for AI
    Unit* target;
protected:
    QPixmap currentSprite, fightSprite, idle1Sprite, idle2Sprite, wastedSprite;
};

