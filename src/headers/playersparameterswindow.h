#ifndef PLAYERSPARAMETERSWINDOW_H
#define PLAYERSPARAMETERSWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include "mainwindow.h"
//#include "gameparameterswindow.h"

class PlayersParametersWindow: public QWidget{
        Q_OBJECT
    private:
        int extension_choice;
        int players_number;
        std::vector<QHBoxLayout*> layouts;
        std::vector<QLineEdit*> players_names;
        std::vector<QComboBox*> players_type;
    public:
        explicit PlayersParametersWindow(int pla_num, int ext_cho, QWidget* parent = nullptr); // DONE
        virtual ~PlayersParametersWindow(); // DONE
    private slots:
//        void previousWindow(); // to do later, would need a forward declaration to include gameparameterswindow.h
        void nextWindow(); // DONE
};


#endif // PLAYERSPARAMETERSWINDOW_H
