#include "./headers/draw.h"

// Abstract class Draw
    // Constructors
    Draw::Draw(int size){
        cards_left = size;
    }

    // Getters
    int Draw::getCardsLeft(){
        return cards_left;
    }
    bool Draw::isEmpty() const{
        return cards_left == 0;
    }

// Class DevelopmentsDraw
    // Constructors
    DevelopmentsDraw::DevelopmentsDraw(int lev, std::vector<Development*> dev): Draw(dev.size()){
        level = lev;
        developments = dev;
    }

    // Getters
    int DevelopmentsDraw::getLevel(){
        return level;
    }

    // Others
    void DevelopmentsDraw::removeCard(int i){
        developments.erase(developments.begin() + i);
        cards_left--;
    }

    Development* DevelopmentsDraw::draw(){
        srand(time(NULL));
        int random = rand() % developments.size();
        Development* temp = developments[random];
        size_t i;
        for(i=0; i<developments.size(); i++){ // not the most efficient option so far
            if(developments[i]->getId() == developments[random]->getId()){
                removeCard(i);
                break;
            }
        }
    //    auto it = std::find(developments.begin(), developments.end(), temp); // doesn't work
        return temp;
    }

    // Destructors
    DevelopmentsDraw::~DevelopmentsDraw(){

    }


// Class NoblesDraw
    // Constructors
    NoblesDraw::NoblesDraw(std::vector<Noble*> nob): Draw(nob.size()){
        nobles = nob;
    }

    // Others
    void NoblesDraw::removeCard(int i){
        nobles.erase(nobles.begin() + i);
        cards_left--;
    }

    Noble* NoblesDraw::draw(){
        srand(time(NULL));
        int random = rand() % nobles.size();
        Noble* temp = nobles[random];
        size_t i;
        for(i=0; i<nobles.size(); i++){ // not the most efficient option so far
            if(nobles[i]->getId() == nobles[random]->getId()){
                removeCard(i);
                break;
            }
        }
        return temp;
    }

    // Destructors
    NoblesDraw::~NoblesDraw(){

    }


// Class CitiesDraw
    // Constructors
    CitiesDraw::CitiesDraw(std::vector<City*> city): Draw(city.size()){
        cities = city;
    }

    // Others
    void CitiesDraw::removeCard(int i){
        cities.erase(cities.begin() + i);
        cards_left--;
    }

    City* CitiesDraw::draw(){
//        srand(time(NULL));
        int random = rand() % cities.size();
        City* temp = cities[random];
        size_t i;
        for(i=0; i<cities.size(); i++){
            if(cities[i]->getId() == cities[random]->getId()){
                removeCard(i);
                break;
            }
        }
        return temp;
    }

    // Destructors
    CitiesDraw::~CitiesDraw(){

    }
