#ifndef DRAW_H
#define DRAW_H

#include "card.h"
#include <vector>
#include "time.h"

class Draw{
    protected:
        // Attributes
        int cards_left;
    public:
        // Constructors
        virtual Draw* FactoryMethod() const = 0; // Factory method
        Draw(int size);
        // Getters
        int getCardsLeft(); // DONE
        // Setters
        virtual void removeCard(int i) = 0;
        // Others
        bool isEmpty() const; // DONE
};

class DevelopmentsDraw: public Draw{ // inheritance
    private:
        // Attributes
        int level;
        std::vector<Development*> developments; // ordered draw
    public:
        // Constructors
        DevelopmentsDraw(int lev, std::vector<Development*> dev); // DONE
        DevelopmentsDraw* FactoryMethod() const{
            return new DevelopmentsDraw(*this);
        }
        // Getters
        int getLevel(); // should be deleted probably, useless // DONE
        // Others
        void removeCard(int i); // DONE // better move from "int i" to "Development* dev" but difficult bc inherited from abstract class
        Development* draw(); // DONE
        // Destructors
        ~DevelopmentsDraw();
};

class NoblesDraw: public Draw{ // inheritance
    private:
        std::vector<Noble*> nobles; // ordered drawé
    public:
        // Constructors
        NoblesDraw(std::vector<Noble*> nob); // DONE
        NoblesDraw* FactoryMethod() const{
            return new NoblesDraw(*this);
        }
        // Others
        void removeCard(int i); // DONE // better move from "int i" to "Noble* nob"
        Noble* draw(); // DONE
        // Destructors
        ~NoblesDraw();
};

class CitiesDraw: public Draw{ // inheritance
    private:
        std::vector<City*> cities; // ordered draw
    public:
        // Constructors
        CitiesDraw(std::vector<City*> cities); 
        CitiesDraw* FactoryMethod() const{
            return new CitiesDraw(*this);
        }
        // Others
        void removeCard(int i); // DONE // better move from "int i" to "City* cit"
        City* draw(); // DONE
        // Destructors
        ~CitiesDraw();
};

#endif // DRAW_H
