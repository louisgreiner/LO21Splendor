#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"
#include <QString>

class Player{
    friend class Inventory; // not sure what is the purpose of it, having access to protected fields ?
    private:
        // Attributes
        QString name;
        Inventory inventory;
        int prestige;
    public:
        // Constructors
        virtual Player* FactoryMethod() const = 0; // Factory method
        Player(QString nam); // ->> Design Pattern Factory // DONE
        // Getters
        QString getName(); // DONE
        Inventory& getInventory(); // DONE
        int getPrestige(); // DONE
        // Setters
        void setPrestige(int pre); // DONE
};

class Human : public Player{
    private:
    public:
        // Constructors
        Human* FactoryMethod() const{
            return new Human(*this);
        }
        Human(QString nam); // DONE
        // Destructor
        ~Human();
};

class IA : public Player{
    private:
        int level;
    public:
        // Constructors
        IA* FactoryMethod() const{
            return new IA(*this);
        }
        IA(QString nam, int lev); // DONE
        // Getters
        int getLevel(); // DONE
        // Destructor
        ~IA();
};

#endif // PLAYER_H
