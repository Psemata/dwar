#pragma once
#include <QWidget>

class MainMenu;
class ArmySelectionMenu;
class BattleWindow;
class EndMenu;
class QStackedLayout;
class Player;
class Human;
class AI;

class MainWidget : public QWidget {
    Q_OBJECT

private:
    // Important values to send to other files
    int val;
    bool ai;

    // Layout
    QStackedLayout * mainLayout;

    // Widget
    MainMenu * mainMenu = nullptr;
    ArmySelectionMenu * armySelectionMenu = nullptr;
    BattleWindow * battleWindow = nullptr;
    EndMenu * endMenu = nullptr;

public:
    MainWidget(QWidget *parent = nullptr);
    void refreshWidgets();
    ~MainWidget();

public slots:
    // Slots used to trigger widget changes
    void moveToArmySelection(int val, bool ia);
    void moveToMap(Human* human, AI* ia);
    void moveToEndMenu(bool who);
    void replay();
    void config();
};
