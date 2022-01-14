#include "./headers/bank.h"

// Constructors
Bank::Bank(){

}

Bank::Bank(std::vector<std::vector<Development*>> dev, std::vector<Noble*> nob, int pla_num){
    // Resources, depending on the number of players
    if(pla_num == 2){
        resources = Resources(4,4,4,4,4,5);
    }
    else if(pla_num == 3){
        resources = Resources(5,5,5,5,5,5);
    }
    else if(pla_num == 4){
        resources = Resources(7,7,7,7,7,5);
    }

    // Draws
    int lev = 0;
    for(auto d : dev){
        this->developments_draw.push_back(DevelopmentsDraw(lev,d).FactoryMethod());
        lev++;
    }
    nobles_draw.push_back(NoblesDraw(nob).FactoryMethod());
    // Board
    std::vector<Development*> temp;
    for(size_t i=0; i<3; i++){ // 3 columns
        developments_board.push_back(temp);
        for(size_t j=0; j<4; j++){ // 4 rows
            developments_board[i].push_back(drawDevelopment(i+1));
            developments_board[i][j]->flipCard();
        }
    }

    for(int i=0; i<pla_num+1; i++){ // player number + 1 = number of nobles
        nobles_board.push_back(drawNoble());
        nobles_board[i]->flipCard();
    }
}

Bank::Bank(std::vector<std::vector<Development*>> dev, std::vector<City*> city, int pla_num){
    // Resources, depending on the number of players
    if(pla_num == 2){
        resources = Resources(4,4,4,4,4,5);
    }
    else if(pla_num == 3){
        resources = Resources(5,5,5,5,5,5);
    }
    else if(pla_num == 4){
        resources = Resources(7,7,7,7,7,5);
    }

    // Draws
    int lev = 0;
    for(auto d : dev){
        this->developments_draw.push_back(DevelopmentsDraw(lev,d).FactoryMethod());
        lev++;
    }
    cities_draw.push_back(CitiesDraw(city).FactoryMethod());
    // Board
    std::vector<Development*> temp;
    for(size_t i=0; i<3; i++){ // 3 columns
        developments_board.push_back(temp);
        for(size_t j=0; j<4; j++){ // 4 rows
            developments_board[i].push_back(drawDevelopment(i+1));
            developments_board[i][j]->flipCard();
        }
    }
    for(size_t i=0; i<3; i++){
        cities_board.push_back(drawCity());
        cities_board[i]->flipCard();
    }
}

// Getters
Resources Bank::getResources(){
    return resources;
}

std::vector<std::vector<Development*>> Bank::getBoardDevelopments(){
    return developments_board;
}

std::vector<DevelopmentsDraw*> Bank::getDrawDevelopments(){
    return developments_draw;
}

std::vector<Noble*> Bank::getBoardNobles(){
    return nobles_board;
}

std::vector<NoblesDraw*> Bank::getDrawNobles(){
    return nobles_draw;
}

std::vector<City*> Bank::getBoardCities(){
    return cities_board;
}

std::vector<CitiesDraw*> Bank::getDrawCities(){
    return cities_draw;
}

void Bank::getBoardDevelopmentInformations(std::ostream& f) const{
    f << "Developments board (ID): \n";
    size_t i = 1;
    for(auto lev : developments_board){
        for(auto dev : lev){
            f << " - " << dev->getId();
        }
        f << " <- level " << i << "\n";
        i++;
    }
}

void Bank::getBoardNobleBoardInformations(std::ostream& f) const{
    f << "Nobles board (ID):\n";
    for(auto nob : nobles_board){
        f << " - " << nob->getId();
    }
    f << "\n";
}

void Bank::getBoardCityBoardInformations(std::ostream& f) const{
    f << "Cities board (ID):\n";
    for(auto city : cities_board){
        f << " - " << city->getId();
    }
    f << "\n";
}

void Bank::getDrawDevelopmentsInformations(std::ostream& f) const{
    f << "Developments draws (cards left):\n";
    for(auto dra : developments_draw){
        f << " - " << dra->getCardsLeft();
    }
    f << " (level 1, level 2, level 3)\n";
}

void Bank::getDrawNoblesInformations(std::ostream& f) const{
    f << "Nobles draw (cards left):\n";
    for(auto dra : nobles_draw){
        f << " - " << dra->getCardsLeft();
    }
    f << "\n";
}

std::ostream& Bank::getBoardInformations(std::ostream& f) const{
    std::cout << "Resources : " << resources << "\n";
    getDrawNoblesInformations(f);
    getBoardNobleBoardInformations(f);
    getDrawDevelopmentsInformations(f);
    getBoardDevelopmentInformations(f);
    return f;
}

// Setters
void Bank::addResources(Resources res){
    resources.setDiamond(resources.getDiamond() + res.getDiamond());
    resources.setSapphire(resources.getSapphire() + res.getSapphire());
    resources.setEmerald(resources.getEmerald() + res.getEmerald());
    resources.setRuby(resources.getRuby() + res.getRuby());
    resources.setOnyx(resources.getOnyx() + res.getOnyx());
    resources.setGold(resources.getGold() + res.getGold());
}

void Bank::removeResources(Resources res){
    resources.setDiamond(resources.getDiamond() - res.getDiamond());
    resources.setSapphire(resources.getSapphire() - res.getSapphire());
    resources.setEmerald(resources.getEmerald() - res.getEmerald());
    resources.setRuby(resources.getRuby() - res.getRuby());
    resources.setOnyx(resources.getOnyx() - res.getOnyx());
    resources.setGold(resources.getGold() - res.getGold());
}

// Others
Development* Bank::drawDevelopment(int level){
    return developments_draw[level-1]->draw();
}

Noble* Bank::drawNoble(){ // [0] = first level of draw, if later we want to have severals noble draws
    return nobles_draw[0]->draw();
}

City* Bank::drawCity(){ 
    return cities_draw[0]->draw();
}

void Bank::removeBoardDevelopment(int lev, int pos){
    developments_board[lev].erase(developments_board[lev].begin() + pos);
}

void Bank::insertBoardDevelopment(Development* dev, int lev, int pos){
    developments_board[lev].insert(developments_board[lev].begin() + pos, dev);
}

void Bank::removeBoardNoble(int pos){
    nobles_board.erase(nobles_board.begin() + pos);
}

void Bank::insertBoardNoble(Noble* nob, int pos){
    nobles_board.insert(nobles_board.begin() + pos, nob);
}

void Bank::removeBoardCity(int pos){
    cities_board.erase(cities_board.begin() + pos);
}

void Bank::insertBoardCity(City* city, int pos){
    cities_board.insert(cities_board.begin() + pos, city);
}


// Destructors
Bank::~Bank(){

}
