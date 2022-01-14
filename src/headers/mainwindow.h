#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include "views.h"
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QIcon>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QLabel;

class MainWindow: public QWidget{
        Q_OBJECT
    private:
        Controller controller;

        QHBoxLayout* final_layout; // board + buttons
        QHBoxLayout* board; // players + inside board
        QVBoxLayout* inside_board; // current player + (nobles board / cities board) + dev token board + hand

        QLabel* cur_player;

        QVBoxLayout* players;

        std::vector<QHBoxLayout*> nobles_board; // 1*5 noble board
        std::vector<QHBoxLayout*> cities_board; // 1*5 city board

        QHBoxLayout* dev_tokens_board; // developments cards + tokens board
        QVBoxLayout* developments_cards; // development draws + development board
        std::vector<QHBoxLayout*> developments_board; // 3*(1draw + 4 developments)
        QVBoxLayout* tokens_board; // 6 tokens board

        QVBoxLayout* hand; // resource hand + cards hand
        QHBoxLayout* resource_hand; // 6 resource token + 5 resource advantage token
        QHBoxLayout* cards_hand; // reserved developments + (owned nobles / owned cities)
        QHBoxLayout* reserved_development; // 3 reserved developments
        QHBoxLayout* owned_nobles; // 1 owned nobles
        QHBoxLayout* owned_cities; // 1 owned city

        QVBoxLayout* buttons; // next + cancel + pick tokens buttons
        QPushButton* next_button;
        QPushButton* cancel_button;
        QPushButton* pick_tokens_button;
        QPushButton* buy_development_button;
        QPushButton* reserve_development_button;

        Resources selected_tokens;
        Development* selected_development;
    private slots:
//        void PlaDevClick(PlayerDevelopmentView* dev);
//        void PlaNobClick(PlayerNobleView* dev);
//        void PlaCitClick(PlayerCityView* cit);
        void DevClick(DevelopmentView* dev);
//        void NobClick(NobleView* nob);
//        void CitClick(CityView* cit);
//        void DrawClick(DrawView* dra);
        void BoardTokenClick(BoardTokenView *tok);
//        void HandTokenClick(HandTokenView *tok);
        void NextButtonClick();
        void CancelButtonClick();
        void PickTokensClick();
        void BuyDevelopmentClick();
        void ReserveDevelopmentClick();
    public:
        explicit MainWindow(QString ext, QString g_name, std::vector<Player*> pla, QWidget *parent = nullptr); // DONE
        void refresh(); // DONE
        void checkTokensNumber(); // DONE
        void nextTurn(); // DONE
};

#endif // MAINWINDOW_H
