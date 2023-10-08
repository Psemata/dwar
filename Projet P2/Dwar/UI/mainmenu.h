#pragma once
#include <QWidget>

class QPushButton;
class SettingsMenu;

class MainMenu : public QWidget {
    Q_OBJECT

private:
    // Buttons
    QPushButton * startButton;
    QPushButton * rulesButton;
    QPushButton * quitButton;

public:
    // Dialog used to set the configuration
    SettingsMenu * difficulty;

    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

public slots:
    // Slots used to play the game or to show the rules
    void play();
    void rules();

signals:
    // Signal used to send the settings chosen in SettingsMenu to the next menu
    void difficultyChosen(int val, bool ia);
};
