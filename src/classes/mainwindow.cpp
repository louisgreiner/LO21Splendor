#include "./headers/mainwindow.h"

MainWindow::MainWindow(QString ext, QString g_name, std::vector<Player*> pla, QWidget *parent): QWidget(parent), controller(ext,g_name,pla){
    setWindowTitle("Splendor");
    selected_tokens = Resources(0,0,0,0,0,0);
    selected_development = nullptr;
    refresh();
}

//void MainWindow::PlaDevClick(PlayerDevelopmentView* dev){ // to do later, to get developments informations

//}

//void MainWindow::PlaNobClick(PlayerNobleView* dev){ // to do later, to get nobles informations

//}

//void MainWindow::PlaCitClick(PlayerCityView* cit){ // to do later, to get cities informations

//}

void MainWindow::DevClick(DevelopmentView* dev){ // to improve later, to get developments informations
    selected_development = dev->getDevelopment().FactoryMethod();
    refresh();
}

//void MainWindow::NobClick(NobleView* nob){ // to do later, to get nobles informations

//}

//void MainWindow::CitClick(CityView* cit){ // to do later, to get cities informations

//}

//void MainWindow::DrawClick(DrawView* dra){ // to be deleted

//}

void MainWindow::BoardTokenClick(BoardTokenView* tok){
    if(tok->getResources().FactoryMethod()->getSum() > 0){ // more than 0 resource of this type left
        if(selected_tokens.getSum() == 0){ // first token picked (do not know if the player will pick 2 or 3 tokens
            if(tok->getResources().FactoryMethod()->getDiamond()){ // check what resource is going to be picked
                selected_tokens.setDiamond(selected_tokens.getDiamond() + 1);
                controller.getGameInstance()->getBank().removeResources(Resources(1,0,0,0,0,0));
            }
            if(tok->getResources().FactoryMethod()->getSapphire()){
                selected_tokens.setSapphire(selected_tokens.getSapphire() + 1);
                controller.getGameInstance()->getBank().removeResources(Resources(0,1,0,0,0,0));

            }
            if(tok->getResources().FactoryMethod()->getEmerald()){
                selected_tokens.setEmerald(selected_tokens.getEmerald() + 1);
                controller.getGameInstance()->getBank().removeResources(Resources(0,0,1,0,0,0));

            }
            if(tok->getResources().FactoryMethod()->getRuby()){
                selected_tokens.setRuby(selected_tokens.getRuby() + 1);
                controller.getGameInstance()->getBank().removeResources(Resources(0,0,0,1,0,0));
            }
            if(tok->getResources().FactoryMethod()->getOnyx()){
                selected_tokens.setOnyx(selected_tokens.getOnyx() + 1);
                controller.getGameInstance()->getBank().removeResources(Resources(0,0,0,0,1,0));
            }
        }
        else if(selected_tokens.getSum() == 1){ // already picked a token, now pick a second one (same or different)
            if((selected_tokens.getDiamond() && tok->getResources().FactoryMethod()->getDiamond())
             ||(selected_tokens.getSapphire() && tok->getResources().FactoryMethod()->getSapphire())
             ||(selected_tokens.getEmerald() && tok->getResources().FactoryMethod()->getEmerald())
             ||(selected_tokens.getRuby() && tok->getResources().FactoryMethod()->getRuby())
             ||(selected_tokens.getOnyx() && tok->getResources().FactoryMethod()->getOnyx())
                    ){ // wants to pick a second token, same resource as the first
                if(tok->getResources().FactoryMethod()->getSum() > 2){ // check if there is enough to pick 2 same tokens
                    if(tok->getResources().FactoryMethod()->getDiamond()){
                        selected_tokens.setDiamond(selected_tokens.getDiamond() + 1);
                        controller.getGameInstance()->getBank().removeResources(Resources(1,0,0,0,0,0));
                    }
                    if(tok->getResources().FactoryMethod()->getSapphire()){
                        selected_tokens.setSapphire(selected_tokens.getSapphire() + 1);
                        controller.getGameInstance()->getBank().removeResources(Resources(0,1,0,0,0,0));
                    }
                    if(tok->getResources().FactoryMethod()->getEmerald()){
                        selected_tokens.setEmerald(selected_tokens.getEmerald() + 1);
                        controller.getGameInstance()->getBank().removeResources(Resources(0,0,1,0,0,0));
                    }
                    if(tok->getResources().FactoryMethod()->getRuby()){
                        selected_tokens.setRuby(selected_tokens.getRuby() + 1);
                        controller.getGameInstance()->getBank().removeResources(Resources(0,0,0,1,0,0));
                    }
                    if(tok->getResources().FactoryMethod()->getOnyx()){
                        selected_tokens.setOnyx(selected_tokens.getOnyx() + 1);
                        controller.getGameInstance()->getBank().removeResources(Resources(0,0,0,0,1,0));
                    }
                }
                else{
                    QMessageBox message(QMessageBox::Icon::Warning, "Error", "Picking this token is impossible : less than 4 of it left (" + QString::number(tok->getResources().FactoryMethod()->getSum()) + "left)");
                    message.exec();
                }
            }
            else{ // wants to pick a second token, different as the first
                if(tok->getResources().FactoryMethod()->getDiamond()){
                    selected_tokens.setDiamond(selected_tokens.getDiamond() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(1,0,0,0,0,0));
                }
                if(tok->getResources().FactoryMethod()->getSapphire()){
                    selected_tokens.setSapphire(selected_tokens.getSapphire() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(0,1,0,0,0,0));

                }
                if(tok->getResources().FactoryMethod()->getEmerald()){
                    selected_tokens.setEmerald(selected_tokens.getEmerald() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(0,0,1,0,0,0));

                }
                if(tok->getResources().FactoryMethod()->getRuby()){
                    selected_tokens.setRuby(selected_tokens.getRuby() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(0,0,0,1,0,0));

                }
                if(tok->getResources().FactoryMethod()->getOnyx()){
                    selected_tokens.setOnyx(selected_tokens.getOnyx() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(0,0,0,0,1,0));
                }
            }
        }
        else if(selected_tokens.getSum() == 2){ // already 2 tokens picked, now pick a 3rd different or validate 2 same
            if((selected_tokens.getDiamond() && tok->getResources().FactoryMethod()->getDiamond())
             ||(selected_tokens.getSapphire() && tok->getResources().FactoryMethod()->getSapphire())
             ||(selected_tokens.getEmerald() && tok->getResources().FactoryMethod()->getEmerald())
             ||(selected_tokens.getRuby() && tok->getResources().FactoryMethod()->getRuby())
             ||(selected_tokens.getOnyx() && tok->getResources().FactoryMethod()->getOnyx())
                    ){ // check if token picked is not one of the two others already picked
                QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot pick this resource : already picked 2 different resources");
                message.exec();
            }
            else if(selected_tokens.getDiamond() == 2
                 || selected_tokens.getSapphire() == 2
                 || selected_tokens.getEmerald() == 2
                 || selected_tokens.getRuby() == 2
                 || selected_tokens.getOnyx() == 2
                    ){ // already picked 2 same tokens
                QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot pick this resource : already picked 2 same resources");
                message.exec();
            }
            else{ // pick a third token, different as the 2 others
                if(tok->getResources().FactoryMethod()->getDiamond()){
                    selected_tokens.setDiamond(selected_tokens.getDiamond() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(1,0,0,0,0,0));
                }
                if(tok->getResources().FactoryMethod()->getSapphire()){
                    selected_tokens.setSapphire(selected_tokens.getSapphire() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(0,1,0,0,0,0));

                }
                if(tok->getResources().FactoryMethod()->getEmerald()){
                    selected_tokens.setEmerald(selected_tokens.getEmerald() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(0,0,1,0,0,0));

                }
                if(tok->getResources().FactoryMethod()->getRuby()){
                    selected_tokens.setRuby(selected_tokens.getRuby() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(0,0,0,1,0,0));
                }
                if(tok->getResources().FactoryMethod()->getOnyx()){
                    selected_tokens.setOnyx(selected_tokens.getOnyx() + 1);
                    controller.getGameInstance()->getBank().removeResources(Resources(0,0,0,0,1,0));
                }
            }
        }
        else{
            QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot pick this resource : already picked 3 different resources");
            message.exec();
        }
    }
    else{ // not possible
        QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot pick this resource : no more resource of this type");
        message.exec();
    }

    refresh();
}

//void MainWindow::HandTokenClick(HandTokenView* tok){ // to do later, should be used to choose which token to withdraw if player has more than 10 tokens at the end of his turn

//}

void MainWindow::NextButtonClick(){ // to be deleted, for test purpose, used to skip a player's turn
    controller.getGameInstance()->getBank().addResources(selected_tokens);
    selected_tokens = Resources(0,0,0,0,0,0);
    selected_development = nullptr;
    controller.nextTurn();
    refresh();
}

void MainWindow::CancelButtonClick(){
    controller.getGameInstance()->getBank().addResources(selected_tokens);
    selected_tokens = Resources(0,0,0,0,0,0);
    selected_development = nullptr;
    refresh();
}

void MainWindow::PickTokensClick(){
    if(selected_tokens.getSum() < 2){
        QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot pick tokens : you need to pick two same or three different tokens first (" + QString::number(selected_tokens.getSum()) + " already selected)");
        message.exec();
    }
    else if(selected_tokens.getSum() == 2){ // check if 2 same tokens
        if(selected_tokens.getDiamond() == 2
        || selected_tokens.getSapphire() == 2
        || selected_tokens.getEmerald() == 2
        || selected_tokens.getRuby() == 2
        || selected_tokens.getOnyx() == 2){
            controller.pick2SameTokens(selected_tokens);
            nextTurn();
        }
        else{ // not possible
            QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot pick tokens : 2 tokens but not the same");
            message.exec();
        }
    }
    else if(selected_tokens.getSum() == 3){ // check if 3 different tokens
        if(selected_tokens.getDiamond() <= 1
        || selected_tokens.getSapphire() <= 1
        || selected_tokens.getEmerald() <= 1
        || selected_tokens.getRuby() <= 1
        || selected_tokens.getOnyx() <= 1){
            controller.pick3DifferentTokens(selected_tokens);
            nextTurn();
        }
        else{ // not possible
            QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot pick tokens : 3 tokens but not all different");
            message.exec();
        }
    }
    else{ // not possible, more than 3 tokens
        QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot pick tokens : more than 3 tokens");
        message.exec();
    }
}

void MainWindow::BuyDevelopmentClick(){
    if(selected_development == nullptr){
        QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot buy development : no selection yet (click on a development card)");
        message.exec();
        return;
    }
    bool in_board = false, in_hand = false;
    for(size_t i=0; i<controller.getGameInstance()->getBank().getBoardDevelopments().size() && in_board == false && in_hand == false; i++){
        for(size_t j=0; j<controller.getGameInstance()->getBank().getBoardDevelopments()[i].size() && in_board == false && in_hand == false; j++){
            if(controller.getGameInstance()->getBank().getBoardDevelopments()[i][j]->getId() == selected_development->getId()){
                in_board = true;
            }
        }
    }
    for(size_t i=0; i<controller.getCurrentPlayer()->getInventory().getReservedDevelopments().size() && in_board == false && in_hand == false; i++){
        if(controller.getCurrentPlayer()->getInventory().getReservedDevelopments()[i]->getId() == selected_development->getId()){
            in_hand = true;
        }
    }
    if(in_board){ // card in board
        if(controller.buyable(selected_development)){ // enough resources
            controller.buyBoardDevelopment(selected_development);
            controller.getGameInstance()->getBank().addResources(selected_tokens);
            nextTurn();
        }
        else{ // not enough resources
            QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot buy development : not enough resources");
            message.exec();
        }
    }
    else if(in_hand){ // card in hand
        if(controller.buyable(selected_development)){ // enough resources
            controller.buyReservedDevelopment(selected_development);
            controller.getGameInstance()->getBank().addResources(selected_tokens);
            nextTurn();
        }
        else{ // not enough resources
            QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot buy development : not enough resources");
            message.exec();
        }
    }
    else{ // not possible
        QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot buy development : card does not belong to the board or your hand");
        message.exec();
    }
}

void MainWindow::ReserveDevelopmentClick(){
    if(selected_development == nullptr){
        QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot reserve development : no selection yet (click on a development card)");
        message.exec();
        return;
    }
    bool in_board = false;
    if(controller.getCurrentPlayer()->getInventory().getReservedDevelopments().size() > 2){ // no more than 3 reserved dev
        QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot reserve development : already 3 reserved development in hand");
        message.exec();
    }
    else{
        for(size_t i=0; i<controller.getGameInstance()->getBank().getBoardDevelopments().size() && in_board == false; i++){
            for(size_t j=0; j<controller.getGameInstance()->getBank().getBoardDevelopments()[i].size() && in_board == false; j++){
                if(controller.getGameInstance()->getBank().getBoardDevelopments()[i][j]->getId() == selected_development->getId()){
                    in_board = true;
                }
            }
        }
        if(in_board){ // card in board
            controller.reserveDevelopment(selected_development);
            controller.getGameInstance()->getBank().addResources(selected_tokens);
            nextTurn();
        }
        else{ // not possible
            QMessageBox message(QMessageBox::Icon::Warning, "Error", "Cannot reserve development : card does not belong to the board");
            message.exec();
        }
    }
}

void MainWindow::refresh(){
    qDeleteAll(this->children());

    final_layout = new QHBoxLayout;
    board = new QHBoxLayout;
    inside_board = new QVBoxLayout;

    // set current player
    cur_player = new QLabel;
    cur_player->setText("Player " + controller.getCurrentPlayer()->getName() + "'s turn ! --- Selected tokens : ("
                        + "d=" + QString::number(selected_tokens.getDiamond()) + ","
                        + "s=" + QString::number(selected_tokens.getSapphire()) + ","
                        + "e=" + QString::number(selected_tokens.getEmerald()) + ","
                        + "r=" + QString::number(selected_tokens.getRuby()) + ","
                        + "o=" + QString::number(selected_tokens.getOnyx()) + ","
                        + "g=" + QString::number(selected_tokens.getGold()) + ")"
                        + " --- Selected development : " + (selected_development != nullptr ? "ID=" + QString::number(selected_development->getId()) : "No selection")
                        + (controller.getGameInstance()->getLastTurn() ? " !! LAST TURN !!" : "")
                        );
    inside_board->addWidget(cur_player);

    // Players
    players = new QVBoxLayout;
    for(size_t i=0; i<controller.getGameInstance()->getPlayers().size(); i++){
        PlayerView* temp_pla = new PlayerView();
        players->addWidget(temp_pla);
//        connect(temp_pla, SIGNAL(ClickedPlayer(PlayerView*)), this, SLOT(PlaClick(PlayerView*)));
        temp_pla->setNewPlayer(*controller.getGameInstance()->getPlayers()[i],controller.getGameInstance()->getExtension());
    }
    board->addLayout(players);

    if(controller.getGameInstance()->getExtension() == "classic"){
        // Nobles board
        nobles_board.clear();
        nobles_board.push_back(new QHBoxLayout);
        for(size_t i=0; i<controller.getGameInstance()->getBank().getBoardNobles().size(); i++){
            NobleView* temp_nob = new NobleView;
            nobles_board[0]->addWidget(temp_nob);
    //        connect(temp_nob, SIGNAL(ClickedNoble(NobleView*)), this, SLOT(NobClick(NobleView*)));
            temp_nob->setNewNoble(*controller.getGameInstance()->getBank().getBoardNobles()[i]);
        }
        inside_board->addLayout(nobles_board[0]);
    }
    else if(controller.getGameInstance()->getExtension() == "cities of splendor"){
        // Cities board
        cities_board.clear();
        cities_board.push_back(new QHBoxLayout);
        for(size_t i=0; i<controller.getGameInstance()->getBank().getBoardCities().size(); i++){
            CityView* temp_cit = new CityView;
            cities_board[0]->addWidget(temp_cit);
//            connect(temp_cit, SIGNAL(ClickedCity(CityView*)), this, SLOT(NobClick(CityView*)));
            temp_cit->setNewCity(*controller.getGameInstance()->getBank().getBoardCities()[i]);
        }
        inside_board->addLayout(cities_board[0]);
    }

    // Developments board and developments draws
    developments_cards = new QVBoxLayout;
    dev_tokens_board = new QHBoxLayout;
    developments_board.clear();
    for(size_t i=0; i<controller.getGameInstance()->getBank().getBoardDevelopments().size(); i++){
        developments_board.push_back(new QHBoxLayout);
    }
    // we assume that there is only 1 draw per level of development card
    for(int i=controller.getGameInstance()->getBank().getBoardDevelopments().size()-1; i>=0; i--){
        DrawView* temp_draw = new DrawView;
        developments_board[i]->addWidget(temp_draw);
        temp_draw->setNewDevelopmentsDraw(*controller.getGameInstance()->getBank().getDrawDevelopments()[i]);
        for(size_t j=0; j<controller.getGameInstance()->getBank().getBoardDevelopments()[i].size(); j++){
            DevelopmentView* temp_dev = new DevelopmentView;
            developments_board[i]->addWidget(temp_dev);
            connect(temp_dev, SIGNAL(ClickedDevelopment(DevelopmentView*)), this, SLOT(DevClick(DevelopmentView*)));
            temp_dev->setNewDevelopment(*controller.getGameInstance()->getBank().getBoardDevelopments()[i][j]);
        }
        developments_cards->addLayout(developments_board[i]);
    }
    dev_tokens_board->addLayout(developments_cards);

    // Tokens board
    tokens_board = new QVBoxLayout();
    for(size_t i=0; i<6; i++){
        BoardTokenView* temp_tok = new BoardTokenView;
        tokens_board->addWidget(temp_tok);
        if(i!=5) connect(temp_tok, SIGNAL(ClickedBoardToken(BoardTokenView*)), this, SLOT(BoardTokenClick(BoardTokenView*)));
        temp_tok->setNewResources(controller.getGameInstance()->getBank().getResources(),i);
    }
    dev_tokens_board->addLayout(tokens_board);

    inside_board->addLayout(dev_tokens_board);

    // Current player's hand
    hand = new QVBoxLayout;

    // set resources and advantage resource tokens
    resource_hand = new QHBoxLayout;
    for(size_t i=0; i<5; i++){
        HandTokenView* temp_tok = new HandTokenView;
        resource_hand->addWidget(temp_tok);
//        connect(temp_tok, SIGNAL(ClickedHandToken(HandTokenView*)), this, SLOT(HandTokenClick(HandTokenView*)));
        temp_tok->setNewResources(controller.getCurrentPlayer()->getInventory().getResources(),controller.getCurrentPlayer()->getInventory().getResourceAdvantages(),i);
    }
    HandTokenView* temp_tok = new HandTokenView;
    resource_hand->addWidget(temp_tok);
//    connect(temp_tok, SIGNAL(ClickedHandToken(HandTokenView*)), this, SLOT(HandTokenClick(HandTokenView*)));
    temp_tok->setNewResources(controller.getCurrentPlayer()->getInventory().getResources(),controller.getCurrentPlayer()->getInventory().getResourceAdvantages(),5);
    hand->addLayout(resource_hand);

    // set reserved developments
    cards_hand = new QHBoxLayout;
    reserved_development = new QHBoxLayout;
    for(size_t i=0; i<3; i++){
        DevelopmentView* temp_dev = new DevelopmentView;
        reserved_development->addWidget(temp_dev);
        if(i < controller.getCurrentPlayer()->getInventory().getReservedDevelopments().size()){
            connect(temp_dev, SIGNAL(ClickedDevelopment(DevelopmentView*)), this, SLOT(DevClick(DevelopmentView*)));
            temp_dev->setNewDevelopment(*controller.getCurrentPlayer()->getInventory().getReservedDevelopments()[i]);
        }
        else{
            temp_dev->setNoDevelopment();
        }
    }
    cards_hand->addLayout(reserved_development);

    if(controller.getGameInstance()->getExtension() == "classic"){
        // set owned nobles
        owned_nobles = new QHBoxLayout;
        for(size_t i=0; i<controller.getCurrentPlayer()->getInventory().getOwnedNobles().size(); i++){
            NobleView* temp_nob = new NobleView;
            owned_nobles->addWidget(temp_nob);
    //        connect(temp_nob, SIGNAL(ClickedNoble(NobleView*)), this, SLOT(NobClick(NobleView*)));
            temp_nob->setNewNoble(*controller.getCurrentPlayer()->getInventory().getOwnedNobles()[i]);
        }
        if(controller.getCurrentPlayer()->getInventory().getOwnedNobles().size() == 0){
            NobleView* temp_nob = new NobleView;
            owned_nobles->addWidget(temp_nob);
    //        connect(temp_nob, SIGNAL(ClickedNoble(NobleView*)), this, SLOT(NobClick(NobleView*)));
            temp_nob->setNoNoble();
        }
        cards_hand->addLayout(owned_nobles);
    }
    else if(controller.getGameInstance()->getExtension() == "cities of splendor"){
        // set owned cities
        // no need to display anything ?! -> cool
    }
    hand->addLayout(cards_hand);

    inside_board->addLayout(hand);

    board->addLayout(inside_board);

    final_layout->addLayout(board);

    // set buttons
    buttons = new QVBoxLayout;

    cancel_button = new QPushButton;
    cancel_button->setText("Cancel action");
    if(selected_tokens.getSum() != 0 || selected_development != nullptr){ // or pop up message error : no action yet started
        connect(cancel_button,SIGNAL(clicked()),this,SLOT(CancelButtonClick()));
    }
    else{
        disconnect(cancel_button,SIGNAL(clicked()),this,SLOT(CancelButtonClick()));
    }
    buttons->addWidget(cancel_button);

    pick_tokens_button = new QPushButton;
    connect(pick_tokens_button,SIGNAL(clicked()), this, SLOT(PickTokensClick()));
    pick_tokens_button->setText("Pick selected tokens");
    buttons->addWidget(pick_tokens_button);

    buy_development_button = new QPushButton;
    connect(buy_development_button,SIGNAL(clicked()), this, SLOT(BuyDevelopmentClick()));
    buy_development_button->setText("Buy selected development");
    buttons->addWidget(buy_development_button);

    reserve_development_button = new QPushButton;
    connect(reserve_development_button,SIGNAL(clicked()), this, SLOT(ReserveDevelopmentClick()));
    reserve_development_button->setText("Reserve selected development");
    buttons->addWidget(reserve_development_button);

    final_layout->addLayout(buttons);

    setLayout(final_layout);

    update();
}

void MainWindow::checkTokensNumber(){
    if(controller.verifyTokensNumber()){
        QMessageBox message(QMessageBox::Icon::Warning, "Warning", "More than 10 tokens (" +
                            QString::number(controller.getCurrentPlayer()->getInventory().getResources().getSum()+controller.getCurrentPlayer()->getInventory().getResources().getGold()) +
                            " in hand) : " +
                            QString::number(controller.getCurrentPlayer()->getInventory().getResources().getSum()+controller.getCurrentPlayer()->getInventory().getResources().getGold() - 10) +
                            " will be deleted randomly (sorry)"
                            );
        message.exec();
    controller.withdrawTokens();
    }
}

void MainWindow::nextTurn(){
    selected_tokens = Resources(0,0,0,0,0,0);
    selected_development = nullptr;
    checkTokensNumber(); // need to be modified for further versions
    controller.nextTurn(); // checks for noble visit / cities as well
    refresh();
}
