QT += core
QT += xml
QT += widgets
QT += gui

TARGET = xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    classes/bank.cpp \
    classes/card.cpp \
    classes/controller.cpp \
    classes/draw.cpp \
    classes/game.cpp \
    classes/gameparameterswindow.cpp \
    classes/inventory.cpp \
    classes/mainwindow.cpp \
    classes/player.cpp \
    classes/playersparameterswindow.cpp \
    classes/resources.cpp \
    classes/victorywindow.cpp \
    classes/views.cpp \
    main.cpp

HEADERS += \
    headers/bank.h \
    headers/card.h \
    headers/classes.h \
    headers/common.h \
    headers/controller.h \
    headers/draw.h \
    headers/exception.h \
    headers/game.h \
    headers/gameparameterswindow.h \
    headers/inventory.h \
    headers/mainwindow.h \
    headers/player.h \
    headers/playersparameterswindow.h \
    headers/resources.h \
    headers/victorywindow.h \
    headers/views.h

FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    extensions/cities_of_splendor.xml \
    extensions/classic.xml
