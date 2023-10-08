QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Map/cell.cpp \
    Map/map.cpp \
    Player/ai.cpp \
    Player/human.cpp \
    Player/player.cpp \
    UI/armylist.cpp \
    UI/armyselectionmenu.cpp \
    UI/battlewindow.cpp \
    UI/buttonaction.cpp \
    UI/clickablelabel.cpp \
    UI/displaystats.cpp \
    UI/endmenu.cpp \
    UI/mainmenu.cpp \
    UI/settingsmenu.cpp \
    Unit/archer.cpp \
    Unit/rider.cpp \
    Unit/saber.cpp \
    Unit/unit.cpp \
    main.cpp \
    mainwidget.cpp

HEADERS += \
    Map/cell.h \
    Map/map.h \
    Player/ai.h \
    Player/human.h \
    Player/player.h \
	UI/armylist.h \
    UI/armyselectionmenu.h \
    UI/battlewindow.h \
	UI/buttonaction.h \
    UI/clickablelabel.h \
    UI/displaystats.h \
    UI/endmenu.h \
    UI/mainmenu.h \
    UI/settingsmenu.h \
    Unit/archer.h \
    Unit/rider.h \
    Unit/saber.h \
    Unit/unit.h \
    mainwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=
