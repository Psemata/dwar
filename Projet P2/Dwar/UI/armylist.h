#pragma once

#include <QWidget>

class QLabel;
class QListWidget;

class ArmyList : public QWidget
{
    Q_OBJECT
public:
    ArmyList(QString title, QWidget *parent = nullptr);
    QListWidget* getArmyList();
    QLabel* getGolds();
    void setYourTurn(QString value);
private:
    QLabel* title;
    QLabel* yourTurn;
    QLabel* golds;
    QLabel* iconGold;
    QListWidget* armyList;
};
