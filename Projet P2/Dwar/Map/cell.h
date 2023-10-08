#pragma once

#include <QGraphicsItem>
#include <QRectF>
#include <QObject>

class Cell : public QGraphicsItem {
public:
    Cell(int id, int type, int x, int y, int width, int height);
    Cell(Cell& cell);
    int getType();
    int getId();
    void setType(int type);
    void setState(int state);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    QRectF boundingRect() const;
private:
    int id;
    //0 default type, 1 solid case, 2 forest, 3 mountain, 41 ally spawn, 42 ennemy spawn
    int typeCell;
    //0 nothing, 1 movement, 2 attack
    int state;
    QRectF bounds;
};
