#pragma once

#include <QWidget>

class QPushButton;
class QLabel;

class EndMenu : public QWidget {
    Q_OBJECT

private:
    // Label
    QLabel * info;
    // Buttons
    QPushButton * replay;
    QPushButton * config;
    QPushButton * quit;

public:
    EndMenu(QWidget *parent = nullptr);
    ~EndMenu();

public slots:
    // Slot used to set the winning text
    void setWinText(bool who);

signals:
    // Signal used to do a replay or to go the config menu
    void replaySignal();
    void configSignal();
};
