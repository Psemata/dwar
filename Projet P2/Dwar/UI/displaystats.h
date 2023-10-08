#pragma once

#include <QWidget>

class Unit;
class QLabel;

class DisplayStats : public QWidget
{
    Q_OBJECT
public:
    DisplayStats(QWidget *parent = nullptr);
    void makeLabels();
    void setValue(Unit* unit);
    void reset();
private:
    QLabel* labelNAME, *labelDMG, *labelHP, *labelMPLeft;
    QLabel* labelVNAME, *labelVDMG, *labelVHP, *labelVMPLeft;
    QLabel* sprite;
};
