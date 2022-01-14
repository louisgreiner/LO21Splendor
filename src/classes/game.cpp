#include "./headers/game.h"
#include "./headers/exception.h"

Game* Game::instance_ = 0;

// Constructors
Game::Game(QString ext, QString g_name, std::vector<Player*> pla){
    // game params
    game_name = g_name;
    extension = ext;
    prestige_win = 15;
    last_turn = false;
    turns = 0;
    global_time = 0;
    time_per_player.push_back(0);
    time_per_player.push_back(0);
    time_per_player.push_back(0);
    time_per_player.push_back(0);

    // create players
    for(auto players_pointer : pla){
       this->players.push_back(players_pointer->FactoryMethod());
    }

    // initialize developments and nobles cards
    std::vector<Development*> temp;
    developments.push_back(temp); // level 1
    developments.push_back(temp); // level 2
    developments.push_back(temp); // level 3

    // initialize cards and Bank
    QString extension_path;
    if (extension == "classic"){
        extension_path = "C:/Users/grein/Desktop/UTC/GI02/LO21/lo21_splendor/src/extensions/classic.xml"; // need to manually change path here, sorry!
//        extension_path = "extensions/classic.xml"; // doesn't work, idk why
//        extension_path = "/extensions/classic.xml"; // same :(
        loadCards(extension_path);
        bank = Bank(developments, nobles, pla.size());
    }else if (extension == "cities of splendor"){
        extension_path = "C:/Users/grein/Desktop/UTC/GI02/LO21/lo21_splendor/src/extensions/cities_of_splendor.xml";
        loadCards(extension_path);
        bank = Bank(developments, cities, pla.size());
    }
}

void Game::loadCards(QString extension_path){
    if (extension == "classic"){
        QDomDocument cardsXML;
        QFile xmlFile(extension_path);
        if (!xmlFile.exists()) {
            throw Exception("XML file doesn't exist");
        }

        if (!xmlFile.open(QIODevice::ReadOnly )){
            xmlFile.close();
            throw Exception("Cannot open XML file");
        }

        cardsXML.setContent(&xmlFile);
        xmlFile.close();

        QDomElement root = cardsXML.documentElement();
        QDomElement child = root.firstChild().toElement();

        while(!child.isNull()){
            if(child.tagName() == "development"){
                int id, prestige, level;
                Player* owner;
                QString status;
                Resources cost, advantages;
                id = child.attribute("id","-1").toInt();
                prestige = child.attribute("prestige","-1").toInt();
                level = child.attribute("level","0").toInt();
                if(child.attribute("owner","0").toInt() == 0){
                    owner = nullptr;
                }
                else{
                    owner = this->findUserById(child.attribute("owner").toInt());
                }
                status = child.attribute("status","face_down"); // toStdString().c_str()
                QDomElement grandChild = child.firstChild().toElement();
                while(!grandChild.isNull()){
                    if(grandChild.tagName() == "cost"){
                        cost = *new Resources(
                            grandChild.attribute("diamond","-1").toInt(),
                            grandChild.attribute("sapphire","-1").toInt(),
                            grandChild.attribute("emerald","-1").toInt(),
                            grandChild.attribute("ruby","-1").toInt(),
                            grandChild.attribute("onyx","-1").toInt(),
                            grandChild.attribute("gold","-1").toInt()
                        );
                    }
                    else if(grandChild.tagName() == "advantages"){
                        advantages = *new Resources(
                            grandChild.attribute("diamond","-1").toInt(),
                            grandChild.attribute("sapphire","-1").toInt(),
                            grandChild.attribute("emerald","-1").toInt(),
                            grandChild.attribute("ruby","-1").toInt(),
                            grandChild.attribute("onyx","-1").toInt(),
                            grandChild.attribute("gold","-1").toInt()
                        );
                    }
                    grandChild = grandChild.nextSibling().toElement();
                    // ALERT : Potential memory leak !!??
                }
                Development temp_dev(id,prestige,&cost,owner,level,&advantages);
                this->developments[child.attribute("level","1").toInt()-1].push_back(temp_dev.FactoryMethod());
            }
            else if(child.tagName() == "noble"){
                int id, prestige;
                Player* owner = nullptr;
                QString status;
                Resources cost;
                id = child.attribute("id","-1").toInt();
                prestige = child.attribute("prestige","-1").toInt();
                if(child.attribute("owner","0").toInt() != 0){
                    owner = this->findUserById(child.attribute("owner").toInt());
                }
                status = child.attribute("status","face_down"); // toStdString().c_str()
                QDomElement grandChild = child.firstChild().toElement();
                while(!grandChild.isNull()){
                    if(grandChild.tagName() == "cost"){
                        cost = *new Resources(
                            grandChild.attribute("diamond","-1").toInt(),
                            grandChild.attribute("sapphire","-1").toInt(),
                            grandChild.attribute("emerald","-1").toInt(),
                            grandChild.attribute("ruby","-1").toInt(),
                            grandChild.attribute("onyx","-1").toInt(),
                            grandChild.attribute("gold","-1").toInt()
                        );
                    }
                    grandChild = grandChild.nextSibling().toElement();
                    // ALERT : Potential memory leak !!??
                }
                Noble temp_nob(id,prestige,&cost,owner);
                this->nobles.push_back(temp_nob.FactoryMethod());
            }
            child = child.nextSibling().toElement();
        }
    }else if (extension == "cities of splendor"){
        QDomDocument cardsXML;
        QFile xmlFile(extension_path);
        if (!xmlFile.exists()) {
            throw Exception("XML file doesn't exist");
        }

        if (!xmlFile.open(QIODevice::ReadOnly )){
            xmlFile.close();
            throw Exception("Cannot open XML file");
        }

        cardsXML.setContent(&xmlFile);
        xmlFile.close();

        QDomElement root = cardsXML.documentElement();
        QDomElement child = root.firstChild().toElement();

        while(!child.isNull()){
            if(child.tagName() == "development"){
                int id, prestige, level;
                Player* owner;
                QString status;
                Resources cost, advantages;
                id = child.attribute("id","-1").toInt();
                prestige = child.attribute("prestige","-1").toInt();
                level = child.attribute("level","0").toInt();
                if(child.attribute("owner","0").toInt() == 0){
                    owner = nullptr;
                }
                else{
                    owner = this->findUserById(child.attribute("owner").toInt());
                }
                status = child.attribute("status","face_down"); // toStdString().c_str()
                QDomElement grandChild = child.firstChild().toElement();
                while(!grandChild.isNull()){
                    if(grandChild.tagName() == "cost"){
                        cost = *new Resources(
                            grandChild.attribute("diamond","-1").toInt(),
                            grandChild.attribute("sapphire","-1").toInt(),
                            grandChild.attribute("emerald","-1").toInt(),
                            grandChild.attribute("ruby","-1").toInt(),
                            grandChild.attribute("onyx","-1").toInt(),
                            grandChild.attribute("gold","-1").toInt()
                    );
                }
                else if(grandChild.tagName() == "advantages"){
                    advantages = *new Resources(
                        grandChild.attribute("diamond","-1").toInt(),
                        grandChild.attribute("sapphire","-1").toInt(),
                        grandChild.attribute("emerald","-1").toInt(),
                        grandChild.attribute("ruby","-1").toInt(),
                        grandChild.attribute("onyx","-1").toInt(),
                        grandChild.attribute("gold","-1").toInt()
                    );
                }
                grandChild = grandChild.nextSibling().toElement();
                // ALERT : Potential memory leak !!??
                }
                Development temp_dev(id,prestige,&cost,owner,level,&advantages);
                this->developments[child.attribute("level","1").toInt()-1].push_back(temp_dev.FactoryMethod());
            }
            else if(child.tagName() == "city"){
                int id;
                Player* owner = nullptr;
                QString status;
                Resources cost;
                int pre=0;
                int points;
                id = child.attribute("id","-1").toInt();
                if(child.attribute("owner","0").toInt() != 0){
                    owner = this->findUserById(child.attribute("owner").toInt());
                }
                status = child.attribute("status","face_down"); // toStdString().c_str()
                QDomElement grandChild = child.firstChild().toElement();
                while(!grandChild.isNull()){
                    if(grandChild.tagName() == "cost"){
                        cost = *new Resources(
                            grandChild.attribute("diamond","-1").toInt(),
                            grandChild.attribute("sapphire","-1").toInt(),
                            grandChild.attribute("emerald","-1").toInt(),
                            grandChild.attribute("ruby","-1").toInt(),
                            grandChild.attribute("onyx","-1").toInt(),
                            grandChild.attribute("gold","-1").toInt()
                        );
                    }
                    if(grandChild.tagName() == "points") {
                        points = grandChild.attribute("points","-1").toInt();
                    }
                    grandChild = grandChild.nextSibling().toElement();
                // ALERT : Potential memory leak !!??
                }
                City temp_city(id,pre, &cost,owner, points);
                this->cities.push_back(temp_city.FactoryMethod());
            }
            child = child.nextSibling().toElement();
        }
    }

}


// Getters
Bank& Game::getBank(){
    return bank;
}

const QString Game::getGameName() const{
    return game_name;
}

const QString Game::getExtension() const{
    return extension;
}

std::vector<std::vector<Development*>> Game::getDevelopments() const{
    return developments;
}

std::vector<Noble*> Game::getNobles() const{
    return nobles;
}

std::vector<City*> Game::getCities() const{
    return cities;
}

std::vector<Player*> Game::getPlayers(){ // or Player* getPlayers() const
    return players;
}

Player* Game::findUserById(int own){
    return players[own+1];
}

int Game::getPrestigeWin() const{
    return prestige_win;
}

bool Game::getLastTurn() const{
    return last_turn;
}

void Game::setLastTurn(bool var){
    last_turn = var;
}

int Game::getTurns() const{
    return turns;
}

time_t Game::getGlobalTime() const{
    return global_time;
}

time_t Game::getTimePerPlayer(int id) const{
    return time_per_player[id];
}

Game* Game::getInstance(QString ext, QString g_name, std::vector<Player*> pla){
    if(instance_ == nullptr){
        instance_ = new Game(ext,g_name,pla);
    }
    return instance_;
}

Game* Game::getSavedInstance(QString g_name){
    return instance_;
}

// Others
void Game::incrementTurns(){
    turns++;
}

void Game::saveGame(){

}

void Game::savePlayersStats(){

}

// Destructor
Game::~Game(){

}
