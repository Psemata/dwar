#include "mainwidget.h"
#include "UI/armyselectionmenu.h"
#include "UI/mainmenu.h"
#include "UI/battlewindow.h"
#include "UI/endmenu.h"
#include "Player/player.h"
#include "Player/ai.h"
#include "Player/human.h"

#include <QStackedLayout>
#include <QtDebug>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    this->mainLayout =  new QStackedLayout(this);

    // Create the elements/widgets of the software
    this->mainMenu = new MainMenu(this);
    this->endMenu = new EndMenu(this);

    mainLayout->addWidget(this->mainMenu); // index 0
    refreshWidgets();
    mainLayout->addWidget(this->endMenu); // index 3

    // Connection to the elements which trigger the widget changes
    QObject::connect(this->mainMenu, &MainMenu::difficultyChosen, this, &MainWidget::moveToArmySelection);
    // Connections to the buttons of the endmenu
    QObject::connect(this->endMenu, &EndMenu::replaySignal, this, &MainWidget::replay);
    QObject::connect(this->endMenu, &EndMenu::configSignal, this, &MainWidget::config);
    setMinimumSize(1350,1080);
}

// Used to add certain widgets to the layout (for example when the user want to replay)
void MainWidget::refreshWidgets(){
    mainLayout->removeWidget(this->armySelectionMenu);
    mainLayout->removeWidget(this->battleWindow);

    // if the object exist, then we need to erase it
    if(this->armySelectionMenu != nullptr && this->battleWindow != nullptr){
        delete this->armySelectionMenu;
        delete this->battleWindow;
    }

    this->armySelectionMenu = new ArmySelectionMenu(this);
    this->battleWindow = new BattleWindow(this);

    mainLayout->insertWidget(1, this->armySelectionMenu); // index 1
    mainLayout->insertWidget(2, this->battleWindow); // index 2

    QObject::connect(this->armySelectionMenu, &ArmySelectionMenu::armyChoosen, this, &MainWidget::moveToMap);
    QObject::connect(this->battleWindow, &BattleWindow::winner, this, &MainWidget::moveToEndMenu);
}

// reset the windows and go to the main menu
void MainWidget::replay(){
    refreshWidgets();
    this->mainLayout->setCurrentIndex(0);
}

// reset the windows and go to the army selection menu
void MainWidget::config(){
    refreshWidgets();
    moveToArmySelection(this->val, this->ai);
}

// Move to army selection
void MainWidget::moveToArmySelection(int val, bool ai){
    this->val = val;
    this->ai = ai;
    this->armySelectionMenu->setConditions(val, ai);
    this->mainLayout->setCurrentIndex(1);
}

// Move to the battlewindow
void MainWidget::moveToMap(Human* human, AI* ia){
    this->battleWindow->setPlayers(human, ia);
    this->mainLayout->setCurrentIndex(2);    
}

// Move to the endmenu
void MainWidget::moveToEndMenu(bool who){
    this->endMenu->setWinText(who);
    this->mainLayout->setCurrentIndex(3);
}

MainWidget::~MainWidget() {

}
