#include "./headers/victorywindow.h"

VictoryWindow::VictoryWindow(std::vector<Player*> pla, QWidget* parent): QWidget(parent){
    setWindowTitle("Splendor : Victory !");
    setFixedSize(600,300);

    victory_text = new QLabel;
    QString text;

    if(pla.size() == 1){
        text += "Player " + pla[0]->getName() + " has won ! Congrats'";
    }
    else{
        text += "It's a draw ! Winners are : ";
        for(size_t i=0; i<pla.size()-1; i++){
            text += pla[i]->getName() + " - ";
        }
        text += pla[pla.size()-1]->getName() + " ! Congrats'";
    }

    victory_text->setText(text);
    QHBoxLayout* final_layout = new QHBoxLayout;
    final_layout->addWidget(victory_text);

    setLayout(final_layout);
}
