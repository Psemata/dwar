#include "settingsmenu.h"

#include <QHBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QtDebug>

SettingsMenu::SettingsMenu(QWidget *parent) : QDialog(parent) {
    //Main Layout
    QHBoxLayout * mLayout = new QHBoxLayout(this);
    QVBoxLayout * itemLayout = new QVBoxLayout();
    QHBoxLayout * buttonsLayout = new QHBoxLayout();

    // Set the spaces in the qdialog
    mLayout->addStretch(1);
    mLayout->addLayout(itemLayout);
    mLayout->addStretch(1);

    // Create the ComboBox
    this->difficulty = new QComboBox(this);
    this->difficulty->addItem("Facile", QVariant(0));
    this->difficulty->addItem("Intermédiaire", QVariant(1));
    this->difficulty->addItem("Difficile", QVariant(2));

    // Create the CheckBox
    this->IA = new QCheckBox("L'IA compose son armée", this);
    this->IA->setChecked(true);

    // Add the items in the layout
    itemLayout->addWidget(this->difficulty);
    itemLayout->addWidget(this->IA);

    itemLayout->addStretch(1);
    itemLayout->addLayout(buttonsLayout);

    // Create the buttons
    this->send = new QPushButton("Lancer la partie", this);
    this->cancel = new QPushButton("Quitter", this);

    buttonsLayout->addWidget(cancel);
    buttonsLayout->addWidget(send);

    // Connection of the buttons to the slots
    QObject::connect(this->send, &QPushButton::clicked, this, &SettingsMenu::sendData);
    QObject::connect(this->cancel, &QPushButton::clicked, this, &SettingsMenu::cancelData);
    QObject::connect(this->IA, &QPushButton::toggled, this->difficulty, &QComboBox::setEnabled);
}

void SettingsMenu::sendData(){
    // Get the value of the difficulty
    int val = this->difficulty->itemData(this->difficulty->currentIndex()).toInt();
    // Emit the signal to change the menu
    emit difficultyChosen(val, this->IA->isChecked());
    // Close the qdialog
    this->close();
}

void SettingsMenu::cancelData(){
    // Close the window in case the user chose to cancel his choices
    this->close();
}


// Destructor
SettingsMenu::~SettingsMenu() {

}
