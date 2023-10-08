#include "cell.h"
#include <QPainter>
#include <QDebug>

const int ALLYCELL = 41;
const int ENNEMYCELL = 42;
const int MOVEMENT = 1;
const int ATTACK = 2;

Cell::Cell(int id, int type, int x, int y, int width, int height) : QGraphicsItem()
{
    this->id = id;
    this->typeCell = type;
    this->state = 0;
    this->bounds.setX(x);
    this->bounds.setY(y);
    this->bounds.setWidth(width);
    this->bounds.setHeight(height);
    setFlags(ItemIsSelectable);
    setZValue(10);
}

//Construct by copy
Cell::Cell(Cell & cell){
    this->id = cell.id;
    this->typeCell = cell.typeCell;
    this->state = cell.state;
    this->bounds.setX(cell.bounds.x());
    this->bounds.setY(cell.bounds.y());
    this->bounds.setWidth(cell.bounds.width());
    this->bounds.setHeight(cell.bounds.height());
    setFlags(ItemIsSelectable);
    setZValue(10);
}

int Cell::getType()
{
    return this->typeCell;
}

int Cell::getId(){
    return this->id;
}

void Cell::setType(int type)
{
    this->typeCell = type;
}

void Cell::setState(int state){
    this->state = state;
}

//Draw the border of the cell
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //Basic color
    QColor color(Qt::black);
    color.setAlphaF(0.15);
    painter->setPen(QPen(color));

    if(typeCell == ALLYCELL){
        //blue border for ally spawn cells
        painter->setPen(Qt::blue);
    }
    else if(typeCell == ENNEMYCELL)
    {
        //red color for ennemy spawn cells
        painter->setPen(Qt::red);
    }

    if(state == MOVEMENT){
        //green color when the state is mouvement
        painter->setPen(Qt::green);
    }
    else if(state == ATTACK)
    {
        //red color when the state is attack
        painter->setPen(Qt::red);
    }
    painter->drawRect(bounds);
}

//return the size of the cell
QRectF Cell::boundingRect() const
{
    return this->bounds;
}

int Cell::type() const {
    return UserType + 1;
}


