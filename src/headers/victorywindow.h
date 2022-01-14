#ifndef VICTORYWINDOW_H
#define VICTORYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "player.h"

class VictoryWindow: public QWidget{
        Q_OBJECT
    private:
        QLabel* victory_text;
    public:
        explicit VictoryWindow(std::vector<Player*> pla, QWidget* parent = nullptr); // DONE
    private slots:
//        void closeWindow();
};

#endif // VICTORYWINDOW_H
