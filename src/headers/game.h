#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "player.h"
#include "bank.h"
#include <ctime> // https://www.programiz.com/cpp-programming/library-function/ctime/time
#include <fstream>
#include <QtXml>
#include <QTextStream>
#include <iostream>
#include <QFile>

class Game{ // singleton, non-thread safe, but we don't need it for now
    private:
        // Attributes
        QString game_name;
        QString extension;
        std::vector<std::vector<Development*>> developments;
        std::vector<Noble*> nobles;
        std::vector<City*> cities;
        Bank bank;
        std::vector<Player*> players;
        int prestige_win;
        bool last_turn;
        int turns;
        time_t global_time;
        std::vector<time_t> time_per_player;
//        std::fstream save_file; // or rather a QString to reference an XML File
        // Constructors, private to prevent direct construction calls with the "new" operator
        Game(QString ext, QString g_name, std::vector<Player*> pla); // DONE
        void loadCards(QString extension_path); // DONE
        static Game* instance_; // = singleton
    public:
        /**
        * This is the static method that controls the access to the singleton
        * instance. On the first run, it creates a singleton object and places it
        * into the static field. On subsequent runs, it returns the client existing
        * object stored in the static field.
        */
        static Game* getInstance(QString ext, QString g_name, std::vector<Player*> pla); // = constructor // DONE
        static Game* getSavedInstance(QString game_name); // = constructor from saved game file
        Game(Game& other) = delete; // not cloneable // DONE
        void operator=(const Game&) = delete; // not assignable // DONE
        // Getters
        Bank& getBank(); // DONE
        const QString getGameName() const; // DONE
        const QString getExtension() const; // DONE
        std::vector<std::vector<Development*>> getDevelopments() const; // DONE
        std::vector<Noble*> getNobles() const; // DONE
        std::vector<City*> getCities() const;
        std::vector<Player*> getPlayers(); // DONE
        Player* findUserById(int own); // DONE
        int getPrestigeWin() const; // DONE
        bool getLastTurn() const;
        void setLastTurn(bool var);
        int getTurns() const; // DONE
        time_t getGlobalTime() const; // DONE
        time_t getTimePerPlayer(int id) const; // DONE
        // Others
        void incrementTurns(); // DONE
        void saveGame();
        void savePlayersStats();
        // Destructor
        ~Game();
};

#endif // GAME_H
