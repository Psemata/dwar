#include "mainmenu.h"
#include "mainwidget.h"
#include "settingsmenu.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QtDebug>
#include <QMessageBox>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    // Layout creation - to host the different parts of the main menu
    QVBoxLayout * mainlayout = new QVBoxLayout(this);

    // Layout which will contain the title image
    QHBoxLayout * header = new QHBoxLayout();
    mainlayout->addLayout(header);

    // Create the title
    QPixmap titleImg(":Images/Title.png");
    QLabel * title = new QLabel;
    title->setPixmap(titleImg);

    // Add some streches to let a space
    header->addStretch(1);
    header->addWidget(title);
    header->addStretch(1);

    // Layout which will contain the center of the menu
    QHBoxLayout * center = new QHBoxLayout();
    mainlayout->addLayout(center);

    // Layout which will contain the buttons
    QVBoxLayout * buttonslayout = new QVBoxLayout();
    center->addStretch(1);
    center->addLayout(buttonslayout);
    center->addStretch(1);

    // Buttons initialization
    this->startButton = new QPushButton(this);
    this->rulesButton = new QPushButton(this);
    this->quitButton = new QPushButton(this);

    // Play button
    QPixmap playImg(":Images/nouvellePartie.png");
    QIcon playIcon(playImg);
    this->startButton->setIcon(playIcon);
    this->startButton->setIconSize(playImg.rect().size());
    this->startButton->setFixedSize(playImg.rect().size());

    // Rules button
    QPixmap rulesImg(":Images/regle.png");
    QIcon rulesIcon(rulesImg);
    this->rulesButton->setIcon(rulesIcon);
    this->rulesButton->setIconSize(rulesImg.rect().size());
    this->rulesButton->setFixedSize(rulesImg.rect().size());

    // Quit button
    QPixmap quitImg(":Images/quitterG.png");
    QIcon quitIcon(quitImg);
    this->quitButton->setIcon(quitIcon);
    this->quitButton->setIconSize(quitImg.rect().size());
    this->quitButton->setFixedSize(quitImg.rect().size());

    // Add the buttons to the layout
    buttonslayout->addStretch(1);
    buttonslayout->addWidget(startButton);
    buttonslayout->addWidget(rulesButton);
    buttonslayout->addWidget(quitButton);
    buttonslayout->addStretch(1);

    // Connection to the slots
    // Button quit
    QObject::connect(quitButton, &QPushButton::clicked, this->parentWidget(), &MainWidget::close);
    // Button rules
    QObject::connect(rulesButton, &QPushButton::clicked, this, &MainMenu::rules);
    // Button play
    QObject::connect(startButton, &QPushButton::clicked, this, &MainMenu::play);
}

// Rules
void MainMenu::rules(){
    QMessageBox::StandardButton reply;
    QString str = "Règles \n\n";
    str+="Vous allez devoir composer votre armée, pour terrasser l'armée ennemie qui est une ";
    str+="intelligence artificielle.\n\n";
    str+="\n But du jeu :\n\n";
    str+="Il vous faut rester en vie et détruire toutes les unités de l'armée ennemie ";
    str+="pour gagner la partie.\n";
    str+="\n Niveau de difficulté :\n";
    str+="Il y a trois niveaux de difficulté, Facile, Intermédiaire et Difficile. Ce qui change c'est ";
    str+="la composition de l'armée ennemie qui est plus grande en fonction de la difficulté.\n ";
    str+="Vous pouvez aussi choisir de composez vous même l'armée de l'IA en ne cochant pas la case ";
    str+="l'IA compose son armée.\n";
    str+="\n Les unités : \n\n";
    str+="Dans le jeu on retrouve un archer, un chevalier et un épéiste.\n";
    str+="L'archer peut attaquer à longue distance.\n";
    str+="Le chevalier a beaucoup de points de vie et peut se déplacer rapidement.\n";
    str+="L'épéiste fait beaucoup de dégâts au corps à corps.\n";
    str+="Chaque unité a comme statique, points de vie, dégâts, points de mouvement et un prix.";
    str+="Vous pouvez avoir toutes les stats d'une unité en cliquant dessus.\n";
    str+="\n Le plateau de jeu :\n\n";
    str+="C'est sur un plateau de jeu en en cases de 25x25 que les armées vont combattre.\n";
    str+="La première phase de jeu vous permet de placer vos unités là où vous le souhaiter. ";
    str+="Quand vous avez fini de placer vous unités vous pouvez appuyer sur le bouton Fin du tour et le combat commence.";
    str+="Durant chaque tour de jeu, vous pouvez déplacer toutes vos unités en fonction de leurs points de mouvements. Quand vous êtes bien positionné ";
    str+="ou que vos unités non plus de points de déplacent. Vous pouvez activer le mode d'attaque. Ce mode ";
    str+="permet d'attaquer les unités ennemies avec les vôtres.\n";
    str+="Si l'armée ennemie n'a plus d'unité, vous gagnez et dans le cas inverse vous perdez.";

    reply = QMessageBox::information(this, "Règles", str, QMessageBox::Ok);
}

// Play
void MainMenu::play(){
    // Create the qdialog and set it to modal before showing it
    this->difficulty = new SettingsMenu(this);
    this->difficulty->setModal(true);
    this->difficulty->show();

    // Connect the qdialog to this menu so the mainwidget can send the data to the next thing wanted
    QObject::connect(this->difficulty, &SettingsMenu::difficultyChosen, this, &MainMenu::difficultyChosen);
}

// Destructor
MainMenu::~MainMenu() {

}
