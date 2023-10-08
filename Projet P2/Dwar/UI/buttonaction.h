#pragma once

#include <QWidget>

class QPushButton;
class QLabel;

class ButtonAction : public QWidget
{
    Q_OBJECT
public:
    ButtonAction(QWidget *parent = nullptr);
    QPushButton* getNextTurn();
    QPushButton* getAttack();
    void setTurn(int turn, int state);
    private:
    QPushButton* nextTurn;
    QPushButton* attack;
    QLabel* labelTurn;
    QString allyTurn;
    QString ennemyTurn;
};

