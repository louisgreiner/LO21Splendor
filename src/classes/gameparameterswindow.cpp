#include "./headers/gameparameterswindow.h"

GameParametersWindow::GameParametersWindow(QWidget* parent): QWidget(parent){
    setWindowTitle("Splendor : Game Parameters");
    setFixedSize(600,300);
    final_layout = new QVBoxLayout;
    player_choice_layout = new QHBoxLayout;

    QLabel* player_choice_text = new QLabel("Enter a value between 2 and 4");
    players_number = new QSpinBox;
    players_number->setRange(2, 4);
    players_number->setSingleStep(1);
    players_number->setValue(2);
    player_choice_layout->addWidget(player_choice_text);
    player_choice_layout->addWidget(players_number);

    QLabel* extension_choice_text = new QLabel("Extension choice");
    extension_choice = new QComboBox;
    extension_choice->addItem("Classic");
    extension_choice->addItem("Cities of Splendor");

    choice = new QHBoxLayout;
    choice->addWidget(extension_choice_text);
    choice->addWidget(extension_choice);

    next_button = new QPushButton("Next", this);
    connect(next_button,SIGNAL(clicked()),this,SLOT(nextWindow()));

    final_layout->addLayout(player_choice_layout);
    final_layout->addLayout(choice);
    final_layout->addWidget(next_button);

    setLayout(final_layout);
}

void GameParametersWindow::nextWindow(){
    PlayersParametersWindow* next_window = new PlayersParametersWindow(players_number->value(),extension_choice->currentIndex());
    next_window->show();
    hide();
}
