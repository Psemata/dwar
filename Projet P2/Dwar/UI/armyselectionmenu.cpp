#include "armyselectionmenu.h"
#include <QPushButton>
#include <QPixmap>
#include <QListWidget>
#include "UI/clickablelabel.h"
#include "Player/player.h"
#include "Player/human.h"
#include "Player/ai.h"
#include "Unit/archer.h"
#include "Unit/saber.h"
#include "Unit/rider.h"
#include <vector>
#include <string>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UI/armylist.h"
#include <QListWidget>

const int ARCHER = 0;
const int RIDER = 1;
const int SABER = 2;
const int ALLYTURN = 0;
const int ENNEMYTURN = 1;

ArmySelectionMenu::ArmySelectionMenu(QWidget *parent) : QWidget(parent) {
    initLayout();

    this->human = new Human();
    this->ai = new AI();
    this->currentPlayer = human;

    //ArmyList initialisation
    initArmyList();

    //Midle initialisation
    initLabelUnit();
    initDescription();
    initButton();

    setLayout(layoutPrincipal);    

    connection();
}

ArmySelectionMenu::~ArmySelectionMenu() {

}

void ArmySelectionMenu::initLayout() {
    this->layoutPrincipal = new QHBoxLayout(this);
    this->layoutAllyArmy = new QVBoxLayout();
    this->layoutMiddle = new QVBoxLayout();
    this->layoutMainDescrption = new QVBoxLayout();
    this->layoutUnit = new QHBoxLayout();
    this->layoutButton = new QHBoxLayout();
    this->layoutShopButton = new QHBoxLayout();
    this->layoutEnemyLayout = new QVBoxLayout();

    this->layoutPrincipal->addLayout(this->layoutAllyArmy);
    this->layoutPrincipal->addLayout(this->layoutMiddle);
    this->layoutMiddle->addSpacing(50);
    this->layoutMiddle->addLayout(this->layoutUnit);
    this->layoutMiddle->addSpacing(100);
    this->layoutMiddle->addStretch(1);

    QHBoxLayout* secondaireDesciption = new QHBoxLayout();
    secondaireDesciption->addLayout(this->layoutMainDescrption);
    secondaireDesciption->setAlignment(Qt::AlignHCenter);
    this->layoutMiddle->addLayout(secondaireDesciption);
    this->layoutMiddle->addSpacing(100);
    this->layoutMiddle->addStretch(1);

    this->layoutMiddle->addLayout(this->layoutButton);
    this->layoutMiddle->addStretch(1);
    this->layoutMiddle->addLayout(this->layoutShopButton, Qt::AlignHCenter);
    this->layoutPrincipal->addLayout(this->layoutEnemyLayout);
}

void ArmySelectionMenu::initArmyList() {
    this->allyList = new  ArmyList(tr("Allié"), this);
    this->enemyList = new  ArmyList(tr("Ennemie"), this);
    this->enemyList->setYourTurn(" ");

    this->layoutAllyArmy->addWidget(this->allyList);
    this->layoutEnemyLayout->addWidget(this->enemyList);
}

void ArmySelectionMenu::initLabelUnit() {
    //Archer
    QPixmap bow(":/classes/Images/blue/Archer/sprite_archer_fight_blue_1.png");
    bow = bow.scaled(250,250);
    this->labelArcher = new ClickableLabel();
    this->labelArcher->setPixmap(bow);
    this->labelArcher->setStyleSheet("border: 4px solid black;");
    this->labelArcher->setMaximumHeight(265);
    this->labelArcher->setMaximumWidth(300);

    //Rider
    QPixmap rider(":/classes/Images/blue/Rider/sprite_rider_fight_blue_1.png");
    rider = rider.scaled(250,250);
    this->labelRider = new ClickableLabel();
    this->labelRider->setPixmap(rider);
    this->labelRider->setMaximumHeight(265);
    this->labelRider->setMaximumWidth(300);
    this->labelRider->setStyleSheet("border: 4px solid black;");

    //Saber
    QPixmap saber(":/classes/Images/blue/Saber/sprite_saber_fight_blue_1.png");
    saber = saber.scaled(250,250);
    this->labelSaber = new ClickableLabel();
    this->labelSaber->setPixmap(saber);
    this->labelSaber->setMaximumHeight(265);
    this->labelSaber->setMaximumWidth(300);
    this->labelSaber->setStyleSheet("border: 4px solid black;");

    this->layoutUnit->addWidget(this->labelArcher);
    this->layoutUnit->addWidget(this->labelRider);
    this->layoutUnit->addWidget(this->labelSaber);
}

void ArmySelectionMenu::initDescription() {
    QFont font;
    font.setPointSize(20);
    this->unitName = new QLabel(" ");
    this->unitName->setFont(font);
    this->unitHealth = new QLabel(" ");
    this->unitHealth->setFont(font);
    this->unitDmg = new QLabel(" ");
    this->unitDmg->setFont(font);
    this->unitMovements = new QLabel(" ");
    this->unitMovements->setFont(font);
    this->unitCost = new QLabel(" ");
    this->unitCost->setFont(font);
    this->layoutMainDescrption->addWidget(unitName);
    this->layoutMainDescrption->addWidget(unitHealth);
    this->layoutMainDescrption->addWidget(unitDmg);
    this->layoutMainDescrption->addWidget(unitMovements);
    this->layoutMainDescrption->addWidget(unitCost);
}

void ArmySelectionMenu::setDesciption(Unit* unit) {
    this->unitName->setText(tr("Nom de l'unité : ") + unit->getClassName());
    this->unitHealth->setText(tr("Points de vie : ") + QString::number(unit->getHP()));
    this->unitDmg->setText(tr("Dégats : ") + QString::number(unit->getDamage()));
    this->unitMovements->setText(tr("Points de mouvements : ") + QString::number(unit->getMovements()));
    this->unitCost->setText(tr("Prix d'achat : ") + QString::number(unit->getCost()));
}

void ArmySelectionMenu::initButton() {
    this->buttonAdd = new QPushButton(this);
    QPixmap addPixmap(":Images/addunit.png");
    QIcon addIcon(addPixmap);
    this->buttonAdd->setIcon(addIcon);
    this->buttonAdd->setIconSize(addPixmap.rect().size());
    this->buttonAdd->setFixedSize(addPixmap.rect().size());
    this->buttonAdd->setEnabled(false);

    this->buttonRemove = new QPushButton(this);
    QPixmap removePixmap(":Images/dellunit.png");
    QIcon removeIcon(removePixmap);
    this->buttonRemove->setIcon(removeIcon);
    this->buttonRemove->setIconSize(removePixmap.rect().size());
    this->buttonRemove->setFixedSize(removePixmap.rect().size());
    this->buttonRemove->setEnabled(false);

    this->buttonValidate = new QPushButton(this);
    QPixmap validatePixmap(":Images/validatearmy.png");
    QIcon validateIcon(validatePixmap);
    this->buttonValidate->setIcon(validateIcon);
    this->buttonValidate->setIconSize(validatePixmap.rect().size());
    this->buttonValidate->setFixedSize(validatePixmap.rect().size());
    this->buttonValidate->setEnabled(false);

    this->layoutButton->addWidget(this->buttonAdd);
    this->layoutButton->addWidget(this->buttonRemove);
    this->layoutButton->addWidget(this->buttonValidate);
    this->layoutButton->setMargin(width());
}

void ArmySelectionMenu::addEasy(){
    // Additions of units into the AI army
    this->ai->addUnit(new Archer("red"));
    this->ai->addUnit(new Saber("red"));
    this->ai->addUnit(new Saber("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Rider("red"));

    // Additions of the units into the list
    this->enemyList->getArmyList()->addItem("Archer");
    this->enemyList->getArmyList()->addItem("Saber");
    this->enemyList->getArmyList()->addItem("Saber");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Rider");

    // Set the gold
    this->enemyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
}

void ArmySelectionMenu::addIntermediate(){
    // Additions of units into the AI army
    this->ai->addUnit(new Archer("red"));
    this->ai->addUnit(new Archer("red"));
    this->ai->addUnit(new Archer("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Saber("red"));
    this->ai->addUnit(new Saber("red"));
    this->ai->addUnit(new Saber("red"));
    this->ai->addUnit(new Saber("red"));

    // Additions of the units into the list
    this->enemyList->getArmyList()->addItem("Archer");
    this->enemyList->getArmyList()->addItem("Archer");
    this->enemyList->getArmyList()->addItem("Archer");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Saber");
    this->enemyList->getArmyList()->addItem("Saber");
    this->enemyList->getArmyList()->addItem("Saber");
    this->enemyList->getArmyList()->addItem("Saber");

    // Set the gold
    this->enemyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
}

void ArmySelectionMenu::addDifficult(){
    // Additions of units into the AI army
    this->ai->addUnit(new Archer("red"));
    this->ai->addUnit(new Archer("red"));
    this->ai->addUnit(new Archer("red"));
    this->ai->addUnit(new Archer("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Rider("red"));
    this->ai->addUnit(new Saber("red"));
    this->ai->addUnit(new Saber("red"));
    this->ai->addUnit(new Saber("red"));
    this->ai->addUnit(new Saber("red"));
    this->ai->addUnit(new Saber("red"));

    // Additions of the units into the list
    this->enemyList->getArmyList()->addItem("Archer");
    this->enemyList->getArmyList()->addItem("Archer");
    this->enemyList->getArmyList()->addItem("Archer");
    this->enemyList->getArmyList()->addItem("Archer");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Rider");
    this->enemyList->getArmyList()->addItem("Saber");
    this->enemyList->getArmyList()->addItem("Saber");
    this->enemyList->getArmyList()->addItem("Saber");
    this->enemyList->getArmyList()->addItem("Saber");
    this->enemyList->getArmyList()->addItem("Saber");

    // Set the gold
    this->enemyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
}

void ArmySelectionMenu::setConditions(int val, bool ai){
    this->difficultyValue = val;
    this->selectionByAi = ai;

    if(selectionByAi){
        switch(val){
            case 0 :
                addEasy();
                break;
            case 1 :
                addIntermediate();
                break;
            case 2 :
                addDifficult();
                break;
        }
        this->enemyList->getGolds()->setText(QString::number(this->ai->getGold()));
        enemyList->setEnabled(false);
    }
}

void ArmySelectionMenu::connection() {
    connect(this->buttonAdd, &QPushButton::clicked,[=]() {
        this->buttonValidate->setEnabled(true);
        bool gold;
        QString color = "blue";
        if(this->currentPlayer == this->ai) {
            color = "red";
        }
        switch (this->classSelected) {
            case ARCHER:
                gold = this->currentPlayer->addUnit(new Archer(color));
                if(gold){
                    if(this->turn == ALLYTURN){
                        this->allyList->getArmyList()->addItem("Archer");
                        this->allyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
                    }else{
                        this->enemyList->getArmyList()->addItem("Archer");
                        this->enemyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
                    }
                }
                break;
            case RIDER:
                gold = this->currentPlayer->addUnit(new Rider(color));
                if(gold){
                    if(this->turn == ALLYTURN){
                        this->allyList->getArmyList()->addItem("Rider");
                        this->allyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
                    }else{
                        this->enemyList->getArmyList()->addItem("Rider");
                        this->enemyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
                    }
                }
                break;
            case SABER:
                gold = this->currentPlayer->addUnit(new Saber(color));
                if(gold){
                    if(this->turn == ALLYTURN){
                        this->allyList->getArmyList()->addItem("Saber");
                        this->allyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
                    }else{
                        this->enemyList->getArmyList()->addItem("Saber");
                        this->enemyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
                    }
                }
                break;
        }
    });

    connect(this->buttonRemove, &QPushButton::clicked,[=]() {
        this->buttonRemove->setEnabled(false);
        if(this->turn == ALLYTURN && this->allyList->getArmyList()->selectedItems().size() != 0){
            //Gets the index of the selected unit
            this->selectedIndex = allyList->getArmyList()->selectionModel()->selectedIndexes().at(0).row();
            //Removes the item
            this->allyList->getArmyList()->takeItem(this->selectedIndex);
            //Remove unit from player
            this->currentPlayer->removeUnit(this->selectedIndex);
            //Clears the selection
            this->allyList->getArmyList()->selectionModel()->clear();
            //Sets golds
            this->allyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
        }else if(this->turn == ENNEMYTURN && this->enemyList->getArmyList()->selectedItems().size() != 0){
            //Gets the index of the selected unit
            this->selectedIndex = enemyList->getArmyList()->selectionModel()->selectedIndexes().at(0).row();
            //Removes the item
            this->enemyList->getArmyList()->takeItem(this->selectedIndex);
            //Remove unit from player
            this->currentPlayer->removeUnit(this->selectedIndex);
            //Clears the selection
            this->enemyList->getArmyList()->selectionModel()->clear();
            //Sets golds
            this->enemyList->getGolds()->setText(QString::number(this->currentPlayer->getGold()));
        }
        this->selectedIndex = -1;
    });

    connect(this->buttonValidate, &QPushButton::clicked,[=]() {           
        //When first player finishes, we go on AI
        //If AI selected her own army then we do not need to chose it for her
        if (this->turn == ALLYTURN && !this->selectionByAi) {
            this->currentPlayer = ai;
            this->allyList->setYourTurn(" ");
            this->enemyList->setYourTurn(tr("C'est à toi !"));
            QPixmap bow(":/classes/Images/red/Archer/sprite_archer_fight_red_1.png");
            bow = bow.scaled(250,250);
            this->labelArcher->setPixmap(bow);
            QPixmap rider(":/classes/Images/red/Rider/sprite_rider_fight_red_1.png");
            rider = rider.scaled(250,250);
            this->labelRider->setPixmap(rider);
            QPixmap saber(":/classes/Images/red/Saber/sprite_saber_fight_red_1.png");
            saber = saber.scaled(250,250);
            this->labelSaber->setPixmap(saber);
            this->turn = ENNEMYTURN;
            this->buttonValidate->setEnabled(false);
        //When we finished to chose AI army or she already chose it then
        //we go on with the battle
        } else {
            emit armyChoosen(this->human, this->ai);
        }
    });

    connect(this->labelArcher, &ClickableLabel::clicked, [=](){
        //Archer Selected
        this->classSelected = ARCHER;
        this->labelArcher->setStyleSheet("border: 4px solid #fdd835;");
        this->labelRider->setStyleSheet("border: 4px solid black;");
        this->labelSaber->setStyleSheet("border: 4px solid black;");
        setDesciption(new Archer("red"));
        this->buttonAdd->setEnabled(true);
    });

    connect(this->labelRider, &ClickableLabel::clicked,[=]() {
        //Rider Selected
        this->classSelected = RIDER;
        this->labelArcher->setStyleSheet("border: 4px solid black;");
        this->labelRider->setStyleSheet("border: 4px solid #fdd835;");
        this->labelSaber->setStyleSheet("border: 4px solid black;");
        setDesciption(new Rider("red"));
        this->buttonAdd->setEnabled(true);
    });

    connect(this->labelSaber, &ClickableLabel::clicked,[=]() {
        //Saber Selected
        this->classSelected = SABER;
        this->labelArcher->setStyleSheet("border: 4px solid black;");
        this->labelRider->setStyleSheet("border: 4px solid black;");
        this->labelSaber->setStyleSheet("border: 4px solid #fdd835;");
        setDesciption(new Saber("red"));
        this->buttonAdd->setEnabled(true);
    });

    connect(this->allyList->getArmyList(), &QListWidget::itemClicked, [=]() {
        this->buttonRemove->setEnabled(true);
    });

    connect(this->enemyList->getArmyList(), &QListWidget::itemClicked, [=]() {
        this->buttonRemove->setEnabled(true);
    });
}
