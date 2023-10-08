#include "unit.h"
#include <QDebug>

const int WASTED = 0;
const int MOVEMENT = 1;
const int ATTACK = 2;

Unit::Unit(int dmg, int hp, int mp, int c, QString name, int r, Cell* ce) : QGraphicsItem()
{
    //Unique ID
    ID = reinterpret_cast<int>(this);
    damage = dmg;
    health = hp;
    movements = mp;
    movementsLeft = mp;
    cost = c;
    className = name;
    range = r;
    cell = ce;
    setSelected(ItemIsSelectable);
    setZValue(99);
    attack = true;
    selection = false;
    target = nullptr;
    idleFrame = 0;
    state = MOVEMENT;
}

bool Unit::Attack(Unit *u){
    attack = false;
    return u->ReceiveDamage(this->getDamage());
}

bool Unit::ReceiveDamage(int hitDamage){
    health -= hitDamage;
    return health <= 0 ? true : false;
}

int Unit::getMovements(){
    return movementsLeft;
}

int Unit::getCost(){
    return cost;
}

int Unit::getDamage(){
    return damage;
}

int Unit::getHP(){
    return health;
}

QString Unit::getClassName() {
    return className;
}

int Unit::getRange() {
    return range;
}

Cell* Unit::getCell() {
    return cell;
}

void Unit::setTarget(Unit *target) {
    this->target = target;
}

Unit* Unit::getTarget() {
    return this->target;
}

QPixmap Unit::getSprite() {
    return currentSprite;
}

//Check if ID are the same
bool Unit::isEquals(Unit *u) {
    if(u != nullptr) {
        if(ID == u->ID) {
            return true;
        }
    }
    return false;
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(cell != nullptr){
        //Draw sprite of unit in the bounding rect of unit
        QRect rect = boundingRect().toRect();
        painter->drawPixmap(rect, currentSprite);
        if(selection){
            //If unit is selected then we draw a yellow rect around unit
            painter->setPen(Qt::yellow);
            painter->drawRect(rect);
        }
    }
    //Which sprite will be drawn depends on state of unit
    switch(state){
    // If unit used all mp or attacked
        case WASTED:
            currentSprite = wastedSprite;
            break;
    // If unit is in movement state
        case MOVEMENT:
            // If there is still movements
            if(movementsLeft > 0){
                // security used to not go over the bounds of an int
                if(this->idleFrame > 10000){
                    this->idleFrame = 0;
                } else {
                    this->idleFrame++;
                }
                setIdle();
            }else{
                currentSprite = wastedSprite;
            }
            break;
    // If unit is in attack state
        case ATTACK:
            if(attack){
                currentSprite = fightSprite;
            }else{
                currentSprite = wastedSprite;
            }
            break;
    }
}

//Bounding rect of unit. Same as the one of its cell
QRectF Unit::boundingRect() const{
    if(this->cell != nullptr){
        // Constructor by copy
        return QRectF(this->cell->boundingRect());
    }else{
        return QRectF();
    }
}

void Unit::setCell(Cell* cell) {
    //Prepare the scene to change its internal index
    //if not done problems will appear
    prepareGeometryChange();
    this->cell = cell;
}

void Unit::moveBy(int m) {
    movementsLeft -= m;
    if(movementsLeft <= 0){
       currentSprite = wastedSprite;
       state = WASTED;
    }
}

bool Unit::isCell() {
    if(cell == nullptr) {
        return false;
    }
    return true;
}

bool Unit::canMove() {
    if(movementsLeft < 0) {
        return true;
    }
    return false;
}

void Unit::resetMove() {
    movementsLeft = movements;
    attack = true;
}

//Type of unit, used to differentiate between unit and cell
int Unit::type() const {
    return UserType + 2;
}

bool Unit::canAttack(){
    return attack;
}

bool Unit::isSelected(){
    return selection;
}

void Unit::setSelected(bool selected){
    selection = selected;
}

void Unit::setAttack(bool attacked){
    attack = attacked;
}

//idleframe is a counter and we change sprite shown every other time
void Unit::setIdle(){
    if(this->idleFrame % 2){
        this->currentSprite = idle1Sprite;
    } else {
        this->currentSprite = idle2Sprite;
    }

}

void Unit::setState(int state){
    this->state = state;
}
