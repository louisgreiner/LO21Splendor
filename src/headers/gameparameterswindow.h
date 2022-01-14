#ifndef GAMEPARAMETERSWINDOW_H
#define GAMEPARAMETERSWINDOW_H

#include "playersparameterswindow.h"

class GameParametersWindow: public QWidget{
        Q_OBJECT
    private:
        QVBoxLayout* final_layout;
        QHBoxLayout* player_choice_layout;
        QHBoxLayout* choice;
        QSpinBox* players_number;
        QComboBox* extension_choice;
        QPushButton* next_button;
    public:
        explicit GameParametersWindow(QWidget* parent = nullptr); // DONE
    private slots:
        void nextWindow(); // DONE
};

#endif // GAMEPARAMETERSWINDOW_H
