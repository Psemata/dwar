#include "armylist.h"
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>

ArmyList::ArmyList(QString title, QWidget *parent) : QWidget(parent)
{
    this->title = new QLabel(title+ " armée", this);
    QFont font;
    font.setPointSize(20);
    font.bold();
    this->title->setFont(font);
    //Change the title color
    if(title == "Allié"){
        //Blue for ally army
        this->title->setStyleSheet("QLabel { color : blue; }");
    }else{
        //Red for ennemy ally
        this->title->setStyleSheet("QLabel { color : red; }");
    }

    //The number of golds
    this->golds = new QLabel("10000", this);
    this->golds->setStyleSheet("QLabel { color : #fdd835; }");
    this->golds->setFont(font);

    //The image for the golds label
    QPixmap coin(":Images/coin.png");
    coin = coin.scaled(100,100);
    this->iconGold = new QLabel(this);
    this->iconGold->setPixmap(coin);

    //This is the widget where the army is display
    this->armyList = new QListWidget(this);
    this->armyList->setMaximumHeight(450);
    QFont font2;
    font2.setPointSize(15);
    this->armyList->setFont(font2);

    //Add widgets to the layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->yourTurn = new QLabel(tr("C'est à toi !"), this);
    this->yourTurn->setFont(font);

    QVBoxLayout* nameLayout = new QVBoxLayout();
    nameLayout->addWidget(this->title);
    nameLayout->addWidget(this->yourTurn);

    mainLayout->addLayout(nameLayout);
    mainLayout->addWidget(this->armyList);

    QHBoxLayout* goldLayout = new QHBoxLayout();
    goldLayout->addWidget(this->iconGold);
    goldLayout->addWidget(this->golds);
    goldLayout->addStretch(1);
    mainLayout->addLayout(goldLayout);

    setMaximumWidth(350);
    setLayout(mainLayout);
}

QLabel* ArmyList::getGolds()
{
    return golds;
}

QListWidget* ArmyList::getArmyList()
{
    return armyList;
}

//Change the text
void ArmyList::setYourTurn(QString value)
{
    this->yourTurn->setText(value);
}
