#include "displaystats.h"
#include "QLabel"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Unit/Unit.h"

DisplayStats::DisplayStats(QWidget *parent) : QWidget(parent)
{
    makeLabels();

    //Set widgets to layout
    //Mainlayout
    QVBoxLayout* vMainLayout = new QVBoxLayout(this);
    vMainLayout->addSpacing(100);

    vMainLayout->addWidget(this->sprite);
    vMainLayout->addSpacing(50);

    //Layout name unit
    QHBoxLayout* hNAMELayout = new QHBoxLayout();
    hNAMELayout->addWidget(this->labelNAME);
    hNAMELayout->addWidget(this->labelVNAME);
    vMainLayout->addLayout(hNAMELayout);

    //Layout dammage unit
    QHBoxLayout* hDMGLayout = new QHBoxLayout();
    hDMGLayout->addWidget(this->labelDMG);
    hDMGLayout->addWidget(this->labelVDMG);
    vMainLayout->addLayout(hDMGLayout);

    //Layout hp unit
    QHBoxLayout* hHPLayout = new QHBoxLayout();
    hHPLayout->addWidget(this->labelHP);
    hHPLayout->addWidget(this->labelVHP);
    vMainLayout->addLayout(hHPLayout);

    //Layout mp unit
    QHBoxLayout* hMPLayout = new QHBoxLayout();
    hMPLayout->addWidget(this->labelMPLeft);
    hMPLayout->addWidget(this->labelVMPLeft);
    vMainLayout->addLayout(hMPLayout);

    vMainLayout->addStretch(30);
    setFixedWidth(260);
    setLayout(vMainLayout);
}

//Initialisation of the labels
void DisplayStats::makeLabels()
{
    this->sprite = new QLabel("", this);
    QFont font;
    font.setPointSize(15);

    this->labelNAME = new QLabel("", this);
    this->labelNAME->setFont(font);
    this->labelVNAME = new QLabel("", this);
    this->labelVNAME->setFont(font);
    this->labelVNAME->setAlignment(Qt::AlignRight);
    this->labelHP = new QLabel("", this);
    this->labelHP->setFont(font);
    this->labelVHP = new QLabel("", this);
    this->labelVHP->setFont(font);
    this->labelVHP->setAlignment(Qt::AlignRight);
    this->labelDMG = new QLabel("", this);
    this->labelDMG->setFont(font);
    this->labelVDMG = new QLabel("", this);
    this->labelVDMG->setFont(font);
    this->labelVDMG->setAlignment(Qt::AlignRight);
    this->labelMPLeft = new QLabel("", this);
    this->labelMPLeft->setFont(font);
    this->labelVMPLeft = new QLabel("", this);
    this->labelVMPLeft->setFont(font);
    this->labelVMPLeft->setAlignment(Qt::AlignRight);
}

//Set all labels with the value of the unit and diplay the sprite
void DisplayStats::setValue(Unit *unit)
{
    QPixmap unitSprite(unit->getSprite());
    unitSprite = unitSprite.scaled(250,250);
    this->sprite->setPixmap(unitSprite);
    this->labelNAME->setText(tr("Nom : "));
    this->labelVNAME->setText(unit->getClassName());
    this->labelDMG->setText(tr("Dégats : "));
    this->labelVDMG->setText(QString::number(unit->getDamage()));
    this->labelHP->setText(tr("HP restant : "));
    this->labelVHP->setText(QString::number(unit->getHP()));
    this->labelMPLeft->setText(tr("PM restant : "));
    this->labelVMPLeft->setText(QString::number(unit->getMovements()));
}

//Set all labels with a empty value and don't display the sprite
void DisplayStats::reset()
{
    this->sprite->setPixmap(QPixmap());
    this->labelNAME->clear();
    this->labelVNAME->clear();
    this->labelDMG->clear();
    this->labelVDMG->clear();
    this->labelHP->clear();
    this->labelVHP->clear();
    this->labelMPLeft->clear();
    this->labelVMPLeft->clear();
}
