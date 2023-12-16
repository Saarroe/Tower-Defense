#ifndef GAME_ENGINE_CPP
#define GAME_ENGINE_CPP


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QtGui>
#include <QList>
#include <QPushButton>
#include <iostream>
#include <QPixmap>
#include <QString>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QGraphicsEllipseItem>
#include <QLineF>
#include <QPointF>
#include <QGridLayout>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "game_engine.hpp"
#include "basic_shooter.hpp"
#include "defense.hpp"
#include "red.hpp"
#include "blue.hpp"
#include "silver.hpp"
#include "black.hpp"
#include "final_boss.hpp"
#include "fast_shooter.hpp"
#include "sniper_shooter.hpp"
#include "freezer_shooter.hpp"
#include "armor_balloon.hpp"

// constructor for the game
Game_engine::Game_engine(QString map_file) : map_(Map(10,10)), money_(10), health_(1), tower_toplaced(nullptr), level_counter(1), wave_balloons_(0){
    scene = new QGraphicsScene();
    setScene(scene);
    // Set the size of the window
    int sceneWidth = 1000;
    int sceneHeight = 700;

    // Set the scene rectangle to define the visible area
    scene->setSceneRect(0,0, sceneWidth, sceneHeight);
    setFixedSize(sceneWidth,sceneHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // find path filename
    QString pathfile = ":/maps/"+map_file;
    map_.read_path(pathfile);
    // init map:
    this->init_map();

    // Add infobox for  showing money and health
    moneyText = new QGraphicsTextItem();
    levelText = new QGraphicsTextItem();
    balloonsText = new QGraphicsTextItem();
    infoText = new QGraphicsTextItem();

    QString money = QString::number(money_);
    QString levels = QString::number(level_counter);
    QString balloons_left = QString::number(wave_balloons_.size());

    moneyText->setPlainText("Money: "+money);
    levelText->setPlainText("Level: "+levels);
    balloonsText->setPlainText("Balloons left: "+balloons_left);
    infoText->setPlainText("Welcome to tower defense game");

    moneyText->setPos(0,600);
    levelText->setPos(150,600);
    balloonsText->setPos(300,600);
    infoText->setPos(625,25);

    moneyText->setFont(QFont("Arial", 18));
    levelText->setFont(QFont("Arial", 18));
    balloonsText->setFont(QFont("Arial", 18));
    infoText->setFont(QFont("Arial", 12));

    scene->addItem(moneyText);
    scene->addItem(levelText);
    scene->addItem(balloonsText);
    scene->addItem(infoText);

    // Create a gridlayout where to put all relevant buttons on the right side of the map
    QGridLayout *gridLayout = new QGridLayout(this);

    // Create buttons or other UI elements on the right side
    QPushButton *button_startwave = new QPushButton("New wave", this);
    QPushButton *button_exit = new QPushButton("Exit", this);
    QPushButton *basic_shooter_btn = new QPushButton("Basic (5)", this);
    QPushButton *fast_shooter_btn = new QPushButton("Fast (10)", this);
    QPushButton *sniper_shooter_btn = new QPushButton("Sniper (5)", this);
    QPushButton *freezer_shooter_btn = new QPushButton("Freezer (8)", this);
    QPushButton *sell_tower_btn = new QPushButton("Sell tower", this);
    QPushButton *uppgrade_tower_btn = new QPushButton("Uppgrade tower (5)", this);

    QPixmap pixmap(":/pictures/tower.png");
    QPixmap pixmap_fast(":/pictures/castle.png");
    QPixmap pixmap_sniper(":/pictures/sniper.png");
    QPixmap pixmap_freezer(":/pictures/high.png");

    QIcon icon(pixmap);
    QIcon icon_fast(pixmap_fast);
    QIcon icon_sniper(pixmap_sniper);
    QIcon icon_freezer(pixmap_freezer);

    basic_shooter_btn->setIcon(icon);
    fast_shooter_btn->setIcon(icon_fast);
    sniper_shooter_btn->setIcon(icon_sniper);
    freezer_shooter_btn->setIcon(icon_freezer);

    button_startwave->setFixedSize(300, 60);
    button_exit->setFixedSize(300, 60);
    uppgrade_tower_btn->setFixedSize(130,60);
    sell_tower_btn->setFixedSize(130, 60);
    basic_shooter_btn->setFixedSize(130, 60);
    fast_shooter_btn->setFixedSize(130, 60);
    sniper_shooter_btn->setFixedSize(130, 60);
    freezer_shooter_btn->setFixedSize(130, 60);

    connect(fast_shooter_btn, SIGNAL(clicked()), this, SLOT(on_button_fast_shooter_clicked()));
    connect(button_startwave, SIGNAL(clicked()), this, SLOT(on_button_startwave_clicked()));
    connect(button_exit, SIGNAL(clicked()), this, SLOT(on_button_exit_clicked()));
    connect(basic_shooter_btn, SIGNAL(clicked()), this, SLOT(on_button_basic_shooter_clicked()));
    connect(sniper_shooter_btn, SIGNAL(clicked()), this, SLOT(on_button_sniper_shooter_clicked()));
    connect(freezer_shooter_btn, SIGNAL(clicked()), this, SLOT(on_button_freezer_shooter_clicked()));
    connect(sell_tower_btn, SIGNAL(clicked()), this, SLOT(on_button_sell_tower_clicked()));
    connect(uppgrade_tower_btn, SIGNAL(clicked()), this, SLOT(on_button_uppgrade_tower_clicked()));

    gridLayout->addWidget(button_startwave, 0, 0, 1, 2);
    gridLayout->addWidget(basic_shooter_btn, 1, 0);
    gridLayout->addWidget(sniper_shooter_btn, 2, 0);
    gridLayout->addWidget(freezer_shooter_btn, 2, 1);
    gridLayout->addWidget(fast_shooter_btn, 1, 1);
    gridLayout->addWidget(uppgrade_tower_btn, 3, 0);
    gridLayout->addWidget(sell_tower_btn, 3, 1);
    gridLayout->addWidget(button_exit, 4, 0, 1, 2);

    gridLayout->setAlignment(Qt::AlignRight);
    gridLayout->setSpacing(25);

    this->setStyleSheet("background-color: lightblue;");

 //set the current playerstate to idle
    changePlayerState(Idle);

    // read levels
    const QString levelfile = ":/text/levels.txt";
    this->read_levels(levelfile);
}

void Game_engine::changePlayerState(PlayerState newState) {
    currentPlayerState= newState;
}

void Game_engine::updateMoneybox(){
    QString money = QString::number(money_);
    moneyText->setPlainText("Money: "+money);
}
void Game_engine::change_infobox(const QString& newText){
    infoText->setPlainText(newText);
}

void Game_engine::updatelevelbox(){
    QString levels = QString::number(level_counter);
    levelText->setPlainText("Level: "+levels);
}

void Game_engine::update_balloon_left_box(){
    QString balloons_left = QString::number(wave_balloons_.size());
    balloonsText->setPlainText("Balloons left: "+balloons_left);
}
QVector<Balloon*> Game_engine::get_balloons(){return balloons_;}

// destructor
Game_engine::~Game_engine(){
    delete timer_spawn;
    delete moneyText;
    delete levelText;
    delete balloonsText;
    delete infoText;
    if (tower_toplaced){
        delete tower_toplaced;
    }
    if (!towers.isEmpty()){
        for (auto tower:towers){
            delete tower;
        }
    }
    if (!balloons_.isEmpty()){
        for (auto tower:balloons_){
            delete tower;
        }
    }
    scene->clear();
    delete scene;

}

void Game_engine::init_map(){

    QVector<QVector<Map_tile>>& grid = map_.get_grid();
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            // Create a MapTileGraphics object for each tile in map

            MapTileGraphics *ui_tile = new MapTileGraphics(grid[i][j], j, i);

            //ui_tile->setPos(j * 60, i * 60); // Adjust the position as needed
            scene->addItem(ui_tile);

        }
    }
}

void Game_engine::read_levels(const QString filename){

    QFile file(filename);

    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::cout << "file not found" << std::endl;
    }else{
        QTextStream in(&file);

        QVector<QString> wave;

        while (!in.atEnd()){
            QString line = in.readLine();
            if (line.isEmpty()){
                all_waves_.append(wave);
                wave.clear();
            }else{
                wave.append(line);
            }
        }

    }
}

void Game_engine::on_button_startwave_clicked(){

    if (currentPlayerState == Idle){
        infoText->setPlainText("New level started");
        if (balloons_.isEmpty() && wave_balloons_.isEmpty()){

            if (!all_waves_.isEmpty()){
                changePlayerState(WaveGoing);
                wave_balloons_ = all_waves_.takeFirst();
                // timer sending balloons to the map
                timer_spawn = new QTimer(this);
                connect(timer_spawn, &QTimer::timeout, this, &Game_engine::spawnBalloon);
                timer_spawn->start(1000);
                if (!towers.isEmpty()){
                    for (auto tower:towers){
                        tower->connect_timer();
                    }
                }else{
                    std::cout << "No towers" << std::endl;
                }

            }else{
                std::cout << "No more waves " << std::endl;
            }

        }else{
            std::cout << "something wrong balloons exist already" << std::endl;
        }
    }else{
        infoText->setPlainText("Level already in progress");
    }
}
void Game_engine::Boss_destroyed(QPointF position, QVector<QString> path_, int counter){

    Balloon* newballoon = new Armor(path_);
    Balloon* newballoon_2 = new Silver(path_);
    Balloon* newballoon_3 = new Red(path_);
    Balloon* newballoon_4 = new Blue(path_);
    Balloon* newballoon_5 = new Black(path_);

    newballoon->set_counter(counter);
    newballoon_2->set_counter(counter);
    newballoon_3->set_counter(counter);
    newballoon_4->set_counter(counter);
    newballoon_5->set_counter(counter);

    balloons_.append(newballoon);
    balloons_.append(newballoon_2);
    balloons_.append(newballoon_3);
    balloons_.append(newballoon_4);
    balloons_.append(newballoon_5);

    newballoon->setPos(position.x(), position.y());
    scene->addItem(newballoon);

    newballoon_2->setPos(position.x(), position.y());
    scene->addItem(newballoon_2);

    newballoon_3->setPos(position.x(), position.y());
    scene->addItem(newballoon_3);

    newballoon_4->setPos(position.x(), position.y());
    scene->addItem(newballoon_4);

    newballoon_5->setPos(position.x(), position.y());
    scene->addItem(newballoon_5);

    // conncet signal to know when the balloons are destoryed
    connect(newballoon, &Balloon::aboutToBeDestroyed, this, &Game_engine::removeDestroyedBalloon);
    connect(newballoon_2, &Balloon::aboutToBeDestroyed, this, &Game_engine::removeDestroyedBalloon);
    connect(newballoon_3, &Balloon::aboutToBeDestroyed, this, &Game_engine::removeDestroyedBalloon);
    connect(newballoon_4, &Balloon::aboutToBeDestroyed, this, &Game_engine::removeDestroyedBalloon);
    connect(newballoon_5, &Balloon::aboutToBeDestroyed, this, &Game_engine::removeDestroyedBalloon);
}

void Game_engine::spawnBalloon(){

    this->update_balloon_left_box();
    if (!wave_balloons_.isEmpty()){
        QString type = wave_balloons_.takeFirst();
        Balloon* newballoon = nullptr;
        if (type=="Red"){
            newballoon = new Red(map_.get_path());
        }else if (type=="Blue"){
            newballoon = new Blue(map_.get_path());
        }else if (type=="Silver"){
            newballoon = new Silver(map_.get_path());
        }else if (type=="Black"){
            newballoon = new Black(map_.get_path());
        }else if (type=="Boss"){
            newballoon = new Final_boss(map_.get_path());
        }else if (type=="Armor"){
            newballoon = new Armor(map_.get_path());
        }else{
            std::cout << "error" << type.toStdString() << std::endl;
        }
        if (newballoon){
           // std::cout<<newballoon->get_armor_status()<<std::endl;
            balloons_.append(newballoon);
            QPointF start_point = map_.get_startingpoint();
            newballoon->setPos(start_point.x(), start_point.y());
            scene->addItem(newballoon);
            // conncet signal to know when the balloons are destoryed
            connect(newballoon, &Balloon::aboutToBeDestroyed, this, &Game_engine::removeDestroyedBalloon);
        }

    }else{
        //std::cout<<"No more balloons to be added" << std::endl;
        if (balloons_.isEmpty()){
            //std::cout << "wave ended" << std::endl;

            timer_spawn->disconnect();
            if (health_ > 0){
                level_counter ++;
                if (level_counter==7){
                    std::cout << currentPlayerState << std::endl;
                    if (currentPlayerState != Endgame){
                        changePlayerState(Gamewon);

                        QMediaPlayer* mediaPlayer = new QMediaPlayer();
                        QAudioOutput* audioOutput = new QAudioOutput();
                        mediaPlayer->setAudioOutput(audioOutput);
                        mediaPlayer->setSource(QUrl("qrc:/sound/victory.mp3"));
                        audioOutput->setVolume(30);
                        if(mediaPlayer->PlayingState== 1){
                            mediaPlayer->setPosition(0);
                        }
                        mediaPlayer->play();
                        QMessageBox::critical(this, "Game Won", "You have won the game!");
                        delete mediaPlayer;
                        delete audioOutput;
                        delete this;
                    }
                }else{
                changePlayerState(Idle);
                this->updatelevelbox();
                infoText->setPlainText("Nice job level completed");
                }
            }
        }
    }
}

void Game_engine::removeDestroyedBalloon(Balloon *balloon) {
    // Find and remove the destroyed balloon from the vector
    balloons_.removeOne(balloon);
    scene->removeItem(balloon);
    money_ += 1;
    this->updateMoneybox();
}

void Game_engine::on_button_exit_clicked(){
    delete this;
    //this->close();
}

void Game_engine::end_game(){
    timer_spawn->disconnect();
    changePlayerState(Endgame);
    QMessageBox::critical(this, "Game Lost", "Balloon reached end of path");
    delete this;
}
void Game_engine::on_button_basic_shooter_clicked(){

    if (currentPlayerState == Idle) {

        // Assuming Basic_shooter cost is calculated separately
        tower_toplaced = new Basic_shooter();

        if (money_ >= tower_toplaced->Get_cost()) {
            changePlayerState(PlacingTower);
            money_ -= tower_toplaced->Get_cost();
            updateMoneybox();

            // Inform the player to click on a tile to place the tower
            infoText->setPlainText("Click on a tile to place the tower");

        } else {
            delete tower_toplaced;
            infoText->setPlainText("Not enough money to buy the tower");
        }
    } else {
        infoText->setPlainText("Already in tower placement mode \n Click on a tile to place the tower");
    }

}

void Game_engine::on_button_fast_shooter_clicked(){
    if (currentPlayerState == Idle) {
        tower_toplaced = new Fast_shooter();
        if (money_ >= tower_toplaced->Get_cost()) {
            changePlayerState(PlacingTower);
            money_ -= tower_toplaced->Get_cost();
            updateMoneybox();

            // Inform the player to click on a tile to place the tower
            infoText->setPlainText("Click on a tile to place the tower");

        }else {
            delete tower_toplaced;
            infoText->setPlainText("Not enough money to buy the tower");
        }
    }else {
        infoText->setPlainText("Already in tower placement mode \n Click on a tile to place the tower");
    }
}

void Game_engine::on_button_sniper_shooter_clicked(){
    if (currentPlayerState == Idle) {
        tower_toplaced = new Sniper_shooter();
        if (money_ >= tower_toplaced->Get_cost()) {
            changePlayerState(PlacingTower);
            money_ -= tower_toplaced->Get_cost();
            updateMoneybox();
            // Inform the player to click on a tile to place the tower
            infoText->setPlainText("Click on a tile to place the tower");

        } else {
            delete tower_toplaced;
            infoText->setPlainText("Not enough money to buy the tower");
        }
    } else {
        infoText->setPlainText("Already in tower placement mode \n Click on a tile to place the tower");
    }

}

void Game_engine::on_button_freezer_shooter_clicked(){
    if (currentPlayerState == Idle) {
        tower_toplaced = new Freezer_shooter();
        if (money_ >= tower_toplaced->Get_cost()) {
            changePlayerState(PlacingTower);
            money_ -= tower_toplaced->Get_cost();
            updateMoneybox();
            // Inform the player to click on a tile to place the tower
            infoText->setPlainText("Click on a tile to place the tower");

        } else {
            delete tower_toplaced;
            infoText->setPlainText("Not enough money to buy the tower");
        }
    } else {
        infoText->setPlainText("Already in tower placement mode \n Click on a tile to place the tower");
    }

}
void Game_engine::on_button_sell_tower_clicked(){
    if (!towers.isEmpty() && currentPlayerState==Idle){
        this->changePlayerState(SellingTower);
        infoText->setPlainText("Select tower to be removed");
    }else{
        infoText->setPlainText("Buy towers first");
    }
}

void Game_engine::on_button_uppgrade_tower_clicked(){

    if (!towers.isEmpty() && currentPlayerState==Idle){

        if (money_>4){

            this->changePlayerState(UppgradingTower);
            infoText->setPlainText( "select tower to be uppgraded");
        }else{
            infoText->setPlainText( "Not enough money");
        }
    }else{
        infoText->setPlainText( "Buy towers first");
    }

}
void Game_engine::remove_money(int x){
    money_-=x;
}
void Game_engine::mousePressEvent(QMouseEvent *event){
    QGraphicsView::mousePressEvent(event);
    double x=event->scenePosition().x();
    double y = event->scenePosition().y();
    screen_click(x, y);
}

void Game_engine::screen_click(double x, double y){
    if (currentPlayerState == PlacingTower){

        // Convert x and y to int by dividing by 60
        int x_int = static_cast<int>(x / 60);
        int y_int = static_cast<int>(y / 60);

        QPointF itemPosition = tower_toplaced->pos();
        int towerCenterX = itemPosition.x();
        int towerCenterY = itemPosition.y();
        tower_toplaced->create_shooting_ellipse(towerCenterX, towerCenterY);

        if ( x_int < 10 && x_int >= 0 && y_int >= 0 && y_int < 10 ){
            QVector<QVector<Map_tile>>& grid = map_.get_grid();
            if (!grid[y_int][x_int].get_isPath()){
                if (grid[y_int][x_int].get_isFree()){
                    scene->addItem(tower_toplaced);
                    tower_toplaced->setPos(x_int*60,y_int*60);
                    //scene->addItem(shooting_area);
                    scene->addItem(tower_toplaced->Get_shooting_ellipse());
                    tower_toplaced->Get_shooting_ellipse()->setPos(x_int*60,y_int*60);

                    this->updateMoneybox();
                    changePlayerState(Idle);
                    grid[y_int][x_int].set_isFree(false);
                    towers.append(tower_toplaced);

                }else{
                    infoText->setPlainText( "Tile clicked is not free! \n Click on a tile to place the tower");
                }
            }else{
                infoText->setPlainText( "Tile clicked is path, select grass tile");
            }
        }else{
            infoText->setPlainText("Select tile in grid");

        }
    }else if (currentPlayerState == SellingTower){
        int x_int = static_cast<int>(x / 60);
        int y_int = static_cast<int>(y / 60);

        if ( x_int < 10 && x_int >= 0 && y_int >= 0 && y_int < 10 ){
            QVector<QVector<Map_tile>>& grid = map_.get_grid();

            if (!grid[y_int][x_int].get_isFree()){
            // iterate over towers
                for (auto tower:towers){
                     QPointF position = tower->get_center_pos();
                     int x_tower = static_cast<int>(position.x() / 60);
                     int y_tower = static_cast<int>(position.y() / 60);
                     if (x_tower == x_int && y_tower == y_int ){
                        scene->removeItem(tower->Get_shooting_ellipse());
                        scene->removeItem(tower);
                        auto index = towers.indexOf(tower);
                        this->add_money(tower->Get_cost());
                        this->updateMoneybox();
                        delete tower;
                        towers.remove(index);
                        this->changePlayerState(Idle);
                        grid[y_int][x_int].set_isFree(true);
                     }
                }
            }
        }

    }else{
        std::cout << "select tower first" << std::endl;
    }

}
void Game_engine::add_money(int money){
    money_ += money;
}

#endif // GAME_ENGINE_CPP


