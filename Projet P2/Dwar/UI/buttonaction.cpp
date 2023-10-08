#include "buttonaction.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

const int SPAWN = 0;
const int MOVEMENT = 1;
const int ATTACK = 2;
const int ALLYTURN = 1;

ButtonAction::ButtonAction(QWidget *parent) : QWidget(parent)
{
    //Button next turn
    this->nextTurn = new QPushButton(this);
    QPixmap sprite1(":Images/placementEnnemi.png");
    QIcon icon1(sprite1);
    this->nextTurn->setIcon(icon1);
    this->nextTurn->setIconSize(sprite1.rect().size());
    this->nextTurn->setFixedSize(sprite1.rect().size());

    //Button attack mod
    this->attack = new QPushButton(this);
    this->attack->setEnabled(false);
    QPixmap sprite2(":Images/attack.png");
    QIcon icon2(sprite2);
    this->attack->setIcon(icon2);
    this->attack->setIconSize(sprite2.rect().size());
    this->attack->setFixedSize(sprite2.rect().size());

    //Label to know whose turn it is
    this->labelTurn = new QLabel(this);
    this->labelTurn->setWordWrap(true);
    QFont font;
    font.setPointSize(15);
    this->labelTurn->setFont(font);
    this->allyTurn = tr("Déplace tes unités dans les cases bleues !");
    this->ennemyTurn = tr("Déplace les unités ennemies dans les cases rouges !");

    //Set widgets to layout
    QVBoxLayout* mainLayout = new QVBoxLayout();

    mainLayout->addWidget(attack);
    mainLayout->addWidget(labelTurn);
    mainLayout->addWidget(nextTurn);

    setFixedWidth(260);
    setLayout(mainLayout);
}

QPushButton* ButtonAction::getAttack()
{
    return attack;
}

QPushButton* ButtonAction::getNextTurn()
{
    return nextTurn;
}

//Change the turn label
void ButtonAction::setTurn(int turn, int state)
{
    if(ALLYTURN == turn)
    {
        if(MOVEMENT == state){
            this->allyTurn = tr("Clique sur tes unites et déplace les dans les cases vertes !");
        }else if(ATTACK == state){
            this->allyTurn = tr("Clique sur tes unites et attaque l'ennemi dans les cases rouges !");
        }
        if(SPAWN != state){
            QPixmap sprite4(":Images/endturn.png");
            QIcon icon1(sprite4);
            this->nextTurn->setIcon(icon1);
            this->nextTurn->setIconSize(sprite4.rect().size());
            this->nextTurn->setFixedSize(sprite4.rect().size());
        }
        labelTurn->setText(this->allyTurn);
    }else{
        if(SPAWN != state){
            this->ennemyTurn = tr("Tour de l'ennemi");
        }else{
            QPixmap sprite3(":Images/commencer.png");
            QIcon icon1(sprite3);
            this->nextTurn->setIcon(icon1);
            this->nextTurn->setIconSize(sprite3.rect().size());
            this->nextTurn->setFixedSize(sprite3.rect().size());
        }
        labelTurn->setText(this->ennemyTurn);
    }
}
