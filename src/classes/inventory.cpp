#include "./headers/inventory.h"

// Constructors
Inventory::Inventory(): resources(Resources(0,0,0,0,0,0)), resource_advantages(Resources(0,0,0,0,0,0)){
}

// Getters
Resources Inventory::getResources(){
    return resources;
}

Resources Inventory::getResourceAdvantages(){
    return resource_advantages;
}

std::vector<Development*> Inventory::getReservedDevelopments(){
    return reserved_developments;
}

std::vector<Development*> Inventory::getOwnedDevelopments(){
    return owned_developments;
}

std::vector<Noble*> Inventory::getOwnedNobles(){
    return owned_nobles;
}

std::vector<City*> Inventory::getOwnedCities(){
    return owned_cities;
}

// Setters
void Inventory::addResources(Resources res){
    resources.setDiamond(resources.getDiamond() + res.getDiamond());
    resources.setSapphire(resources.getSapphire() + res.getSapphire());
    resources.setEmerald(resources.getEmerald() + res.getEmerald());
    resources.setRuby(resources.getRuby() + res.getRuby());
    resources.setOnyx(resources.getOnyx() + res.getOnyx());
    resources.setGold(resources.getGold() + res.getGold());
}

void Inventory::removeResources(Resources res){
    if(res.getDiamond() > 0) resources.setDiamond(resources.getDiamond() - res.getDiamond());
    if(res.getSapphire() > 0) resources.setSapphire(resources.getSapphire() - res.getSapphire());
    if(res.getEmerald() > 0) resources.setEmerald(resources.getEmerald() - res.getEmerald());
    if(res.getRuby() > 0) resources.setRuby(resources.getRuby() - res.getRuby());
    if(res.getOnyx() > 0) resources.setOnyx(resources.getOnyx() - res.getOnyx());
    if(res.getGold() > 0) resources.setGold(resources.getGold() - res.getGold());
}

void Inventory::addResourceAdvantages(Resources res_adv){
    resource_advantages.setDiamond(resource_advantages.getDiamond() + res_adv.getDiamond());
    resource_advantages.setSapphire(resource_advantages.getSapphire() + res_adv.getSapphire());
    resource_advantages.setEmerald(resource_advantages.getEmerald() + res_adv.getEmerald());
    resource_advantages.setRuby(resource_advantages.getRuby() + res_adv.getRuby());
    resource_advantages.setOnyx(resource_advantages.getOnyx() + res_adv.getOnyx());
    resource_advantages.setGold(resource_advantages.getGold() + res_adv.getGold());
}

void Inventory::addReservedDevelopment(Development* dev){
    if(reserved_developments.size() >= 3) throw "error in adding reserved dev";
    reserved_developments.push_back(dev);
}

void Inventory::removeReservedDevelopment(Development* dev){
    if(reserved_developments.size() <= 0) throw "error in deleting reserved dev";
    size_t i;
    for(i=0; i<reserved_developments.size(); i++){ // not the most efficient option so far
        if(reserved_developments[i]->getId() == dev->getId()){
            reserved_developments.erase(reserved_developments.begin() + i);
            break;
        }
    }
}

void Inventory::addOwnedDevelopment(Development* dev){
    owned_developments.push_back(dev);
}

void Inventory::addOwnedNoble(Noble* nob){
    owned_nobles.push_back(nob);
}

void Inventory::addOwnedCity(City* city){
    owned_cities.push_back(city);
}


// Destructors
Inventory::~Inventory(){

}
