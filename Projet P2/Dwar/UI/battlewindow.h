#pragma once

#include <QWidget>

class Map;
class Human;
class AI;
class Player;
class Unit;
class Cell;
class DisplayStats;

// node used to resolve the pathfinding algorithm
struct node{
    // costG => cost to go from the start node to the studied node
    // costH => cost to go from the studied node to the end node
    // costF => the sum of the two above
    double costG, costH, costF;
    int parentID;
};

// typedef to facilite the use of map<int, node>
typedef std::map<int, node> listNode;

class BattleWindow : public QWidget {
    Q_OBJECT
public:
    BattleWindow(QWidget *parent = nullptr);
    ~BattleWindow();
    void setPlayers(Human* human, AI* ai);

private:
    Player* human;
    Player* ai;
    Map* map;
    DisplayStats* displayStats;
    Unit* unitSelected;
    //0 = idle => no unit selected, 1 = movement => unit selected, 2 = attack => unit selected
    int state;
    int turn;
    QList<Cell*> cells;

    // Function used for the units
    void moveUnitToCell(Cell* cell);
    void spawnBase();

    // Function used to help the game process
    Unit* isUnitOnCell(Cell* cell);
    QList<Cell*> cellsInRange(int range, Cell* cell);    
    void clearCells();
    void changeStates();

    // Used for AI
    Cell* destinationTarget(Unit* IAunit, Unit* targetUnit);
    void IATurn();

    // Timer used for animations sprites
    QTimer * timer;
    void checkSprites();

    // Function used for the pathfinding
    double distance(Cell * cell1, Cell * cell2);
    bool isPresent(int id, listNode & l);
    void addNearbyCell(int id, listNode & closedList, listNode & openList, Cell * destination);
    int bestNode(listNode & l);
    void addClosedList(listNode & closedList, listNode & openList, int id);
    void traceWay(listNode & closedList, QList<Cell*> & path, Cell * destination);
    QList<Cell*> pathfinding(Cell* dest, Cell* currentCell);

public slots :
    // Slots used to play the game
    void receiveCell(Cell* cell);
    void receiveUnit(Unit* unit);
signals :
    void winner(bool who);
};
