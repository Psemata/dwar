#pragma once
#include <QWidget>

class Player;
class Human;
class AI;
class QListWidget;
class Unit;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class ArmyList;
class QPushButton;
class ClickableLabel;

class ArmySelectionMenu : public QWidget {
    Q_OBJECT
public:
    ArmySelectionMenu(QWidget *parent = nullptr);
    ~ArmySelectionMenu();    
    void setConditions(int val, bool ai);
private:
    QLabel *unitName, *unitDmg, *unitHealth, *unitMovements, *unitCost;

    Human *human;
    AI *ai;
    Player *currentPlayer;

    int classSelected = 0;
    int selectedIndex = -1;
    int turn = 0;

    bool selectionByAi;
    int difficultyValue;

    ArmyList* allyList;
    ArmyList* enemyList;

    QPushButton* buttonAdd;
    QPushButton* buttonRemove;
    QPushButton* buttonValidate;

    ClickableLabel* labelArcher;
    ClickableLabel* labelRider;
    ClickableLabel* labelSaber;

    QHBoxLayout* layoutPrincipal;
    QVBoxLayout* layoutAllyArmy;
    QVBoxLayout* layoutMiddle;
    QVBoxLayout* layoutMainDescrption;
    QHBoxLayout* layoutUnit;
    QHBoxLayout* layoutButton;
    QHBoxLayout* layoutShopButton;
    QVBoxLayout* layoutEnemyLayout;

    void connection();
    void initLayout();
    void initLabelUnit();
    void initDescription();
    void initButton();
    void initArmyList();
    void setDesciption(Unit* unit);
    //  Different fonctions used to add units to the AI
    void addEasy();
    void addIntermediate();
    void addDifficult();
signals:
    void armyChoosen(Human* human, AI* ai);
};
