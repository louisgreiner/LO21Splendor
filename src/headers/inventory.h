#ifndef INVENTORY_H
#define INVENTORY_H

#include "resources.h"
#include "card.h"
#include <vector>

class Inventory{
    private:
        // Attributes
        Resources resources;
        Resources resource_advantages;
        std::vector<Development*> reserved_developments; // max 3
        std::vector<Development*> owned_developments;
        std::vector<Noble*> owned_nobles;
        std::vector<City*> owned_cities;
    public:
        // Constructors
        Inventory(); // DONE
        // Getters
        Resources getResources(); // DONE
        Resources getResourceAdvantages(); // DONE
        std::vector<Development*> getReservedDevelopments(); // DONE
        std::vector<Development*> getOwnedDevelopments(); // DONE
        std::vector<Noble*> getOwnedNobles(); // DONE
        std::vector<City*> getOwnedCities(); // DONE
        
        // Setters
        void addResources(Resources res); // DONE
        void removeResources(Resources res); // DONE
        void addResourceAdvantages(Resources res); // DONE
        void addReservedDevelopment(Development* dev); // DONE
        void removeReservedDevelopment(Development* dev); // DONE
        void addOwnedDevelopment(Development* dev); // DONE
        void addOwnedNoble(Noble* nob); // DONE
        void addOwnedCity(City* city); // DONE

        // Destructors
        ~Inventory();

    friend class Resources; // usefull or useless ? i dont know
};

#endif // INVENTORY_H
