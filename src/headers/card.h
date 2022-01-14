#ifndef CARD_H
#define CARD_H

#include <QString>
#include <iostream>
#include "resources.h"

class Player; // forward declaration
class Human; // forward declaration

class Card{
    private:
        // Attributes
        int id;
        int prestige;
        Resources cost;
        Player* owner;
        QString status; // "face_up" or "face_down" // actually useless :(
    public:
        // Constructors
        virtual Card* FactoryMethod() const = 0; // Factory design pattern
        Card(int id, int pre, Resources *res, Player* own); // DONE
        // Getters
        int getId() const; // DONE
        int getPrestige() const; // DONE
        Resources getCost() const; // DONE
        Player* getOwner() const; // DONE
        QString getStatus() const; // DONE
        virtual void getInformations(std::ostream& f = std::cout) const = 0;
        // Setters
        void changeOwner(Player& player); // DONE
        void flipCard(); // DONE
};

class Development: public Card{ // inheritance
    private:
        // Attributes
        int level;
        Resources advantages;
    public:
        // Constructors
        Development(int i, int pre, Resources* res, Player* own, int level, Resources* adv); // DONE
        Development* FactoryMethod() const{
            return new Development(*this);
        }
        // Getters
        int getLevel() const; // DONE
        Resources getAdvantages() const; // DONE
        void getInformations(std::ostream& f= std::cout) const; // DONE
        // Destructors
        ~Development();
};

class Noble: public Card{ // inheritance
    private:
        // Attributes
    public:
        // Constructors
        Noble(int i, int pre, Resources* res, Player* own); // DONE
        Noble* FactoryMethod() const{
            return new Noble(*this);
        }
        // Getters
        void getInformations(std::ostream& f= std::cout) const; // DONE
        // Destructors
        ~Noble();
};


class City: public Card{ // inheritance
    private:
        // Attributes
        int points; // prestige points needed to be able to get a specific city
    public:
        // Constructors
        City(int i, int pre, Resources* res, Player* own, int p); // DONE
        City* FactoryMethod() const{
            return new City(*this);
        }
        // Getters
        void getInformations(std::ostream& f= std::cout) const; // DONE
        int getPoints() const; // DONE
        int getPrestige() const = delete; // DONE

        // Destructors
        ~City();
};

std::ostream& operator<<(std::ostream& f, const Development& dev); // DONE
std::ostream& operator<<(std::ostream& f, const Noble& nob); // DONE
std::ostream& operator<<(std::ostream& f, const City& nob); // DONE

#endif // CARD_H
