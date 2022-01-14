#ifndef BANK_H
#define BANK_H

#include "resources.h"
#include "card.h"
#include "draw.h"
#include <vector>

class Bank{
    private:
        // Attributes
        Resources resources;
        std::vector<std::vector<Development*>> developments_board; // 3 rows * 4 columns
        std::vector<DevelopmentsDraw*> developments_draw; // 1 row * 3 columns
        std::vector<Noble*> nobles_board; // 1 row * 5 colums
        std::vector<NoblesDraw*> nobles_draw; // just 1 noble draw, implemented as vector for flexibility
        std::vector<City*> cities_board; // 1 row * 3 colums
        std::vector<CitiesDraw*> cities_draw; // just 1 city draw, implemented as vector for flexibility
    public:
        // Constructors
        Bank(); // DONE
        // We're overloading the constructor, to keep a specific constructor to a specific extension
        Bank(std::vector<std::vector<Development*>> dev, std::vector<Noble*> nob, int pla_num); // initialize the draws by reading the game class // DONE
        Bank(std::vector<std::vector<Development*>> dev, std::vector<City*> city, int pla_num); // DONE
        Bank& operator=(const Bank& b) = default; // DONE
        // Getters
        Resources getResources(); // DONE
        std::vector<std::vector<Development*>> getBoardDevelopments(); // DONE
        std::vector<DevelopmentsDraw*> getDrawDevelopments(); // DONE
        std::vector<Noble*> getBoardNobles(); // DONE
        std::vector<NoblesDraw*> getDrawNobles(); // DONE
        std::vector<City*> getBoardCities(); // DONE
        std::vector<CitiesDraw*> getDrawCities(); // DONE
        void getBoardDevelopmentInformations(std::ostream& f= std::cout) const; // DONE
        void getBoardNobleBoardInformations(std::ostream& f= std::cout) const; // DONE
        void getBoardCityBoardInformations(std::ostream& f) const; // DONE
        void getDrawDevelopmentsInformations(std::ostream& f= std::cout) const; // DONE
        void getDrawNoblesInformations(std::ostream& f= std::cout) const; // DONE
        std::ostream& getBoardInformations(std::ostream& f= std::cout) const; // DONE

        // Setters
        void addResources(Resources res); // DONE
        void removeResources(Resources res); // DONE

        // Others
        Development* drawDevelopment(int level); // DONE
        Noble* drawNoble(); // DONE
        City* drawCity(); // DONE
        void removeBoardDevelopment(int lev, int pos); // DONE
        void insertBoardDevelopment(Development* dev, int lev, int pos); // DONE
        void removeBoardNoble(int pos); // DONE
        void insertBoardNoble(Noble* nob, int pos); // DONE
        void removeBoardCity(int pos); // DONE
        void insertBoardCity(City* city, int pos); // DONE

        // Destructors
        ~Bank();
};

#endif // BANK_H
