#include "./headers/card.h"
#include "./headers/exception.h"

// Abstract class Card
    // Constructors
    Card::Card(int i, int pre, Resources* res, Player* own){
        id = i;
        prestige = pre;
        cost = *res;
        owner = own;
        status = "face_down";
    }

    // Getters
    int Card::getId() const{
        return id;
    }

    int Card::getPrestige() const{
        return prestige;
    }

    Resources Card::getCost() const{
        return cost;
    }

    Player* Card::getOwner() const{
        return owner;
    }

    QString Card::getStatus() const{
        return status;
    }

    // Setters
    void Card::changeOwner(Player& player){
        owner = &player;
    }

    void Card::flipCard(){
        if(status == "face_up"){
            status = "face_down";
        }
        else if(status == "face_down"){
            status = "face_up";
        }
        else{
            throw Exception("Cannot flip card");
        }
    }

// Class Development
    // Constructors
    Development::Development(int i, int pre, Resources* res, Player* own, int lev, Resources* adv): Card(i,pre,res,own){
        level = lev;
        advantages = *adv;
    }

    // Getters
    int Development::getLevel() const{
        return level;
    }

    Resources Development::getAdvantages() const{
        return advantages;
    }

    void Development::getInformations(std::ostream& f) const {
        f << "\nDevelopment :"
             "\n\t- ID : " << getId() <<
             "\n\t- Level : " << getLevel() <<
             "\n\t- Prestige : " << getPrestige() <<
             "\n\t- Cost : " << getCost() <<
             "\n\t- Advantages : " << getAdvantages() <<
             "\n\t- Owner : " << getOwner() <<
             "\n\t- Status : " << getStatus().toStdString() << "\n";
    }

    std::ostream& operator<<(std::ostream& f, const Development& dev){
        dev.getInformations(f);
        return f;
    }

    // Destructors
    Development::~Development(){

    }

// Class Noble
    // Constructors
    Noble::Noble(int i, int pre, Resources* res, Player* own): Card(i,pre,res,own){
    }

    void Noble::getInformations(std::ostream& f) const {
        f << "\nDevelopment :"
             "\n\t- ID : " << getId() <<
             "\n\t- Prestige : " << getPrestige() <<
             "\n\t- Cost : " << getCost() <<
             "\n\t- Owner : " << getOwner() <<
             "\n\t- Status : " << getStatus().toStdString() << "\n";
    }

    std::ostream& operator<<(std::ostream& f, const Noble& nob){
        nob.getInformations(f);
        return f;
    }

    // Destructors
    Noble::~Noble(){

    }

// Class City
    // Constructors
    City::City(int i, int pre , Resources* res, Player* own, int p): Card(i,pre,res,own), points(p){
    }

    void City::getInformations(std::ostream& f) const {
        f << "\nDevelopment :"
             "\n\t- ID : " << getId() <<
             "\n\t- Prestige needed : " << getPoints() <<
             "\n\t- Cost : " << getCost() <<
             "\n\t- Owner : " << getOwner() <<
             "\n\t- Status : " << getStatus().toStdString()<< "\n";
    }

    std::ostream& operator<<(std::ostream& f, const City& city){
        city.getInformations(f);
        return f;
    }

    int City::getPoints() const {
        return points;
    }

    // Destructors
    City::~City(){

    }
