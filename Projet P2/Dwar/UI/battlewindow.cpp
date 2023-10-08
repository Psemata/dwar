#include "battlewindow.h"
#include "Map/map.h"
#include "Map/cell.h"
#include "Player/player.h"
#include "Player/ai.h"
#include "Player/human.h"
#include "Unit/unit.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QtMath>
#include "displaystats.h"
#include "UI/buttonaction.h"

// CONSTANT - Last cell's id
const int IDMAX = 625;
const int SPAWN = 0;
const int MOVEMENT = 1;
const int ATTACK = 2;
const int ALLYTURN = 1;
const int ENNEMYTURN = 2;
const int ALLYCELL = 41;
const int ENNEMYCELL = 42;
const int RIVERCELL = 1;
const int PLAINCELL = 0;

BattleWindow::BattleWindow(QWidget *parent) : QWidget(parent) {
    this->human = nullptr;
    this->ai = nullptr;
    this->unitSelected = nullptr;
    this->state = SPAWN;
    this->turn = ALLYTURN;
    this->map = new Map();
    this->displayStats = new DisplayStats();

    this->timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &BattleWindow::checkSprites);

    QHBoxLayout* layoutPrincipal = new QHBoxLayout();
    layoutPrincipal->addWidget(displayStats);
    layoutPrincipal->addWidget(map);

    ButtonAction* buttonAction = new ButtonAction(this);
    buttonAction->setTurn(this->turn, this->state);

    connect(buttonAction->getNextTurn(), &QPushButton::clicked,[=]() {
        //If we are not in spawn state that means that we finished attacking and
        // end turn
        if(state != SPAWN){
            buttonAction->getNextTurn()->setEnabled(false);
            state = MOVEMENT;
            changeStates();
            buttonAction->getAttack()->setEnabled(true);
            if(turn == ALLYTURN){
                //Reset of units movements and attacks
                for(Unit* u : human->getArmyList()){
                    u->resetMove();
                }
            }
        //If we are in spawn mode and it's ennemy turn, that means that we want
        // to change to stop spawn mode and get into movement mode
        }else if(state == SPAWN && turn == ENNEMYTURN){
            buttonAction->getNextTurn()->setEnabled(false);
            state = MOVEMENT;
            changeStates();
            buttonAction->getAttack()->setEnabled(true);
            cells = map->getListCells();
            //Resets all cells from spawn to plain
            for(Cell* cell : cells){
                if(cell->getType() == ALLYCELL || cell->getType() == ENNEMYCELL){
                    cell->setType(PLAINCELL);
                }
            }
            map->updateMap();
        //If we are in spawn mode and it's ally turn, that means that we want
        // to move ennemy units
        } else if(state == SPAWN && turn == ALLYTURN){
            turn = ENNEMYTURN;
        }
        //If we arrive here and we are still in movement mode, that means that
        // we were in attack mode and we finished our turn and IA plays
        if(state == MOVEMENT){
            turn = ENNEMYTURN;
            buttonAction->setTurn(this->turn, this->state);
            // IA turn
            IATurn();
            turn = ALLYTURN;
        }
        clearCells();
        buttonAction->setTurn(this->turn, this->state);
    });

    connect(buttonAction->getAttack(), &QPushButton::clicked,[=]() {
        state = ATTACK;
        changeStates();
        buttonAction->getAttack()->setEnabled(false);
        buttonAction->getNextTurn()->setEnabled(true);
        clearCells();
        buttonAction->setTurn(this->turn, this->state);
    });
	
    layoutPrincipal->addWidget(buttonAction);
    setLayout(layoutPrincipal);
}

BattleWindow::~BattleWindow() {

}

// SLOTS SECTION

void BattleWindow::receiveCell(Cell* cell) {
    qDebug() << "Receive cell " << cell->getType();
    //Reset values of the stats
    if(isUnitOnCell(cell) == nullptr) {
        if(unitSelected != nullptr && unitSelected->getCell() != cell){
            displayStats->reset();
        }else if(unitSelected == nullptr) {
            displayStats->reset();
        }
    }

    //If cell clicked is part of cells where unit can move then we move
    if(cells.contains(cell) && state != ATTACK) {
        moveUnitToCell(cell);
    //If there is a unit selected and where we click is not on unit nor on
    // cells where unit can move then we unselect unit
    }else if(unitSelected != nullptr && cell != unitSelected->getCell()){
        clearCells();
    }
}

void BattleWindow::receiveUnit(Unit* unit) {

    qDebug() << unit->getHP();
    //Reset or set values of the stats
    if(unitSelected == nullptr){
        displayStats->setValue(unit);
    } else {
        displayStats->reset();
    }

    //If an unit is selected and unit clicked is within the range of attack of unit
    //selected and we are in attack mode then we attack
    if(unitSelected != nullptr && cells.contains(unit->getCell()) && state == ATTACK){
        //If unit we want to attack is not in same team
        if((human->getArmyList().contains(unit) && ai->getArmyList().contains(unitSelected))
            || (human->getArmyList().contains(unitSelected) && ai->getArmyList().contains(unit))){
            unitSelected->Attack(unit);
            if(unit->getHP() <= 0){
                map->removeUnit(unit);
                if(ai->getArmyList().contains(unit)){
                    ai->removeUnit(unit);
                    if(ai->getArmyList().size() == 0){
                        //Win human
                        emit winner(true);
                    }
                }
            }
        }
        clearCells();
    }else if(unitSelected == nullptr){
        //If unit we clicked is our own
        if((turn == ALLYTURN && human->getArmyList().contains(unit)) || (turn == ENNEMYTURN && ai->getArmyList().contains(unit)) ){
            unitSelected = unit;
            unit->setSelected(true);
            if(state == MOVEMENT){
                //Accessible cells are the ones in movement range
                cells = cellsInRange(unit->getMovements(), unit->getCell());
                //put in green
                for(int i = 0; i < cells.size(); i++){
                    cells[i]->setState(MOVEMENT);
                }
            }else if(state == SPAWN){
                //Accessible cells are the ones corresponding in type
                Cell* cell = unit->getCell();
                for(Cell* c : map->getListCells()){
                    if(c != cell && c->getType() == cell->getType()){
                        cells.append(c);
                    }
                }
            }else if(state == ATTACK){
                //Accessible cells are the ones in attack range
                if(unit->canAttack()){
                    cells = cellsInRange(unit->getRange(), unit->getCell());
                    //put in red
                    for(int i = 0; i < cells.size(); i++){
                        cells[i]->setState(ATTACK);
                    }
                }
            }
            this->map->updateMap();
        }
    }
}

// TRANSITION METHOD

void BattleWindow::setPlayers(Human* human, AI* ai) {
    this->human = human;
    this->ai = ai;
    this->map->addUnits(human->getArmyList(), ai->getArmyList());
    this->timer->start(500);
	QObject::connect(map, &Map::clicCell, this, &BattleWindow::receiveCell);
    QObject::connect(map, &Map::clicUnit, this, &BattleWindow::receiveUnit);
    spawnBase();
}

// UNIT SECTION

void BattleWindow::moveUnitToCell(Cell* cell){
    if(state == MOVEMENT){
        //If there is no unit where we click
        Unit* unit = isUnitOnCell(cell);
        if(unit == nullptr){
            //Get list of cells
            QList<Cell*> path = pathfinding(cell, unitSelected->getCell());
            unitSelected->moveBy(path.size()-1);
            unitSelected->setCell(cell);
        }
    }
    if(state == SPAWN){
        //If there is an unit on the cell we click, we swap cells
        Unit* unit = isUnitOnCell(cell);
        if(unit != nullptr){
            unit->setCell(unitSelected->getCell());
        }
        unitSelected->setCell(cell);
    }
    clearCells();
}

void BattleWindow::spawnBase() {
    int nbHuman = human->getArmyList().size()-1;
    int nbIa = ai->getArmyList().size()-1;
    for(int i = 0; i < map->getListCells().length(); i++)
    {
        if(map->getListCells().at(i)->getType() == ALLYCELL){
            if(nbHuman >= 0){
                this->human->getArmyList().at(nbHuman)->setCell(map->getListCells().at(i));
                nbHuman--;
            }
        }else if(map->getListCells().at(i)->getType() == ENNEMYCELL){
            if(nbIa >= 0){
                this->ai->getArmyList().at(nbIa)->setCell(map->getListCells().at(i));
                nbIa--;
            }
        }
    }
    this->map->updateMap();
}

// HELP SECTION

Unit* BattleWindow::isUnitOnCell(Cell* cell){
    for(Unit* unit : human->getArmyList()){
        if(unit->getCell() == cell && !unit->isEquals(unitSelected)){
            return unit;
        }
    }
    for(Unit* unit : ai->getArmyList()){
        if(unit->getCell() == cell && !unit->isEquals(unitSelected) ){
            return unit;
        }
    }
    return nullptr;
}

QList<Cell*> BattleWindow::cellsInRange(int range, Cell* cell){
    QList<Cell*> cellsInRange;
    cellsInRange.push_back(cell);
    QList<Cell*> cells = map->getListCells();
    int stepY = 1;

    //change direction of X axe, first on right then on left
    for(int j = 0; j < 2; j++){
        //StepX goes by one down
        int stepX = 25;
        int index = cells.indexOf(cell);
        bool isBlocked = false;
        //Goes on the direction of X axe
        for(int i = 0; i < range; i++){
            stepX = 25;
            //change direction of Y axem first bottom then top
            for(int m = 0; m < 2; m++){
                isBlocked = false;
                //Goes on the direction of Y axe
                for(int k = 0; k <= range-i; k++){
                    //Distance of cell from base cell
                    int distance = index + stepY*i + stepX*k;
                    if(distance <= cells.size()-1 && distance >= 0){
                        Cell* cellInRange = cells.at(distance);
                        //If cell has already been added, then we skip this line
                        if(cellsInRange.contains(cellInRange) && i != 0){
                            continue;
                        }
                        int stepY2 = stepY;
                        //Change Y axe
                        for(int n = 0; n < 2; n++){
                            //Goes right then left but not on Y axe only
                            for(int l = 0; l <= range-i-k; l++){
                                distance = index + stepY*i + stepX*k + stepY2*l;
                                if(distance <= cells.size()-1 && distance >= 0){
                                    cellInRange = cells.at(distance);
                                    if(cellInRange != nullptr && cellInRange->getType() != RIVERCELL && isUnitOnCell(cellInRange) == nullptr){
                                        if(!cellsInRange.contains(cellInRange)){
                                            cellsInRange.append(cellInRange);
                                        }else{
                                            continue;
                                        }
                                    }else if(cellInRange != nullptr && cellInRange->getType() != RIVERCELL && state == ATTACK){
                                        if(!cellsInRange.contains(cellInRange)){
                                            cellsInRange.append(cellInRange);
                                        }else{
                                            continue;
                                        }
                                    }else{
                                        //If the cell where we are is a cell we
                                        //are not allowed to go to
                                        //We break the upper loop (k one)
                                        //So we do not continue up or down
                                        if(l == 0){
                                            isBlocked = true;
                                        }
                                        break;
                                    }
                                }
                            }
                            stepY2 = stepY*-1;
                        }
                        //break k loop
                        if(isBlocked){
                            break;
                        }
                    }
                }
                stepX = -25;
            }
        }
        stepY = -1;
    }
    //remove cell where is unit
    cellsInRange.removeOne(cell);

    return cellsInRange;
}

//Reset cells and unitSelected
void BattleWindow::clearCells(){
    for(int i = 0; i < cells.size(); i++){
        cells[i]->setState(SPAWN);
    }
    cells.clear();
    if(unitSelected != nullptr){
        unitSelected->setSelected(false);
    }
    unitSelected = nullptr;
    this->map->updateMap();
}

//Change states of all units in state of the game
void BattleWindow::changeStates(){
    for(Unit* unit : human->armyList){
        unit->setState(this->state);
    }
    for(Unit* unit : ai->armyList){
        unit->setState(this->state);
    }
}

// AI SECTION

// Get the destination for an AI : the cell has to be the nearest from its target
Cell* BattleWindow::destinationTarget(Unit* IAunit, Unit* targetUnit) {
    // Get the cells in the movement range of the unit
    QList<Cell *> movementRange = cellsInRange(IAunit->getMovements(), IAunit->getCell());
    // Get the cells in the attack range of the unit
    QList<Cell *> attackRange = cellsInRange(IAunit->getRange(), IAunit->getCell());
    // Get the cell of the target unit
    Cell * targetPosition = targetUnit->getCell();

    // Get the cell which has the smallest distance to the targetPosition
    Cell * targetDestination = IAunit->getCell();
    // Move only if he can and if he should
    if(!movementRange.empty() && !attackRange.contains(targetPosition)){
        double min = distance(movementRange[0], targetPosition);
        for(Cell * cell : movementRange) {
            if(distance(cell, targetPosition) < min){
                targetDestination = cell;
                min = distance(cell, targetPosition);
            }
        }
    }

    // Return the targetDestination
    return targetDestination;
}

// Function used to make the AI play
void BattleWindow::IATurn(){
    // Get the AI (Player) as a AI
    AI * ia = static_cast<AI*>(this->ai);
    // Sort the order of the team
    ia->teamSort(this->human, 0, this->ai->getArmyList().size());

    for(Unit * unit : ia->getArmyList()){
        this->unitSelected = unit;
        // Set a target to the current unit
        ia->target(unitSelected, this->human->getArmyList());
        // Move the unit to its destination
        if(unitSelected->getTarget() != nullptr){
            Cell * destination = destinationTarget(unitSelected, unitSelected->getTarget());
            if(destination != unit->getCell()){
                this->moveUnitToCell(destination);
            }
        }
    }

    // Combat mode
    state = ATTACK;

    for(Unit * unit : ia->getArmyList()){
        this->unitSelected = unit;
        ia->target(unitSelected, this->human->getArmyList());
        Unit * target = unitSelected->getTarget();
        // The current unit attack its target if it's in the range
        QList<Cell *> attackRange = cellsInRange(unitSelected->getRange(), unitSelected->getCell());
        if(attackRange.contains(target->getCell())){
            // Then the unit can attack its target
            unitSelected->Attack(target);
            // Check if the unit is dead
            if(target->getHP() <= 0){
                // if it is, remove it from the map and the list
                map->removeUnit(target);
                if(human->getArmyList().contains(target)){
                    human->removeUnit(target);
                    // finally, check if the AI has won the game
                    if(human->getArmyList().size() == 0){
                        //Win IA
                        emit winner(false);
                        break;
                    }
                }
            }

        }
    }

    // Pass the turn
    state = MOVEMENT;

    // reset the movements of ia's units
    if(!(ia->getArmyList().empty())){
        for(Unit* u : ia->getArmyList()){
            u->resetMove();
        }
    }

    clearCells();
}

// TIMER SECTION
// Update the units animation
void BattleWindow::checkSprites(){
    for(Unit * unit : this->ai->getArmyList()){
        unit->update();
    }
    for(Unit * unit : this->human->getArmyList()){
        unit->update();
    }
}

// PATHFINDING SECTION

// Process the distance between two cells
double BattleWindow::distance(Cell * cell1, Cell * cell2) {
    // return the distance between two cells in cell unit (for exemple, two cells between them
    return qSqrt(qPow(cell1->boundingRect().x() - cell2->boundingRect().x(), 2) + qPow(cell1->boundingRect().y() - cell2->boundingRect().y(), 2));
}

// Check if a node is in one of the list
bool BattleWindow::isPresent(int id, listNode& l) {
    listNode::iterator i = l.find(id);
    if(i != l.end()) {
        return true;
    } else {
        return false;
    }
}

// Add the adjacent cells to a list
void BattleWindow::addNearbyCell(int id, listNode & closedList, listNode & openList, Cell * destination) {
    // create temporary node to be used to study
    node tmp;
    // list used to study all possibilities around the studied cell
    QList<int> listID;
    // get the cell which is at the start (id studied)
    Cell * departureCell = map->getListCells()[id];
    // cell which will contain each cell around departureCell
    Cell * studiedCell;
    // comparison between cells adjacent to the studied one (processed with ids as keys) {left, top, center, right, bottom : a cross}
    for(int i = id-1; i <= id+1; i++){
        // if it is outside the map, we continue
        if(i < 0 || i >= IDMAX){
            continue;
        }
        // if the cells are not in the center column of the cross
        if(i < id || i > id){
            // get the cell at the respective id
            studiedCell = map->getListCells()[i];
            // if the cell at the studied id is occupied or a wall/river/etc.. then we forget it
            if(studiedCell->getType() == RIVERCELL || isUnitOnCell(studiedCell) != nullptr){
                continue;
            } else {
                // otherwise, we save the cell's id as a path possibility
                listID.append(i);
            }
        // if the cells are in the center column of the cross
        } else if(i == id) {
            for(int j = i-25; j <= i+25; j += 25) {
                // if it is outside the map, we continue
                if((j < 0) || j > IDMAX) {
                    continue;
                }
                // if it's the center cell, we continue
                if(j == id) {
                    continue;
                }
                // if the cell at the studied id is occupied or a wall/river then
                studiedCell = map->getListCells()[j];
                if(studiedCell->getType() == RIVERCELL || isUnitOnCell(studiedCell) != nullptr) {
                    continue;
                }
                // if the cell is a possibility, we save it
                listID.append(j);
            }
        }
    }
    for(int idTemp : listID) {
        // if the studied cell isn't in the closedList, then we process it and add it to the openList
        if(!isPresent(idTemp, closedList)){
            // Calcul of the G cost of the studied node : cost of the parent + distance to the parent
            tmp.costG = closedList[id].costG + distance(studiedCell, departureCell);
            // Calcul of the H cost of the studied node : distance of the studied node to the destination
            tmp.costH = distance(studiedCell, destination);
            // Sum of the two above
            tmp.costF = tmp.costH + tmp.costG;
            tmp.parentID = id;

            // if it is present in the openList
            if(isPresent(idTemp, openList)){
                // we compare it with its homonym
                if(tmp.costF < openList[idTemp].costF){
                    // if it's better, we replace it
                    openList[idTemp]=tmp;
                }
            } else {
              // if the studied cell is not in the closedList, we add it in the openList first
              openList[idTemp] = tmp;
            }
        }
    }
}

// Return the best node in the open list
int BattleWindow::bestNode(listNode & l) {
    // Get the costF from the first element
    double costFTemp = l.begin()->second.costF;
    // Get the id from the first element
    int idTemp = l.begin()->first;

    // Process the list (openList) to find which is the element which has the smallest costF
    for(listNode::iterator i = l.begin(); i != l.end();i++){
        if(i->second.costF < costFTemp){
            costFTemp = i->second.costF;
            idTemp = i->first;
        }
    }

    // Return the id from the smallest element
    return idTemp;
}

// Add an element,  from the openlist to the closedlist
void BattleWindow::addClosedList(listNode & closedList, listNode & openList, int id) {
    // Add it to the closed list
    closedList[id] = openList[id];
    // Erase it from the open list
    openList.erase(id);
}

// Create the path from the end to the beginning
void BattleWindow::traceWay(listNode & closedList, QList<Cell*> & path, Cell * destination) {
    // Create a temporary node which is used to represent the destination
    node tmp = closedList[destination->getId()];

    // Copy the destination cell
    Cell * cell = destination;
    // Get the parent id from the tmp node
    int previous = tmp.parentID;
    // Add the cell to the path
    path.push_front(cell);

    // As long as it's not the end of the path
    while(previous != -1){
        // Get the previous cell
        cell = map->getListCells()[previous];
        // Add it to the path
        path.push_front(cell);

        // Set the next id to be added
        tmp = closedList[tmp.parentID];
        previous = tmp.parentID;
    }
}

// Final method for the pathfinding
QList<Cell*> BattleWindow::pathfinding(Cell* dest, Cell* currentCell) {
    // list used to study the path
    listNode closedList;
    listNode openList;

    // list final
    QList <Cell *> path;

    // Get the destination
    Cell * destination = dest;

    // Get the ide of the currentCell (departure)
    int current = currentCell->getId();
    // node created which represents the departure
    node departure;
    // value which means it's the first cell (special value to set the beginning of the path)
    departure.parentID = -1;

    // add the start to the openList
    openList[current] = departure;
    // then add it to the closedList (the start is mandatorily in the path)
    addClosedList(closedList, openList, current);
    // start to add nearby cells to the openList
    addNearbyCell(current, closedList, openList, destination);

    while((current != destination->getId()) && (!openList.empty())){
        // get the best node in the openList
        current = bestNode(openList);
        // add the best node to the closedList (best path possible)
        addClosedList(closedList, openList, current);
        // we start the search all over again until we get to the destination
        addNearbyCell(current, closedList, openList, destination);
    }

    // if the destination is reached, we get back up to the beginning to recreate the path
    if(current == destination->getId()){
        // get the path back
        traceWay(closedList, path, destination);
    }

    return path;
}
