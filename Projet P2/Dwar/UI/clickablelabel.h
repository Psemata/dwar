#pragma once

#include <QLabel>
#include <QWidget>

class ClickableLabel : public QLabel {
    Q_OBJECT
public:
    ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();
signals:
   void clicked();
protected:
   void mousePressEvent(QMouseEvent* event);
};

