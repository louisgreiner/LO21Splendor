#include "./headers/resources.h"

// Constructors
Resources::Resources():diamond(0),sapphire(0),emerald(0),ruby(0),onyx(0),gold(0){

}

Resources::Resources(int d, int s, int e, int r, int o, int g){
    setDiamond(d);
    setSapphire(s);
    setEmerald(e);
    setRuby(r);
    setOnyx(o);
    setGold(g);
}

// Getters
int Resources::getDiamond(){
    return diamond;
}

int Resources::getSapphire(){
    return sapphire;
}

int Resources::getEmerald(){
    return emerald;
}

int Resources::getRuby(){
    return ruby;
}

int Resources::getOnyx(){
    return onyx;
}

int Resources::getGold(){
    return gold;
}

int Resources::getSum(){
    return diamond + sapphire + emerald + ruby + onyx;
}

void Resources::getInformations(std::ostream& f) const{
    f << "(d=" << diamond << ", s=" << sapphire << ", e=" << emerald << ", r=" << ruby << ", o=" << onyx << ", g=" << gold << ")";
}

std::ostream& operator<<(std::ostream& f, const Resources& res){
    res.getInformations(f);
    return f;
}

// Setters
void Resources::setDiamond(int d){
    diamond = d;
}

void Resources::setSapphire(int s){
    sapphire = s;
}

void Resources::setEmerald(int e){
    emerald = e;
}

void Resources::setRuby(int r){
    ruby = r;
}

void Resources::setOnyx(int o){
    onyx = o;
}

void Resources::setGold(int g){
    gold = g;
}
