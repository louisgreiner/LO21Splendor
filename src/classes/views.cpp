#include "./headers/views.h"

Views::Views(){

}

// Class PlayerView
    PlayerView::PlayerView(const Player& pla, QWidget* parent): QPushButton(parent), player(pla.FactoryMethod()){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(300,200);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(false);
    }
    PlayerView::PlayerView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(300,200);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(false);
    }
    void PlayerView::setNewPlayer(const Player& pla, const QString ext){
        setChecked(false);
        player = &pla;
        extension = ext;

        informations = new QVBoxLayout(this);

        cards = new QHBoxLayout;
        // set reserved developments
        dev = new QHBoxLayout();
        for(size_t i=0; i<3; i++){
            PlayerDevelopmentView* temp_dev = new PlayerDevelopmentView;
            dev->addWidget(temp_dev);
            if(i < player->FactoryMethod()->getInventory().getReservedDevelopments().size()){
                // connect
                temp_dev->setNewDevelopment(*player->FactoryMethod()->getInventory().getReservedDevelopments()[i]);
            }
            else{
                temp_dev->setNoDevelopment();
            }
        }
        cards->addLayout(dev);

        if(extension == "classic"){
            // set owned nobles
            nob = new QHBoxLayout();
            if(player->FactoryMethod()->getInventory().getOwnedNobles().size() != 0){
                for(size_t i=0; i<player->FactoryMethod()->getInventory().getOwnedNobles().size(); i++){
                    PlayerNobleView* temp_nob = new PlayerNobleView;
                    nob->addWidget(temp_nob);
                    // connect
                    temp_nob->setNewNoble(*player->FactoryMethod()->getInventory().getOwnedNobles()[i]);
                }
            }
            else{
                PlayerNobleView* temp_nob = new PlayerNobleView;
                nob->addWidget(temp_nob);
                temp_nob->setNoNoble();
            }
            cards->addLayout(nob);
        }
        else if(extension == "cities of splendor"){
            // set owned cities
            cit = new QHBoxLayout();
            if(player->FactoryMethod()->getInventory().getOwnedCities().size() != 0){
                for(size_t i=0; i<player->FactoryMethod()->getInventory().getOwnedCities().size(); i++){
                    PlayerCityView* temp_cit = new PlayerCityView;
                    cit->addWidget(temp_cit);
                    // connect
                    temp_cit->setNewCity(*player->FactoryMethod()->getInventory().getOwnedCities()[i]);
                }
            }
            else{
                PlayerCityView* temp_cit = new PlayerCityView;
                cit->addWidget(temp_cit);
                temp_cit->setNoCity();
            }
            cards->addLayout(cit);
        }

        informations->addLayout(cards);

        // set resources and advantage resource tokens
        resources = new QHBoxLayout;
        for(size_t i=0; i<5; i++){
            HandTokenView* temp_tok = new HandTokenView;
            resources->addWidget(temp_tok);
//            connect(temp_tok, SIGNAL(ClickedHandToken(HandTokenView*)), this, SLOT(HandTokenClick(HandTokenView*)));
            temp_tok->setNewResources(player->FactoryMethod()->getInventory().getResources(),player->FactoryMethod()->getInventory().getResourceAdvantages(),i);
        }
        HandTokenView* temp_tok = new HandTokenView;
        resources->addWidget(temp_tok);
//        connect(temp_tok, SIGNAL(ClickedHandToken(HandTokenView*)), this, SLOT(HandTokenClick(HandTokenView*)));
        temp_tok->setNewResources(player->FactoryMethod()->getInventory().getResources(),player->FactoryMethod()->getInventory().getResourceAdvantages(),5);
        informations->addLayout(resources);

//        setLayout(informations);

        update();
    }
    void PlayerView::setNoPlayer(){
        player = nullptr;
        setCheckable(false);

        QPalette pal = palette();
        pal.setColor(QPalette::Base, QColor(200, 200, 200, 127));
        setPalette(pal);

        update();
    }
    const Player& PlayerView::getPlayer() const{
        return *player;
    }
    void PlayerView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        // set player's name
        painter.drawText(QPoint(10,15),player->FactoryMethod()->getName());

        // set prestige points
        painter.drawText(QPoint(230,15),"Prestige : " + QString::number(player->FactoryMethod()->getPrestige()));
    }

// Class PlayerDevelopmentView
    PlayerDevelopmentView::PlayerDevelopmentView(const Development& dev, QWidget* parent): QPushButton(parent), development(dev.FactoryMethod()){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(60,84);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(false);
    }
    PlayerDevelopmentView::PlayerDevelopmentView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(60,84);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(false);
    }
    void PlayerDevelopmentView::setNewDevelopment(const Development& dev){
        setCheckable(false);
        setChecked(false);
        development = &dev;
        // set color background relative to advantage of resources given
        QPalette pal = palette();
        if(development->getAdvantages().getDiamond()) pal.setColor(QPalette::Base, QColor(214, 255, 244, 127));
        else if(development->getAdvantages().getSapphire()) pal.setColor(QPalette::Base, QColor(6, 32 , 73, 127));
        else if(development->getAdvantages().getEmerald()) pal.setColor(QPalette::Base, QColor(31, 78, 47, 127));
        else if(development->getAdvantages().getRuby()) pal.setColor(QPalette::Base, QColor(88, 7, 37, 127));
        else if(development->getAdvantages().getOnyx()) pal.setColor(QPalette::Base, QColor(35, 38, 39, 127));
        setPalette(pal);
        update();
    }
    void PlayerDevelopmentView::setNoDevelopment(){
        development = nullptr;
        setCheckable(false);

        QPalette pal = palette();
        pal.setColor(QPalette::Base, QColor(200, 200, 200, 127));
        setPalette(pal);

        update();
    }
    const Development& PlayerDevelopmentView::getDevelopment() const{
        return *development;
    }
    bool PlayerDevelopmentView::DevelopmentExist() const{
        return development != nullptr;
    }
    void PlayerDevelopmentView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        if(development == nullptr){
            painter.drawText(QPoint(10,42), "No dev");
            return;
        }

        // set image relative to advantage of resources given
//         if(development->getAdvantages().getDiamond()) painter.drawText(QPoint(50,15),"Diamond");
//         if(development->getAdvantages().getSapphire()) painter.drawText(QPoint(50,15),"Sapphire");
//         if(development->getAdvantages().getEmerald()) painter.drawText(QPoint(53,15),"Emerald");
//         if(development->getAdvantages().getRuby()) painter.drawText(QPoint(68,15),"Ruby");
//         if(development->getAdvantages().getOnyx()) painter.drawText(QPoint(68,15),"Onyx");

        // set prestige points given
        painter.drawText(QPoint(10,15), "p=" +  QString::number(development->getPrestige()));
        painter.drawText(QPoint(10,30), "id=" +  QString::number(development->getId()));

        // set resources cost
        if(development->getCost().getDiamond() != 0) painter.drawText(QPoint(10,50),"d=" + QString::number(development->getCost().getDiamond()));
        if(development->getCost().getSapphire() != 0) painter.drawText(QPoint(10,65),"s=" + QString::number(development->getCost().getSapphire()));
        if(development->getCost().getEmerald() != 0) painter.drawText(QPoint(10,80),"e=" + QString::number(development->getCost().getEmerald()));
        if(development->getCost().getRuby() != 0) painter.drawText(QPoint(35,57),"r=" + QString::number(development->getCost().getRuby()));
        if(development->getCost().getOnyx() != 0) painter.drawText(QPoint(35,72),"o=" + QString::number(development->getCost().getOnyx()));
    }

// Class PlayerNobleView
    PlayerNobleView::PlayerNobleView(const Noble& nob, QWidget* parent): QPushButton(parent), noble(nob.FactoryMethod()){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(60,84);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(false);
    }
    PlayerNobleView::PlayerNobleView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(60,84);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(false);
    }
    void PlayerNobleView::setNewNoble(const Noble& nob){
        setCheckable(false);
        setChecked(false);
        noble = &nob;
        update();
    }
    void PlayerNobleView::setNoNoble(){
        noble = nullptr;
        setCheckable(false);

        QPalette pal = palette();
        pal.setColor(QPalette::Base, QColor(200, 200, 200, 127));
        setPalette(pal);

        update();
    }
    const Noble& PlayerNobleView::getNoble() const{
        return *noble;
    }
    bool PlayerNobleView::NobleExist() const{
        return noble != nullptr;
    }
    void PlayerNobleView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        if(noble == nullptr){
            painter.drawText(QPoint(10,42), "No nob");
            return;
        }

        // set image relative to advantage of resources given
//         if(development->getAdvantages().getDiamond()) painter.drawText(QPoint(50,15),"Diamond");
//         if(development->getAdvantages().getSapphire()) painter.drawText(QPoint(50,15),"Sapphire");
//         if(development->getAdvantages().getEmerald()) painter.drawText(QPoint(53,15),"Emerald");
//         if(development->getAdvantages().getRuby()) painter.drawText(QPoint(68,15),"Ruby");
//         if(development->getAdvantages().getOnyx()) painter.drawText(QPoint(68,15),"Onyx");

        // set prestige points given
        painter.drawText(QPoint(10,15), "p=" + QString::number(noble->getPrestige()));
        painter.drawText(QPoint(10,30), "id=" +  QString::number(noble->getId()));
        painter.drawText(QPoint(15,45), "NOBLE");

        // set resources cost
//        if(noble->getCost().getDiamond() != 0) painter.drawText(QPoint(10,105),"d=" + QString::number(noble->getCost().getDiamond()));
//        if(noble->getCost().getSapphire() != 0) painter.drawText(QPoint(10,120),"s=" + QString::number(noble->getCost().getSapphire()));
//        if(noble->getCost().getEmerald() != 0) painter.drawText(QPoint(10,135),"e=" + QString::number(noble->getCost().getEmerald()));
//        if(noble->getCost().getRuby() != 0) painter.drawText(QPoint(35,112),"r=" + QString::number(noble->getCost().getRuby()));
//        if(noble->getCost().getOnyx() != 0) painter.drawText(QPoint(35,127),"o=" + QString::number(noble->getCost().getOnyx()));
    }

// Class PlayerCityView
    PlayerCityView::PlayerCityView(const City& cit, QWidget* parent): QPushButton(parent), city(cit.FactoryMethod()){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(60,84);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(false);
    }
    PlayerCityView::PlayerCityView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(60,84);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(false);
    }
    void PlayerCityView::setNewCity(const City& cit){
        setCheckable(false);
        setChecked(false);
        city = &cit;
        update();
    }
    void PlayerCityView::setNoCity(){
        city = nullptr;
        setCheckable(false);

        QPalette pal = palette();
        pal.setColor(QPalette::Base, QColor(200, 200, 200, 127));
        setPalette(pal);

        update();
    }
    const City& PlayerCityView::getCity() const{
        return *city;
    }
    bool PlayerCityView::CityExist() const{
        return city != nullptr;
    }
    void PlayerCityView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        if(city == nullptr){
            painter.drawText(QPoint(10,42), "No cit");
            return;
        }

        // set prestige points given
        painter.drawText(QPoint(10,15), "id=" +  QString::number(city->getId()));
        painter.drawText(QPoint(15,47), "CITY");

    }

// Class DevelopmentView
    DevelopmentView::DevelopmentView(const Development& dev, QWidget* parent): QPushButton(parent), development(dev.FactoryMethod()){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(100,140);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    DevelopmentView::DevelopmentView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(100,140);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    void DevelopmentView::setNewDevelopment(const Development& dev){
        setCheckable(true);
        setChecked(false);
        development = &dev;
        // set color background relative to advantage of resources given
        QPalette pal = palette();
        if(development->getAdvantages().getDiamond()) pal.setColor(QPalette::Base, QColor(214, 255, 244, 127));
        else if(development->getAdvantages().getSapphire()) pal.setColor(QPalette::Base, QColor(6, 32 , 73, 127));
        else if(development->getAdvantages().getEmerald()) pal.setColor(QPalette::Base, QColor(31, 78, 47, 127));
        else if(development->getAdvantages().getRuby()) pal.setColor(QPalette::Base, QColor(88, 7, 37, 127));
        else if(development->getAdvantages().getOnyx()) pal.setColor(QPalette::Base, QColor(35, 38, 39, 127));
        setPalette(pal);
        update();
    }
    void DevelopmentView::setNoDevelopment(){
        development = nullptr;
        setCheckable(false);

        QPalette pal = palette();
        pal.setColor(QPalette::Base, QColor(200, 200, 200, 127));
        setPalette(pal);

        update();
    }
    const Development& DevelopmentView::getDevelopment() const{
        return *development;
    }
    bool DevelopmentView::DevelopmentExist() const{
        return development != nullptr;
    }
    void DevelopmentView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        if(development == nullptr){
            painter.drawText(QPoint(5,70), "No development");
            return;
        }

        // set image relative to advantage of resources given
        if(development->getAdvantages().getDiamond()) painter.drawText(QPoint(50,15),"Diamond");
        else if(development->getAdvantages().getSapphire()) painter.drawText(QPoint(50,15),"Sapphire");
        else if(development->getAdvantages().getEmerald()) painter.drawText(QPoint(53,15),"Emerald");
        else if(development->getAdvantages().getRuby()) painter.drawText(QPoint(68,15),"Ruby");
        else if(development->getAdvantages().getOnyx()) painter.drawText(QPoint(68,15),"Onyx");

        // set prestige points given
        painter.drawText(QPoint(10,15), "p=" +  QString::number(development->getPrestige()));
        painter.drawText(QPoint(10,30), "id=" +  QString::number(development->getId()));

        // set resources cost
        if(development->getCost().getDiamond() != 0) painter.drawText(QPoint(10,105),"d=" + QString::number(development->getCost().getDiamond()));
        if(development->getCost().getSapphire() != 0) painter.drawText(QPoint(10,120),"s=" + QString::number(development->getCost().getSapphire()));
        if(development->getCost().getEmerald() != 0) painter.drawText(QPoint(10,135),"e=" + QString::number(development->getCost().getEmerald()));
        if(development->getCost().getRuby() != 0) painter.drawText(QPoint(35,112),"r=" + QString::number(development->getCost().getRuby()));
        if(development->getCost().getOnyx() != 0) painter.drawText(QPoint(35,127),"o=" + QString::number(development->getCost().getOnyx()));
    }

// Class NobleView
    NobleView::NobleView(const Noble& nob, QWidget* parent): QPushButton(parent), noble(nob.FactoryMethod()){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(100,140);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    NobleView::NobleView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(100,140);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    void NobleView::setNewNoble(const Noble& nob){
        setCheckable(true);
        setChecked(false);
        noble = &nob;
        update();
    }
    void NobleView::setNoNoble(){
        noble = nullptr;
        setCheckable(false);

        QPalette pal = palette();
        pal.setColor(QPalette::Base, QColor(200, 200, 200, 127));
        setPalette(pal);

        update();
    }
    const Noble& NobleView::getNoble() const{
        return *noble;
    }
    bool NobleView::NobleExist() const{
        return noble != nullptr;
    }
    void NobleView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        if(noble == nullptr){
            painter.drawText(QPoint(25,70), "No noble");
            return;
        }

        // set image relative to advantage of resources given
        painter.drawText(QPoint(30,60), "NOBLE");

        // set prestige points given
        painter.drawText(QPoint(10,15), "p=" + QString::number(noble->getPrestige()));

        // set resources cost
        if(noble->getCost().getDiamond() != 0) painter.drawText(QPoint(10,105),"d=" + QString::number(noble->getCost().getDiamond()));
        if(noble->getCost().getSapphire() != 0) painter.drawText(QPoint(10,120),"s=" + QString::number(noble->getCost().getSapphire()));
        if(noble->getCost().getEmerald() != 0) painter.drawText(QPoint(10,135),"e=" + QString::number(noble->getCost().getEmerald()));
        if(noble->getCost().getRuby() != 0) painter.drawText(QPoint(35,112),"r=" + QString::number(noble->getCost().getRuby()));
        if(noble->getCost().getOnyx() != 0) painter.drawText(QPoint(35,127),"o=" + QString::number(noble->getCost().getOnyx()));
    }

// Class CityView
    CityView::CityView(const City& cit, QWidget* parent): QPushButton(parent), city(cit.FactoryMethod()){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(100,140);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    CityView::CityView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(100,140);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    void CityView::setNewCity(const City& cit){
        setCheckable(true);
        setChecked(false);
        city = &cit;
        update();
    }
    void CityView::setNoCity(){
        city = nullptr;
        setCheckable(false);

        QPalette pal = palette();
        pal.setColor(QPalette::Base, QColor(200, 200, 200, 127));
        setPalette(pal);

        update();
    }
    const City& CityView::getCity() const{
        return *city;
    }
    bool CityView::CityExist() const{
        return city != nullptr;
    }
    void CityView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        if(city == nullptr){
            painter.drawText(QPoint(25,70), "No city");
            return;
        }

        // set image relative to advantage of resources given
        painter.drawText(QPoint(30,60), "CITY");

        // set points needed before getting the city
        painter.drawText(QPoint(10,15), "p=" + QString::number(city->getPoints()));

        // set resources cost
        if(city->getCost().getDiamond() != 0) painter.drawText(QPoint(10,105),"d=" + QString::number(city->getCost().getDiamond()));
        if(city->getCost().getSapphire() != 0) painter.drawText(QPoint(10,120),"s=" + QString::number(city->getCost().getSapphire()));
        if(city->getCost().getEmerald() != 0) painter.drawText(QPoint(10,135),"e=" + QString::number(city->getCost().getEmerald()));
        if(city->getCost().getRuby() != 0) painter.drawText(QPoint(35,112),"r=" + QString::number(city->getCost().getRuby()));
        if(city->getCost().getOnyx() != 0) painter.drawText(QPoint(35,127),"o=" + QString::number(city->getCost().getOnyx()));
    }

// Class DrawView
    DrawView::DrawView(const DevelopmentsDraw& dev_draw, QWidget* parent): QPushButton(parent), development_draw(dev_draw.FactoryMethod()){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(100,140);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    DrawView::DrawView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(100,140);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    void DrawView::setNewDevelopmentsDraw(const DevelopmentsDraw& dev_draw){
        setCheckable(false);
        setChecked(false);
        development_draw = &dev_draw;
        // set color background relative to level of the draw
        QPalette pal = palette();
        if(development_draw->FactoryMethod()->getLevel() == 0) pal.setColor(QPalette::Base, QColor(22, 184, 78, 127));
        else if(development_draw->FactoryMethod()->getLevel() == 1) pal.setColor(QPalette::Base, QColor(255, 255, 0, 127));
        else if(development_draw->FactoryMethod()->getLevel() == 2) pal.setColor(QPalette::Base, QColor(240, 0, 32, 127));
        setPalette(pal);
        update();
    }
    const DevelopmentsDraw& DrawView::getDevelopmentsDraw() const{
        return *development_draw;
    }
    bool DrawView::isEmpty() const{
        return development_draw->isEmpty();
    }
    void DrawView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        // set number of cards remaining in the draw
        painter.drawText(QPoint(18,70), "cards left=" + QString::number(development_draw->FactoryMethod()->getCardsLeft()));
    }

// Class BoardTokenView
    BoardTokenView::BoardTokenView(const Resources& res, QWidget* parent): QPushButton(parent), resources(&res){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(40,40);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    BoardTokenView::BoardTokenView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(40,40);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    void BoardTokenView::setNewResources(const Resources& res, int type){
        setCheckable(true);
        setChecked(false);

        if(type == 0) resources = new Resources(res.FactoryMethod()->getDiamond(),0,0,0,0,0);
        else if(type == 1) resources = new Resources(0,res.FactoryMethod()->getSapphire(),0,0,0,0);
        else if(type == 2) resources = new Resources(0,0,res.FactoryMethod()->getEmerald(),0,0,0);
        else if(type == 3) resources = new Resources(0,0,0,res.FactoryMethod()->getRuby(),0,0);
        else if(type == 4) resources = new Resources(0,0,0,0,res.FactoryMethod()->getOnyx(),0);
        else if(type == 5) resources = new Resources(0,0,0,0,0,res.FactoryMethod()->getGold());

        // set color background relative to the resource of the token
        QPalette pal = palette();
        if(resources->FactoryMethod()->getDiamond()) pal.setColor(QPalette::Base, QColor(214, 255, 244, 127));
        else if(resources->FactoryMethod()->getSapphire()) pal.setColor(QPalette::Base, QColor(6, 32 , 73, 127));
        else if(resources->FactoryMethod()->getEmerald()) pal.setColor(QPalette::Base, QColor(31, 78, 47, 127));
        else if(resources->FactoryMethod()->getRuby()) pal.setColor(QPalette::Base, QColor(88, 7, 37, 127));
        else if(resources->FactoryMethod()->getOnyx()) pal.setColor(QPalette::Base, QColor(35, 38, 39, 127));
        else if(resources->FactoryMethod()->getGold()) pal.setColor(QPalette::Base, QColor(255, 215, 0, 127));
        else pal.setColor(QPalette::Base, QColor(100, 100, 100, 127));
        setPalette(pal);
        update();
    }
    const Resources BoardTokenView::getResources() const{
        return *resources;
    }
    void BoardTokenView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        // set number of tokens
        if(resources->FactoryMethod()->getDiamond()) painter.drawText(QPoint(9,20),"d="+QString::number(resources->FactoryMethod()->getDiamond()));
        else if(resources->FactoryMethod()->getSapphire()) painter.drawText(QPoint(9,20),"s="+QString::number(resources->FactoryMethod()->getSapphire()));
        else if(resources->FactoryMethod()->getEmerald()) painter.drawText(QPoint(9,20),"e="+QString::number(resources->FactoryMethod()->getEmerald()));
        else if(resources->FactoryMethod()->getRuby()) painter.drawText(QPoint(9,20),"r="+QString::number(resources->FactoryMethod()->getRuby()));
        else if(resources->FactoryMethod()->getOnyx()) painter.drawText(QPoint(9,20),"o="+QString::number(resources->FactoryMethod()->getOnyx()));
        else if(resources->FactoryMethod()->getGold()) painter.drawText(QPoint(9,20),"g="+QString::number(resources->FactoryMethod()->getGold()));
        else painter.drawText(QPoint(17,20),"0");

        if(resources->FactoryMethod()->getSum() == 0) setCheckable(false);
        else setCheckable(true);
    }

// Class HandTokenView
    HandTokenView::HandTokenView(const Resources& res, QWidget* parent): QPushButton(parent), resources(&res){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(40,40);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    HandTokenView::HandTokenView(QWidget* parent): QPushButton(parent){
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
        setFixedSize(40,40);
        connect(this,SIGNAL(clicked()), this, SLOT(ClickedEvent()));
        setCheckable(true);
    }
    void HandTokenView::setNewResources(const Resources& res, const Resources& adv, int type){
        setCheckable(true);
        setChecked(false);

        // set attributes and set color background relative to the resource of the token
        QPalette pal = palette();
        if(type == 0){
            resources = new Resources(res.FactoryMethod()->getDiamond(),-1,-1,-1,-1,-1);
            resources_advantages = new Resources(adv.FactoryMethod()->getDiamond(),-1,-1,-1,-1,-1);
            pal.setColor(QPalette::Base, QColor(214, 255, 244, 127));
        }
        else if(type == 1){
            resources = new Resources(-1,res.FactoryMethod()->getSapphire(),-1,-1,-1,-1);
            resources_advantages = new Resources(-1,adv.FactoryMethod()->getSapphire(),-1,-1,-1,-1);
            pal.setColor(QPalette::Base, QColor(6, 32 , 73, 127));
        }
        else if(type == 2){
            resources = new Resources(-1,-1,res.FactoryMethod()->getEmerald(),-1,-1,-1);
            resources_advantages = new Resources(-1,-1,adv.FactoryMethod()->getEmerald(),-1,-1,-1);
            pal.setColor(QPalette::Base, QColor(31, 78, 47, 127));
        }
        else if(type == 3){
            resources = new Resources(-1,-1,-1,res.FactoryMethod()->getRuby(),-1,-1);
            resources_advantages = new Resources(-1,-1,-1,adv.FactoryMethod()->getRuby(),-1,-1);
            pal.setColor(QPalette::Base, QColor(88, 7, 37, 127));
        }
        else if(type == 4){
            resources = new Resources(-1,-1,-1,-1,res.FactoryMethod()->getOnyx(),-1);
            resources_advantages = new Resources(-1,-1,-1,-1,adv.FactoryMethod()->getOnyx(),-1);
            pal.setColor(QPalette::Base, QColor(35, 38, 39, 127));
        }
        else if(type == 5){
            resources = new Resources(-1,-1,-1,-1,-1,res.FactoryMethod()->getGold());
            resources_advantages = new Resources(-1,-1,-1,-1,-1,adv.FactoryMethod()->getGold());
            pal.setColor(QPalette::Base, QColor(255, 215, 0, 127));
        }
        setPalette(pal);
        update();
    }
    const Resources HandTokenView::getResources() const{
        return *resources;
    }
    void HandTokenView::paintEvent(QPaintEvent* /* event */){
        QPainter painter(this);

        // set number of tokens
        if(resources->FactoryMethod()->getDiamond() != -1) painter.drawText(QPoint(9,20),QString::number(resources->FactoryMethod()->getDiamond()) + " / " + QString::number(resources_advantages->FactoryMethod()->getDiamond()));
        else if(resources->FactoryMethod()->getSapphire() != -1) painter.drawText(QPoint(9,20),QString::number(resources->FactoryMethod()->getSapphire()) + " / " + QString::number(resources_advantages->FactoryMethod()->getSapphire()));
        else if(resources->FactoryMethod()->getEmerald() != -1) painter.drawText(QPoint(9,20),QString::number(resources->FactoryMethod()->getEmerald()) + " / " + QString::number(resources_advantages->FactoryMethod()->getEmerald()));
        else if(resources->FactoryMethod()->getRuby() != -1) painter.drawText(QPoint(9,20),QString::number(resources->FactoryMethod()->getRuby()) + " / " + QString::number(resources_advantages->FactoryMethod()->getRuby()));
        else if(resources->FactoryMethod()->getOnyx() != -1) painter.drawText(QPoint(9,20),QString::number(resources->FactoryMethod()->getOnyx()) + " / " + QString::number(resources_advantages->FactoryMethod()->getOnyx()));
        else if(resources->FactoryMethod()->getGold() != -1) painter.drawText(QPoint(17,20),QString::number(resources->FactoryMethod()->getGold()));
    }
