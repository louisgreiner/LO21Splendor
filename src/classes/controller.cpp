#include "./headers/controller.h"

Controller::Controller(QString ext, QString g_name, std::vector<Player*> pla){
    current_player = nullptr;
    game_instance = Game::getInstance(ext,g_name,pla);
    current_player = game_instance->getPlayers()[0];

    // for test purpose only
    current_player->getInventory().addResourceAdvantages(Resources(4,4,4,4,4,0));
    current_player->setPrestige(14);
}

void Controller::displayBoard(){
    std::cout << "***** BOARD >>>>>\n";
    game_instance->getBank().getBoardInformations();
    std::cout << "<<<<< BOARD *****\n";
}

Player* Controller::getCurrentPlayer(){
    return current_player;
}

Game* Controller::getGameInstance(){
    return game_instance;
}

void Controller::pick3DifferentTokens(Resources res){
    if(res.getGold() != 0){
        throw Exception("Error : tried to pick gold token (pick3DifferentTokens)");
    }

    if(res.getSum() != 3){
        throw Exception("Error : tried to pick more than 3 different tokens (pick3DifferentTokens)");
    }

    if(res.getDiamond() > 1 || res.getSapphire() > 1 || res.getEmerald() > 1 || res.getRuby() > 1 || res.getOnyx() > 1){
        throw Exception("Error : tried to pick several tokens of each (pick3DifferentTokens)");
    }

    if(res.getDiamond() && game_instance->getBank().getResources().getDiamond() == -1){
        throw Exception("Error : no more diamond token in bank (pick3DifferentTokens)");
    }

    if(res.getSapphire() && game_instance->getBank().getResources().getSapphire() == -1){
        throw Exception("Error : no more sapphire token in bank (pick3DifferentTokens)");
    }

    if(res.getEmerald() && game_instance->getBank().getResources().getEmerald() == -1){
        throw Exception("Error : no more emerald token in bank (pick3DifferentTokens)");
    }

    if(res.getRuby() && game_instance->getBank().getResources().getRuby() == -1){
        throw Exception("Error : no more ruby token in bank (pick3DifferentTokens)");
    }

    if(res.getOnyx() && game_instance->getBank().getResources().getOnyx() == -1){
        throw Exception("Error : no more onyx token in bank (pick3DifferentTokens)");
    }

    current_player->getInventory().addResources(res);
//    game_instance->getBank().removeResources(res);
}

void Controller::pick2SameTokens(Resources res){
    if(res.getGold() != 0){
        throw Exception("Error : tried to pick gold token (pick2SameTokens)");
    }

    if(res.getSum() != 2){
        throw Exception("Error : tried to pick more than 2 same tokens (pick2SameTokens)");
    }

    // can only pick 2 same tokens if diamond >= 4 (condition is 2 because 4 - 2already picked = 2)
    if(res.getDiamond() && game_instance->getBank().getResources().getDiamond() < 2){
        throw Exception("Error : less than 4 diamond tokens remaining (pick2SameTokens)");
    }

    if(res.getSapphire() && game_instance->getBank().getResources().getSapphire() < 2){
        throw Exception("Error : less than 4 sapphire tokens remaining (pick2SameTokens)");
    }

    if(res.getEmerald() && game_instance->getBank().getResources().getEmerald() < 2){
        throw Exception("Error : less than 4 emerald tokens remaining (pick2SameTokens)");
    }

    if(res.getRuby() && game_instance->getBank().getResources().getRuby() < 2){
        throw Exception("Error : less than 4 ruby tokens remaining (pick2SameTokens)");
    }

    if(res.getOnyx() && game_instance->getBank().getResources().getOnyx() < 2){
        throw Exception("Error : less than 4 onyx tokens remaining (pick2SameTokens)");
    }

    current_player->getInventory().addResources(res);
//    game_instance->getBank().removeResources(res);
}

void Controller::reserveDevelopment(Development *dev){
    if(current_player->getInventory().getReservedDevelopments().size() >= 3){
        throw Exception("Error : reserved development's hand is full (reserveDevelopment)");
    }
    bool valid_card = 0;
    int location = 0;
    for(size_t i=0; i<game_instance->getBank().getBoardDevelopments()[dev->getLevel()-1].size(); i++){
        if(game_instance->getBank().getBoardDevelopments()[dev->getLevel()-1][i]->getId() == dev->getId()){
            valid_card = 1;
            location = i;
        }
    }
    if(valid_card == 0){
        throw Exception("Error : no valid card (reserveDevelopment)");
    }

    // give gold if there is any left in bank
    if(game_instance->getBank().getResources().getGold() > 0){
        current_player->getInventory().addResources(Resources(0,0,0,0,0,1));
        game_instance->getBank().removeResources(Resources(0,0,0,0,0,1));
    }

    // change card's owner (bank -> player)
    game_instance->getBank().getBoardDevelopments()[dev->getLevel()-1][location]->changeOwner(*current_player);
    // add card to player's inventory
    current_player->getInventory().addReservedDevelopment(dev);

    // delete card from board and re-filling
    game_instance->getBank().removeBoardDevelopment(dev->getLevel()-1,location);

    // re-fill the board
    game_instance->getBank().insertBoardDevelopment(game_instance->getBank().drawDevelopment(dev->getLevel()),dev->getLevel()-1,location);
}

void Controller::buyReservedDevelopment(Development* dev){
    bool valid_card = 0;
    for(size_t i=0; i<current_player->getInventory().getReservedDevelopments().size(); i++){
        if(current_player->getInventory().getReservedDevelopments()[i]->getId() == dev->getId()){
            valid_card = 1;
        }
    }
    if(valid_card == 0){
        throw Exception("Error : no valid card (buyReservedDevelopment)");
    }

    // copy cost to check buyability
    // priority = advantages > resources > gold
    Resources res_left = dev->getCost();
    // deduct resources advantages
    res_left.setDiamond(res_left.getDiamond() - current_player->getInventory().getResourceAdvantages().getDiamond());
    res_left.setSapphire(res_left.getSapphire() - current_player->getInventory().getResourceAdvantages().getSapphire());
    res_left.setEmerald(res_left.getEmerald() - current_player->getInventory().getResourceAdvantages().getEmerald());
    res_left.setRuby(res_left.getRuby() - current_player->getInventory().getResourceAdvantages().getRuby());
    res_left.setOnyx(res_left.getOnyx() - current_player->getInventory().getResourceAdvantages().getOnyx());

    // deduct resources
    int dia = 0, sap = 0, eme = 0, rub = 0, ony = 0;
    for(int i=0; i<current_player->getInventory().getResources().getDiamond() && res_left.getDiamond()>0 ; i++){
        res_left.setDiamond(res_left.getDiamond() - 1);
        dia++;
    }
    for(int i=0; i<current_player->getInventory().getResources().getSapphire() && res_left.getSapphire()>0 ; i++){
        res_left.setSapphire(res_left.getSapphire() - 1);
        sap++;
    }
    for(int i=0; i<current_player->getInventory().getResources().getEmerald() && res_left.getEmerald()>0 ; i++){
        res_left.setEmerald(res_left.getEmerald() - 1);
        eme++;
    }
    for(int i=0; i<current_player->getInventory().getResources().getRuby() && res_left.getRuby()>0 ; i++){
        res_left.setRuby(res_left.getRuby() - 1);
        rub++;
    }
    for(int i=0; i<current_player->getInventory().getResources().getOnyx() && res_left.getOnyx()>0 ; i++){
        res_left.setOnyx(res_left.getOnyx() - 1);
        ony++;
    }

    // deduct gold
    int left = res_left.getSum(), gol = 0;
    if(left > current_player->getInventory().getResources().getGold()){
        throw Exception("Error : no enough gold (buyReservedDevelopment)");
    }
    for(int i=0; i<current_player->getInventory().getResources().getGold() && left>0; i++){
        left--;
        gol++;
    }

    // remove player's resources
    current_player->getInventory().removeResources(Resources(dia,sap,eme,rub,ony,gol));
    // add resources advantages
    current_player->getInventory().addResourceAdvantages(Resources(dev->getAdvantages().getDiamond(),dev->getAdvantages().getSapphire(),dev->getAdvantages().getEmerald(),dev->getAdvantages().getRuby(),dev->getAdvantages().getOnyx(),0));
    // return resources to bank
    game_instance->getBank().addResources(Resources(dia,sap,eme,rub,ony,gol));
    // add development to owned development
    current_player->getInventory().addOwnedDevelopment(dev);
    // add prestige
    current_player->setPrestige(current_player->getPrestige()+dev->getPrestige());
    // remove development from reserved development
    current_player->getInventory().removeReservedDevelopment(dev);
}

void Controller::buyBoardDevelopment(Development* dev){
    bool valid_card = 0;
    int location = 0;
    for(size_t i=0; i<game_instance->getBank().getBoardDevelopments()[dev->getLevel()-1].size(); i++){
        if(game_instance->getBank().getBoardDevelopments()[dev->getLevel()-1][i]->getId() == dev->getId()){
            valid_card = 1;
            location = i;
        }
    }
    if(valid_card == 0){
        throw Exception("Error : no valid card (buyBoardDevelopment)");
    }

    // copy cost to check buyability
    // priority = advantages > resources > gold
    Resources res_left = dev->getCost();
    // deduct resources advantages
    res_left.setDiamond(res_left.getDiamond() - current_player->getInventory().getResourceAdvantages().getDiamond());
    res_left.setSapphire(res_left.getSapphire() - current_player->getInventory().getResourceAdvantages().getSapphire());
    res_left.setEmerald(res_left.getEmerald() - current_player->getInventory().getResourceAdvantages().getEmerald());
    res_left.setRuby(res_left.getRuby() - current_player->getInventory().getResourceAdvantages().getRuby());
    res_left.setOnyx(res_left.getOnyx() - current_player->getInventory().getResourceAdvantages().getOnyx());

    // deduct resources
    int dia = 0, sap = 0, eme = 0, rub = 0, ony = 0;
    for(int i=0; i<current_player->getInventory().getResources().getDiamond() && res_left.getDiamond()>0 ; i++){
        res_left.setDiamond(res_left.getDiamond() - 1);
        dia++;
    }
    for(int i=0; i<current_player->getInventory().getResources().getSapphire() && res_left.getSapphire()>0 ; i++){
        res_left.setSapphire(res_left.getSapphire() - 1);
        sap++;
    }
    for(int i=0; i<current_player->getInventory().getResources().getEmerald() && res_left.getEmerald()>0 ; i++){
        res_left.setEmerald(res_left.getEmerald() - 1);
        eme++;
    }
    for(int i=0; i<current_player->getInventory().getResources().getRuby() && res_left.getRuby()>0 ; i++){
        res_left.setRuby(res_left.getRuby() - 1);
        rub++;
    }
    for(int i=0; i<current_player->getInventory().getResources().getOnyx() && res_left.getOnyx()>0 ; i++){
        res_left.setOnyx(res_left.getOnyx() - 1);
        ony++;
    }

    // deduct gold
    int left = res_left.getSum(), gol = 0;
    if(left > current_player->getInventory().getResources().getGold()){
        throw Exception("Error : no enough gold (buyReservedDevelopment)");
    }
    for(int i=0; i<current_player->getInventory().getResources().getGold() && left>0; i++){
        left--;
        gol++;
    }

    // remove player's resources
    current_player->getInventory().removeResources(Resources(dia,sap,eme,rub,ony,gol));
    // add resources advantages
    current_player->getInventory().addResourceAdvantages(Resources(dev->getAdvantages().getDiamond(),dev->getAdvantages().getSapphire(),dev->getAdvantages().getEmerald(),dev->getAdvantages().getRuby(),dev->getAdvantages().getOnyx(),0));
    // return resources to bank
    game_instance->getBank().addResources(Resources(dia,sap,eme,rub,ony,gol));
    // change card's owner (bank -> player)
    game_instance->getBank().getBoardDevelopments()[dev->getLevel()-1][location]->changeOwner(*current_player);
    // add card to player's inventory
    current_player->getInventory().addOwnedDevelopment(dev);
    // add prestige
    current_player->setPrestige(current_player->getPrestige()+dev->getPrestige());
    // delete development from board
    game_instance->getBank().removeBoardDevelopment(dev->getLevel()-1,location);
    // re-fill the board
    game_instance->getBank().insertBoardDevelopment(game_instance->getBank().drawDevelopment(dev->getLevel()),dev->getLevel()-1,location);
}

void Controller::generateIAActions(){
    // check if any card is buyable, if yes -> buy it
    int dev_board_lev=-1,dev_board_pos=-1;
    for(size_t i=0; i<game_instance->getBank().getBoardDevelopments().size(); i++){
        for(size_t j=0; j<game_instance->getBank().getBoardDevelopments()[i].size(); j++){
            if(buyable(game_instance->getBank().getBoardDevelopments()[i][j])){
                if(dev_board_lev != -1 && dev_board_pos != -1){
                    if(game_instance->getBank().getBoardDevelopments()[i][j]->getPrestige() > game_instance->getBank().getBoardDevelopments()[dev_board_lev][dev_board_pos]->getPrestige()){
                        dev_board_lev = i;
                        dev_board_pos = j;
                    }
                }
                else{
                    dev_board_lev = i;
                    dev_board_pos = j;
                }
            }
        }
    }
    int dev_hand_pos=-1;
    for(size_t i=0; i<current_player->getInventory().getReservedDevelopments().size(); i++){
        if(buyable(current_player->getInventory().getReservedDevelopments()[i])){
            if(dev_hand_pos != -1){
                if(current_player->getInventory().getReservedDevelopments()[i]->getPrestige() > current_player->getInventory().getReservedDevelopments()[dev_hand_pos]->getPrestige()){
                    dev_hand_pos = i;
                }
            }
            else{
                dev_hand_pos = i;
            }
        }
    }
    if((dev_board_lev != -1 && dev_board_pos != -1) || dev_hand_pos != -1){
        if(dev_hand_pos == -1){
            buyBoardDevelopment(game_instance->getBank().getBoardDevelopments()[dev_board_lev][dev_board_pos]);
        }
        else if(dev_board_lev == -1 && dev_board_pos == -1){
            buyReservedDevelopment(current_player->getInventory().getReservedDevelopments()[dev_hand_pos]);
        }
        else{ // need to compare, find max prestige of 2 cards, priority given to reserved developments in case of draw
            if(game_instance->getBank().getBoardDevelopments()[dev_board_lev][dev_board_pos]->getPrestige() > current_player->getInventory().getReservedDevelopments()[dev_hand_pos]->getPrestige()){
                buyBoardDevelopment(game_instance->getBank().getBoardDevelopments()[dev_board_lev][dev_board_pos]);
            }
            else{
                buyReservedDevelopment(current_player->getInventory().getReservedDevelopments()[dev_hand_pos]);
            }
        }
        return;
    }

    // if 0 development reserved -> reserve a random level 2 development
    if(current_player->getInventory().getReservedDevelopments().size() == 0){
        srand(time(NULL));
        int random = rand() % game_instance->getBank().getBoardDevelopments()[1].size();
        reserveDevelopment(game_instance->getBank().getBoardDevelopments()[1][random]);
        return;
    }

    // if 1 development reserved -> reserve a random level random development
    if(current_player->getInventory().getReservedDevelopments().size() == 1){
        srand(time(NULL));
        int random_lev = rand() % game_instance->getBank().getBoardDevelopments().size();
        int random_pos = rand() % game_instance->getBank().getBoardDevelopments()[random_lev].size();
        reserveDevelopment(game_instance->getBank().getBoardDevelopments()[random_lev][random_pos]);
        return;
    }

    // if 2 developments reserved ->
        // if sum of its own resources < 5 -> pick 3 resources, based on the predominant resources of its 2 reserved developments
    if(current_player->getInventory().getReservedDevelopments().size() == 2){
//        if(current_player->getInventory().getResources().getSum() < 5){ // not sure about < 5
            if(true){ // if possible to pick 3 different tokens
                int predominant_resources[3] = {-1,-1,-1}, sum_resources[5];
                sum_resources[0] = current_player->getInventory().getReservedDevelopments()[0]->getCost().getDiamond() + current_player->getInventory().getReservedDevelopments()[1]->getCost().getDiamond() - current_player->getInventory().getResources().getDiamond();
                sum_resources[1] = current_player->getInventory().getReservedDevelopments()[0]->getCost().getSapphire() + current_player->getInventory().getReservedDevelopments()[1]->getCost().getSapphire() - current_player->getInventory().getResources().getSapphire();
                sum_resources[2] = current_player->getInventory().getReservedDevelopments()[0]->getCost().getEmerald() + current_player->getInventory().getReservedDevelopments()[1]->getCost().getEmerald() - current_player->getInventory().getResources().getEmerald();
                sum_resources[3] = current_player->getInventory().getReservedDevelopments()[0]->getCost().getRuby() + current_player->getInventory().getReservedDevelopments()[1]->getCost().getRuby() - current_player->getInventory().getResources().getRuby();
                sum_resources[4] = current_player->getInventory().getReservedDevelopments()[0]->getCost().getOnyx() + current_player->getInventory().getReservedDevelopments()[1]->getCost().getOnyx() - current_player->getInventory().getResources().getOnyx();
                for(size_t i=0; i<3; i++){
                    for(int j=0; j<5; j++){
                        if(predominant_resources[0] != j && predominant_resources[1] != j && predominant_resources[i] < sum_resources[j]){
                            predominant_resources[i] = j;
                        }
                    }
                    if(predominant_resources[i] == 0 && game_instance->getBank().getResources().getDiamond() < 1) { // wants diamond but 0 left (*gets very angry* fuck it) -> choose random resource
                        srand(time(NULL));
                        int random = rand() % 5;
                        while(random == predominant_resources[i]){
                            random = (random + 1) % 5 ;
                        }
                        predominant_resources[i] = random;
                    }
                    if(predominant_resources[i] == 0 && game_instance->getBank().getResources().getSapphire() < 1) { // wants diamond but 0 left (*gets very angry* fuck it) -> choose random resource
                        srand(time(NULL));
                        int random = rand() % 5;
                        while(random == predominant_resources[i]){
                            random = (random + 1) % 5 ;
                        }
                        predominant_resources[i] = random;
                    }
                    if(predominant_resources[i] == 0 && game_instance->getBank().getResources().getEmerald() < 1) { // wants diamond but 0 left (*gets very angry* fuck it) -> choose random resource
                        srand(time(NULL));
                        int random = rand() % 5;
                        while(random == predominant_resources[i]){
                            random = (random + 1) % 5 ;
                        }
                        predominant_resources[i] = random;
                    }
                    if(predominant_resources[i] == 0 && game_instance->getBank().getResources().getRuby() < 1) { // wants diamond but 0 left (*gets very angry* fuck it) -> choose random resource
                        srand(time(NULL));
                        int random = rand() % 5;
                        while(random == predominant_resources[i]){
                            random = (random + 1) % 5 ;
                        }
                        predominant_resources[i] = random;
                    }
                    if(predominant_resources[i] == 0 && game_instance->getBank().getResources().getOnyx() < 1) { // wants diamond but 0 left (*gets very angry* fuck it) -> choose random resource
                        srand(time(NULL));
                        int random = rand() % 5;
                        while(random == predominant_resources[i]){
                            random = (random + 1) % 5 ;
                        }
                        predominant_resources[i] = random;
                    }
                }
                Resources res(0,0,0,0,0,0);
                for(size_t i=0; i<3; i++){
                    if(predominant_resources[i] == 0) res.setDiamond(1);
                    else if(predominant_resources[i] == 1) res.setSapphire(1);
                    else if(predominant_resources[i] == 2) res.setEmerald(1);
                    else if(predominant_resources[i] == 3) res.setRuby(1);
                    else if(predominant_resources[i] == 4) res.setOnyx(1);
                }
                pick3DifferentTokens(res);
                game_instance->getBank().removeResources(res);
            }
            else{ // not possible to pick 3 different tokens
                // for the moment it crashes here (but hardly reachable)
                // something ??
                nextTurn(); // to escape "very low chance crash", but we would need a better behavior
            }

//        }
//        else{ // more than 5 resources // something ??

//        }
        return;
    }
}

bool Controller::verifyTokensNumber(){
    if(current_player->getInventory().getResources().getSum() + current_player->getInventory().getResources().getGold() <= 10){
        return 0; // ok
    }
    else{
        return 1; // not ok, ask current player to chose X tokens to throw back to the bank
    }
}

void Controller::withdrawTokens(){
    while(current_player->getInventory().getResources().getSum()+current_player->getInventory().getResources().getGold() > 10){
        srand(time(NULL));
        int random = rand() % 6;
        if(random == 0 && current_player->getInventory().getResources().getDiamond() > 0){
            current_player->getInventory().removeResources(Resources(1,0,0,0,0,0));
            game_instance->getBank().addResources(Resources(1,0,0,0,0,0));
        }
        else if(random == 1 && current_player->getInventory().getResources().getSapphire() > 0){
            current_player->getInventory().removeResources(Resources(0,1,0,0,0,0));
            game_instance->getBank().addResources(Resources(0,1,0,0,0,0));
        }
        else if(random == 2 && current_player->getInventory().getResources().getEmerald() > 0){
            current_player->getInventory().removeResources(Resources(0,0,1,0,0,0));
            game_instance->getBank().addResources(Resources(0,0,1,0,0,0));
        }
        else if(random == 3 && current_player->getInventory().getResources().getRuby() > 0){
            current_player->getInventory().removeResources(Resources(0,0,0,1,0,0));
            game_instance->getBank().addResources(Resources(0,0,0,1,0,0));
        }
        else if(random == 4 && current_player->getInventory().getResources().getOnyx() > 0){
            current_player->getInventory().removeResources(Resources(0,0,0,0,1,0));
            game_instance->getBank().addResources(Resources(0,0,0,0,1,0));
        }
        else if(random == 5 && current_player->getInventory().getResources().getGold() > 0){
            current_player->getInventory().removeResources(Resources(0,0,0,0,0,1));
            game_instance->getBank().addResources(Resources(0,0,0,0,0,1));
        }
    }
}

void Controller::verifyNobles(){
    for(size_t i=0; i<game_instance->getBank().getBoardNobles().size(); i++){
        if(current_player->getInventory().getResourceAdvantages().getDiamond() >= game_instance->getBank().getBoardNobles()[i]->getCost().getDiamond()
        && current_player->getInventory().getResourceAdvantages().getSapphire() >= game_instance->getBank().getBoardNobles()[i]->getCost().getSapphire()
        && current_player->getInventory().getResourceAdvantages().getEmerald() >= game_instance->getBank().getBoardNobles()[i]->getCost().getEmerald()
        && current_player->getInventory().getResourceAdvantages().getRuby() >= game_instance->getBank().getBoardNobles()[i]->getCost().getRuby()
        && current_player->getInventory().getResourceAdvantages().getOnyx() >= game_instance->getBank().getBoardNobles()[i]->getCost().getOnyx()
                ){
            // change owner of noble card
            game_instance->getBank().getBoardNobles()[i]->changeOwner(*current_player);
            // add to current player inventory
            current_player->getInventory().addOwnedNoble(game_instance->getBank().getBoardNobles()[i]);
            // add prestige
            current_player->setPrestige(current_player->getPrestige()+game_instance->getBank().getBoardNobles()[i]->getPrestige());
            // remove from noble board
            game_instance->getBank().removeBoardNoble(i);
            // re-fill board // not sure if the rules say so
//            game_instance->getBank().insertBoardNoble(game_instance->getBank().drawNoble(),i);
            break;
        }
    }
}

void Controller::verifyCities(){
    for (size_t i=0; i<game_instance->getBank().getBoardCities().size(); i++){
        if(current_player->getInventory().getResourceAdvantages().getDiamond() >= game_instance->getBank().getBoardCities()[i]->getCost().getDiamond()
        && current_player->getInventory().getResourceAdvantages().getSapphire() >= game_instance->getBank().getBoardCities()[i]->getCost().getSapphire()
        && current_player->getInventory().getResourceAdvantages().getEmerald() >= game_instance->getBank().getBoardCities()[i]->getCost().getEmerald()
        && current_player->getInventory().getResourceAdvantages().getRuby() >= game_instance->getBank().getBoardCities()[i]->getCost().getRuby()
        && current_player->getInventory().getResourceAdvantages().getOnyx() >= game_instance->getBank().getBoardCities()[i]->getCost().getOnyx()
        && current_player->getPrestige() >= game_instance->getBank().getBoardCities()[i]->getPoints()
                ){
            // change owner of city card
            game_instance->getBank().getBoardCities()[i]->changeOwner(*current_player);
            // add to current player inventory
            current_player->getInventory().addOwnedCity(game_instance->getBank().getBoardCities()[i]);
            // remove from city board
            game_instance->getBank().removeBoardCity(i);
            // re-fill board // not sure if the rules say so
//            game_instance->getBank().insertBoardCity(game_instance->getBank().drawCity(),i);
            break;
        }
    }
}

void Controller::win(){
    if(game_instance->getExtension() == "classic"){
        if(current_player->getPrestige() >= game_instance->getPrestigeWin()){
            game_instance->setLastTurn(true);
        }
        if(game_instance->getLastTurn() && game_instance->getTurns() % game_instance->getPlayers().size() == game_instance->getPlayers().size() - 1){
            std::vector<Player*> winner;
            winner.push_back(game_instance->getPlayers()[0]);
            for(size_t i=1; i<game_instance->getPlayers().size(); i++){
                if(game_instance->getPlayers()[i]->getPrestige() > winner[0]->getPrestige()){
                    winner.clear();
                    winner.push_back(game_instance->getPlayers()[i]);
                }
                else if(game_instance->getPlayers()[i]->getPrestige() == winner[0]->getPrestige()){
                    winner.push_back(game_instance->getPlayers()[i]);
                }
            }
            VictoryWindow* next_window = new VictoryWindow(winner);
            next_window->show();
        }
    }
    else if(game_instance->getExtension() == "cities of splendor"){
        if(current_player->getPrestige() >= game_instance->getPrestigeWin() || current_player->getInventory().getOwnedCities().size() >= 1){
            game_instance->setLastTurn(true);
        }
        if(game_instance->getLastTurn() && game_instance->getTurns() % game_instance->getPlayers().size() == game_instance->getPlayers().size() - 1){
            std::vector<Player*> winner;
            winner.push_back(game_instance->getPlayers()[0]);
            for(size_t i=1; i<game_instance->getPlayers().size(); i++){
                if(game_instance->getPlayers()[i]->getInventory().getOwnedCities().size() >= winner[0]->getInventory().getOwnedCities().size() && game_instance->getPlayers()[i]->getPrestige() > winner[0]->getPrestige()){
                    winner.clear();
                    winner.push_back(game_instance->getPlayers()[i]);
                }
                else if(game_instance->getPlayers()[i]->getInventory().getOwnedCities().size() == winner[0]->getInventory().getOwnedCities().size() && game_instance->getPlayers()[i]->getPrestige() == winner[0]->getPrestige()){
                    winner.push_back(game_instance->getPlayers()[i]);
                }
            }
            VictoryWindow* next_window = new VictoryWindow(winner);
            next_window->show();
        }
    }
}

void Controller::nextTurn(){
    if(game_instance->getExtension() == "classic"){
        verifyNobles();
    }
    else if(game_instance->getExtension() == "cities of splendor"){
        verifyCities();
    }
    win();
    game_instance->incrementTurns();
    current_player = game_instance->getPlayers()[(game_instance->getTurns() % game_instance->getPlayers().size())];
    if(dynamic_cast<IA*>(current_player) != NULL){ // current player is an IA
        generateIAActions();
        nextTurn();
    }
}

bool Controller::buyable(Development* dev){
    bool buyable = true;
    // copy cost to check buyability
    // priority = advantages > resources > gold
    Resources res_left = dev->getCost();
    // deduct resources advantages
    res_left.setDiamond(res_left.getDiamond() - current_player->getInventory().getResourceAdvantages().getDiamond());
    res_left.setSapphire(res_left.getSapphire() - current_player->getInventory().getResourceAdvantages().getSapphire());
    res_left.setEmerald(res_left.getEmerald() - current_player->getInventory().getResourceAdvantages().getEmerald());
    res_left.setRuby(res_left.getRuby() - current_player->getInventory().getResourceAdvantages().getRuby());
    res_left.setOnyx(res_left.getOnyx() - current_player->getInventory().getResourceAdvantages().getOnyx());

    // deduct resources
    for(int i=0; i<current_player->getInventory().getResources().getDiamond() && res_left.getDiamond()>0 ; i++){
        res_left.setDiamond(res_left.getDiamond() - 1);
    }
    for(int i=0; i<current_player->getInventory().getResources().getSapphire() && res_left.getSapphire()>0 ; i++){
        res_left.setSapphire(res_left.getSapphire() - 1);
    }
    for(int i=0; i<current_player->getInventory().getResources().getEmerald() && res_left.getEmerald()>0 ; i++){
        res_left.setEmerald(res_left.getEmerald() - 1);
    }
    for(int i=0; i<current_player->getInventory().getResources().getRuby() && res_left.getRuby()>0 ; i++){
        res_left.setRuby(res_left.getRuby() - 1);
    }
    for(int i=0; i<current_player->getInventory().getResources().getOnyx() && res_left.getOnyx()>0 ; i++){
        res_left.setOnyx(res_left.getOnyx() - 1);
    }

    // deduct gold
    int left = res_left.getSum();
    if(left > current_player->getInventory().getResources().getGold()){
        buyable = false;
    }

    return buyable;
}

Controller::~Controller(){

}
