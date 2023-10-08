#include "map.h"
#include <QDebug>
#include <QMouseEvent>
#include <QFile>
#include <QGraphicsItem>
#include <QFile>
#include "cell.h"
#include "Player/player.h"
#include "Unit/unit.h"

const int CELL = 65537;
const int UNIT = 65538;

Map::Map(QWidget *parent)
    : QGraphicsView(parent)
{
    this->file = nullptr;
    this->scene = new QGraphicsScene(this);
    setScene(this->scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   
    //Display the map
    showMap();
    //Load the tmx file
    loadFile(":tiledMap/TiledMap/mapDwar.tmx");
    //Red the tmx file
    readTMX();
}

Map::~Map()
{
}

QList<Cell*> Map::getListCells()
{
    return listCells;
}

//Display the map
void Map::showMap()
{
    QPixmap map(":tiledMap/TiledMap/mapDwar.png");
    scene->addPixmap(map);
}

//update the scene
void Map::updateMap()
{
    this->scene->update();
}

//Load the tmx file
bool Map::loadFile(QString pathFile)
{
    this->file = new QFile(pathFile);

    //Set the XML content of the file
    if(!xmlBOM.setContent(this->file)){
        qDebug()<<"TMXParser ERROR : can't open file";
        return false;
    }
    return true;
}

//Read the tmx file and modify the type of some cell
void Map::readTMX()
{
    QDomElement map = this->xmlBOM.documentElement();
    //set the propeties of the map
    this->nbTilesWidth = map.attribute("width").toInt();
    this->nbTilesheight = map.attribute("height").toInt();
    this->tilesWidth = map.attribute("tilewidth").toInt();
    this->tilesHeight = map.attribute("tileheight").toInt();
    //Make the list of Cell
    makeCells();
    //Make a list of each objectgroup elements
    QDomNodeList nodes = map.elementsByTagName("objectgroup");
    for(int i = 0; i < nodes.count(); i++)
    {
        //Take one object
        QDomNodeList objects = nodes.at(i).toElement().elementsByTagName("object");

        QDomElement object;
        int nb = 0;
        //Browse the Cell list
        for(int j = 0; j < listCells.length(); j++){
            //Set the information of the object
            object = objects.at(nb).toElement();
            int oX = object.attribute("x").toInt();
            int oY = object.attribute("y").toInt();
            int cX = listCells.at(j)->boundingRect().x();
            int cY = listCells.at(j)->boundingRect().y();
            //Check if the object position is equals to the cell position
            if(cX == oX && cY == oY)
            {
                //Change de type of the cell with the object type
                listCells[j]->setType(object.attribute("type").toInt());
                nb++;
            }
        }
    }
}

//Make the Cell list with the type 0
void Map::makeCells(){
    int id = 0;
    int x = 0;
    int y = 0;
    for(int i = 0; i < this->nbTilesheight; ++i)
    {
        for(int j = 0; j < this->nbTilesWidth; ++j)
        {
            //Add a new Cell with the type 0
            Cell* cell = new Cell(id++, 0, x, y, tilesWidth, tilesHeight);
            this->listCells.append(cell);
            x+=tilesWidth;
        }
        y+=tilesHeight;
        x=0;
    }
    //Add all cells to the scene
    addCells();
}

//Add all cells to the scene
void Map::addCells()
{
    for(int i = 0; i < listCells.length(); ++i)
    {
        scene->addItem(listCells.at(i));
    }
}

//Add all units of each army to the scene
void Map::addUnits(QList<Unit*> human, QList<Unit*> ai)
{
    //Ally list
    for(int i = 0; i < human.size(); ++i)
    {
        scene->addItem(human.at(i));
    }
    //Enemy list
    for(int i = 0; i < ai.size(); ++i)
    {
        scene->addItem(ai.at(i));
    }    
}

//Remove all units of the scene
void Map::removeUnit(Unit *unit){
    scene->removeItem(unit);
}

//Management of the mouse press event
void Map::mousePressEvent(QMouseEvent *event){
    //Check if the mouse position is equals with an items
    if(itemAt(event->pos())){
        //Take the items equals to this position
        QList<QGraphicsItem*> list = items(event->pos());
        //Browse the item list
        for(QGraphicsItem* item : list){
            //Check is the item is an Unit
            if(item->type() == UNIT){
                //Emit the unit
                emit clicUnit(qgraphicsitem_cast<Unit*>(item));
            }
        }
        //Browse the item list
        for(QGraphicsItem* item : list){
            //Check is the item is a Cell
            if(item->type() == CELL){
                //Emit the cell
                emit clicCell(qgraphicsitem_cast<Cell*>(item));
            }
        }
        QGraphicsView::mousePressEvent(event);
    }
}

