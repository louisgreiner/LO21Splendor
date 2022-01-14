#ifndef VIEWS_H
#define VIEWS_H

#include "card.h"
#include "draw.h"
#include "player.h"

#include "QWidget"
#include <QPushButton>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QColor>
#include <QIcon>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Views{
    public:
        Views();
};

class PlayerView: public QPushButton{
        Q_OBJECT
    private:
        const Player* player = nullptr;
        QString extension;
        QVBoxLayout* informations; // cards + resources
        QHBoxLayout* cards; // dev + nob
        QHBoxLayout* dev; // 3 reserved developments
        QHBoxLayout* nob; // 1 (or more) owned noble
        QHBoxLayout* cit; // 1 owned city
        QHBoxLayout* resources; // 6 tokens
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        PlayerView(const Player& pla, QWidget* parent = nullptr); // DONE
        explicit PlayerView(QWidget* parent = nullptr); // DONE
        void setNewPlayer(const Player& pla, const QString ext); // DONE
        void setNoPlayer(); // DONE
        const Player& getPlayer() const; // DONE
    signals:
        void ClickedPlayer(PlayerView*);
    public slots:

    private slots:
        void ClickedEvent() { emit ClickedPlayer(this); } // DONE

};

class PlayerNobleView: public QPushButton{
        Q_OBJECT
    private:
        const Noble* noble = nullptr;
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        PlayerNobleView(const Noble& nob, QWidget* parent = nullptr); // DONE
        explicit PlayerNobleView(QWidget* parent = nullptr); // DONE
        void setNewNoble(const Noble& nob); // DONE
        void setNoNoble(); // DONE
        const Noble& getNoble() const; // DONE
        bool NobleExist() const; // DONE
    signals:
        void ClickedNoble(PlayerNobleView*);
    public slots:

    private slots:
        void ClickedEvent(){ emit ClickedNoble(this); } // DONE
};

class PlayerCityView: public QPushButton{
        Q_OBJECT
    private:
        const City* city = nullptr;
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        PlayerCityView(const City& cit, QWidget* parent = nullptr); // DONE
        explicit PlayerCityView(QWidget* parent = nullptr); // DONE
        void setNewCity(const City& cit); // DONE
        void setNoCity(); // DONE
        const City& getCity() const; // DONE
        bool CityExist() const; // DONE
    signals:
        void ClickedCity(PlayerCityView*);
    public slots:

    private slots:
        void ClickedEvent(){ emit ClickedCity(this); } // DONE
};

class PlayerDevelopmentView: public QPushButton{
        Q_OBJECT
    private:
        const Development* development = nullptr;
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        PlayerDevelopmentView(const Development& dev, QWidget* parent = nullptr); // DONE
        explicit PlayerDevelopmentView(QWidget* parent = nullptr); // DONE
        void setNewDevelopment(const Development& dev); // DONE
        void setNoDevelopment(); // DONE
        const Development& getDevelopment() const; // DONE
        bool DevelopmentExist() const; // DONE
    signals:
        void ClickedDevelopment(PlayerDevelopmentView*);
    public slots:

    private slots:
        void ClickedEvent(){ emit ClickedDevelopment(this); } // DONE
};

class DevelopmentView: public QPushButton{
        Q_OBJECT
    private:
        const Development* development = nullptr;
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        DevelopmentView(const Development& dev, QWidget* parent = nullptr); // DONE
        explicit DevelopmentView(QWidget* parent = nullptr); // DONE
        void setNewDevelopment(const Development& dev); // DONE
        void setNoDevelopment(); // DONE
        const Development& getDevelopment() const; // DONE
        bool DevelopmentExist() const; // DONE
        // buyable ?
    signals:
        void ClickedDevelopment(DevelopmentView*);
    public slots:

    private slots:
        void ClickedEvent(){ emit ClickedDevelopment(this); } // DONE
};

class NobleView: public QPushButton{
        Q_OBJECT
    private:
        const Noble* noble = nullptr;
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        NobleView(const Noble& nob, QWidget* parent = nullptr); // DONE
        explicit NobleView(QWidget* parent = nullptr); // DONE
        void setNewNoble(const Noble& nob); // DONE
        void setNoNoble(); // DONE
        const Noble& getNoble() const; // DONE
        bool NobleExist() const; // DONE
    signals:
        void ClickedNoble(NobleView*);
    public slots:

    private slots:
        void ClickedEvent(){ emit ClickedNoble(this); } // DONE
};

class CityView: public QPushButton{
        Q_OBJECT
    private:
        const City* city = nullptr;
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        CityView(const City& cit, QWidget* parent = nullptr); // DONE
        explicit CityView(QWidget* parent = nullptr); // DONE
        void setNewCity(const City& cit); // DONE
        void setNoCity(); // DONE
        const City& getCity() const; // DONE
        bool CityExist() const; // DONE
        // buyable ?
    signals:
        void ClickedCity(CityView*);
    public slots:

    private slots:
        void ClickedEvent(){ emit ClickedCity(this); } // DONE
};

class DrawView: public QPushButton{
        Q_OBJECT
    private:
        const DevelopmentsDraw* development_draw = nullptr;
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        DrawView(const DevelopmentsDraw& dev_draw, QWidget* parent = nullptr); // DONE
        explicit DrawView(QWidget* parent = nullptr); // DONE
        void setNewDevelopmentsDraw(const DevelopmentsDraw& dev_draw); // DONE
        const DevelopmentsDraw& getDevelopmentsDraw() const; // DONE
        bool isEmpty() const; // DONE
    signals:
        void ClickedDraw(DrawView*);
    public slots:

    private slots:
        void ClickedEvent(){ emit ClickedDraw(this); } // DONE
};

class BoardTokenView: public QPushButton{
        Q_OBJECT
    private:
        const Resources* resources = nullptr;
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        BoardTokenView(const Resources& res, QWidget* parent = nullptr); // DONE
        explicit BoardTokenView(QWidget* parent = nullptr); // DONE
        void setNewResources(const Resources& res, int type); // DONE
        const Resources getResources() const; // DONE
    signals:
        void ClickedBoardToken(BoardTokenView*);
    private slots:
        void ClickedEvent(){ emit ClickedBoardToken(this); } // DONE
};

class HandTokenView: public QPushButton{
        Q_OBJECT
    private:
        const Resources* resources = nullptr;
        const Resources* resources_advantages = nullptr;
    protected:
        void paintEvent(QPaintEvent *event) override; // DONE
    public:
        HandTokenView(const Resources& res, QWidget* parent = nullptr); // DONE
        explicit HandTokenView(QWidget* parent = nullptr); // DONE
        void setNewResources(const Resources& res, const Resources& adv, int type); // DONE
        const Resources getResources() const; // DONE
    signals:
        void ClickedHandToken(HandTokenView*);
    private slots:
        void ClickedEvent(){ emit ClickedHandToken(this); } // DONE
};

#endif // VIEWS_H
