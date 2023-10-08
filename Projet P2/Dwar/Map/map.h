#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QtXml>

class QFile;
class Cell;
class Player;
class Unit;

class Map : public QGraphicsView
{
    Q_OBJECT
public:
    Map(QWidget *parent = nullptr);
    ~Map();
    QList<Cell*> getListCells();
    //Add all units to the scene
    void addUnits(QList<Unit*> human, QList<Unit*> ai);
    //Remove all units to the scene
    void removeUnit(Unit* unit);
    void updateMap();
private:
    QGraphicsScene *scene;
    QFile* file;
    QDomDocument xmlBOM;
    QList<Cell*> listCells;
    int nbTilesWidth;
    int nbTilesheight;
    int tilesWidth;
    int tilesHeight;
    void showMap();
    void makeCells();
    //Add cells to the scene
    void addCells();    
    void readTMX();
    void mousePressEvent(QMouseEvent *event);
    bool loadFile(QString pathFile);

signals:
    void clicCell(Cell* cell);
    void clicUnit(Unit* unit);
};
