#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "bank.h"
#include "game.h"
#include "exception.h"
#include "victorywindow.h"

class Controller{
    private:
        // Attributes
        Player* current_player;
        Game* game_instance;
    public:
        // Constructors
        Controller(QString ext, QString g_name, std::vector<Player*> pla); // DONE
        // Getters
        Player* getCurrentPlayer(); // DONE
        Game* getGameInstance(); // DONE
        // Players actions
        void pick3DifferentTokens(Resources res); // DONE
        void pick2SameTokens(Resources res); // DONE
        void reserveDevelopment(Development* dev); // DONE
        void buyReservedDevelopment(Development* dev); // DONE
        void buyBoardDevelopment(Development* dev); // DONE
        void generateIAActions(); // DONE -> behavior explained in the documentation
        // End of the turn checkings
        bool verifyTokensNumber(); // DONE
        void withdrawTokens(); // DONE
        void verifyNobles(); // DONE
        void verifyCities(); // DONE
        void win(); // DONE
        time_t timeSpent();
        void nextTurn(); // DONE
        // Displayers
        void displayBoard(); // DONE
        bool buyable(Development* dev); // DONE
        // Destructors
        ~Controller();
};

#endif // CONTROLLER_H
