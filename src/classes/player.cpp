#include "./headers/player.h"

// Abstract class Player
    // Constructors
    Player::Player(QString nam): name(nam), inventory(Inventory()), prestige(0){
    }

    // Getters
    QString Player::getName(){
        return name;
    }

    Inventory& Player::getInventory(){
        return inventory;
    }

    int Player::getPrestige(){
        return prestige;
    }

    // Setters
    void Player::setPrestige(int pre){
        prestige = pre;
    }

// Class Human
    // Constructors
    Human::Human(QString nam): Player(nam){
    }

    // Destructor
    Human::~Human(){

    }

// Class IA
    // Constructors
    IA::IA(QString nam, int lev): Player(nam), level(lev){

    }

    // Getters
    int IA::getLevel(){
        return level;
    }

    // Destructor
    IA::~IA(){

    }

