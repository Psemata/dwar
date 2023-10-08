#include "endmenu.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QtWidgets>

EndMenu::EndMenu(QWidget *parent) : QWidget(parent) {
    // Main layout
    QVBoxLayout * mainlayout = new QVBoxLayout(this);
    mainlayout->addSpacing(250);
    // Text layout
    QHBoxLayout * contentlayout = new QHBoxLayout();
    mainlayout->addLayout(contentlayout);
    mainlayout->addSpacing(150);
    //Button layout
    QHBoxLayout * centerLayout = new QHBoxLayout();
    mainlayout->addLayout(centerLayout);
    QVBoxLayout * buttonLayout = new QVBoxLayout();

    // Label
    this->info = new QLabel(tr("Victoire"), this);
    QFont font;
    font.setPointSize(20);
    this->info->setFont(font);

    // Buttons
    this->replay = new QPushButton(this);
    QPixmap rejouer(":Images/rejouer.png");
    this->replay->setIcon(QIcon(rejouer));
    this->replay->setIconSize(rejouer.rect().size());
    this->replay->setFixedSize(rejouer.rect().size());
    this->config = new QPushButton(this);
    QPixmap configuration(":Images/configuration.png");
    this->config->setIcon(QIcon(configuration));
    this->config->setIconSize(configuration.rect().size());
    this->config->setFixedSize(configuration.rect().size());
    this->quit = new QPushButton(this);
    QPixmap quitter(":Images/quitter.png");
    this->quit->setIcon(QIcon(quitter));
    this->quit->setIconSize(quitter.rect().size());
    this->quit->setFixedSize(quitter.rect().size());

    //Add info to the layout
    contentlayout->addStretch(1);
    contentlayout->addWidget(this->info);
    contentlayout->addStretch(1);

    // Add the buttons to the layout
    buttonLayout->addWidget(this->replay);
    buttonLayout->addWidget(this->config);
    buttonLayout->addWidget(this->quit);
    buttonLayout->addStretch(1);

    centerLayout->addStretch(1);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addStretch(1);

    QObject::connect(replay, &QPushButton::pressed, this, &EndMenu::replaySignal);
    QObject::connect(config, &QPushButton::pressed, this, &EndMenu::configSignal);
    QObject::connect(quit, &QPushButton::pressed, QApplication::instance(), &QApplication::quit);
}

EndMenu::~EndMenu(){

}

// Set the winning text
void EndMenu::setWinText(bool who){
    if(who){
        this->info->setText(tr("L'armée du joueur remporte la bataille !"));
    } else {
        this->info->setText(tr("L'armée de l'IA remporte la bataille !"));
    }
}
