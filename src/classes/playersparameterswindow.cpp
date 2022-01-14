#include "./headers/playersparameterswindow.h"

PlayersParametersWindow::PlayersParametersWindow(int pla_num, int ext_cho, QWidget* parent): QWidget(parent), extension_choice(ext_cho), players_number(pla_num){
    setWindowTitle("Splendor : Players Parameters");
    setFixedSize(600,300);

    QLabel* player_text;
    QComboBox* choice_player_type;
    QVBoxLayout* final_layout = new QVBoxLayout;
    QHBoxLayout* player_layout;
    QLineEdit* player_name;
//    QPushButton* previous_button;
    QPushButton* next_button;

    player_text = new QLabel("Player 0 is Human (by default)\t");
    player_layout = new QHBoxLayout;
    choice_player_type = new QComboBox;
    choice_player_type->addItem("Human");
    player_layout->addWidget(player_text);
    player_layout->addWidget(choice_player_type);

    layouts.push_back(player_layout);

    player_name = new QLineEdit(nullptr);
    player_name->setPlaceholderText("Player name");

    players_names.push_back(player_name);
    players_type.push_back(choice_player_type);

    player_layout->addWidget(player_name);
    final_layout->addLayout(player_layout);

    for(int i=1; i<pla_num; i++){
         player_text = new QLabel("Choose between Human and IA for Player " + QString::number(i));
         player_layout = new QHBoxLayout;
         choice_player_type = new QComboBox;
         choice_player_type->addItem("Human");
         choice_player_type->addItem("IA");
         player_layout->addWidget(player_text);
         player_layout->addWidget(choice_player_type);

         layouts.push_back(player_layout);

         player_name = new QLineEdit(nullptr);
         player_name->setPlaceholderText("Player name");

         players_names.push_back(player_name);
         players_type.push_back(choice_player_type);

         player_layout->addWidget(player_name);
         final_layout->addLayout(player_layout);
    }

    QHBoxLayout* buttons_layout = new QHBoxLayout;
//    previous_button = new QPushButton("Previous",this);
//    QObject::connect(previous_button, SIGNAL(clicked()), this, SLOT(previousWindow()));
//    buttons_layout->addWidget(previous_button);
    next_button = new QPushButton("Next",this);
    QObject::connect(next_button, SIGNAL(clicked()), this, SLOT(nextWindow()));
    buttons_layout->addWidget(next_button);
    final_layout->addLayout(buttons_layout);

    setLayout(final_layout);
}

void PlayersParametersWindow::nextWindow(){
    QString ext;
    // extension choice
    if(extension_choice == 0){ // 0 = Classic
        ext = "classic";
    }
    else if(extension_choice == 1){ // 1 = Extension Cities of Splendor
        ext = "cities of splendor";
    }

    // generate players
    std::vector<Player*> pla;
    for(size_t i=0; i<players_names.size(); i++){
        if(players_type[i]->currentIndex() == 0){ // 0 = Human
            Human temp_human(players_names[i]->text());
            pla.push_back(temp_human.FactoryMethod());
        }
        else if(players_type[i]->currentIndex() == 1){ // 1 = IA
            IA temp_IA(players_names[i]->text() + " (IA)",1);
            pla.push_back(temp_IA.FactoryMethod());
        }
    }

    MainWindow* window = new MainWindow(ext,"Game 1",pla);
    window->move(300,50);
    window->show();
    hide();
}

PlayersParametersWindow::~PlayersParametersWindow(){

}
