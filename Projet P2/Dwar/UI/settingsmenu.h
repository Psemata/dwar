#pragma once
#include <QDialog>

class QComboBox;
class QCheckBox;
class QPushButton;

class SettingsMenu : public QDialog {
    Q_OBJECT

private:
    // Content
    QComboBox * difficulty;
    QCheckBox * IA;

    // Buttons
    QPushButton * send;
    QPushButton * cancel;

public:
    SettingsMenu(QWidget *parent = nullptr);
    ~SettingsMenu();

public slots:
    // Slots used to send data or to cancel data
    void sendData();
    void cancelData();

signals:
    // Signal used to send the value chosen
    void difficultyChosen(int val, bool ia);

};
