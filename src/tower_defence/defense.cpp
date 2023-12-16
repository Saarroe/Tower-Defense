#include "defense.hpp"
#include "game_engine.hpp"
extern Game_engine *game;

Defense::Defense(int cost, int range, int damage, int firerate,  QGraphicsItem *parent)
    : cost_(cost), range_(range), damage_(damage), has_target_(false), fire_rate_(firerate), isFreezer(false), slower_(0), isUppgraded_(false){

    attacktimer = new QTimer(this);
    connect(attacktimer, &QTimer::timeout, this, &Defense::Attack_target);
}
Defense::~Defense(){
    delete attacktimer;
    delete shooting_ellipse_;
}

int Defense::Get_cost() const{
    return cost_;
}
QGraphicsEllipseItem * Defense::Get_shooting_ellipse()const {
    return shooting_ellipse_;
}
int Defense::get_damage() const{
    return damage_;}

bool Defense::get_has_target() const{
    return has_target_;
}
void Defense::change_has_target(bool state){
    has_target_ = state;

}
void Defense::connect_timer(){
    //connect(attacktimer, &QTimer::timeout, this, &Defense::Attack_target);
    attacktimer->start(fire_rate_);
}

int Defense::get_range() const{
    return range_;
}

void Defense::set_isFreezer(bool x){
    isFreezer = x;
}
void Defense::set_slower(int x){
    slower_ = x;
}
int Defense::get_slower(){
    return slower_;
}

void Defense::uppgrade_slower(){
    slower_ += 5;
}
QPointF Defense::get_center_pos() const {
    QPointF position = this->pos();
    position.setX(position.x() + 30); // Add 30 pixels to the x-coordinate
    position.setY(position.y() + 30); // Add 30 pixels to the y-coordinate
    return position;
}
void Defense::create_shooting_ellipse(int x, int y){
    // Assuming a diameter for the ellipse, adjust as needed
    const int diameter = range_;

    // Calculate the top-left corner coordinates for the ellipse
    int topLeftX = x - (diameter / 2) + 30;
    int topLeftY = y - (diameter / 2) + 30;

    // Create the ellipse centered at (x, y)
    shooting_ellipse_ = new QGraphicsEllipseItem(topLeftX, topLeftY, diameter, diameter);
    shooting_ellipse_->setVisible(false);

}

void Defense::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    shooting_ellipse_->setVisible(!shooting_ellipse_->isVisible());

    if (game->currentPlayerState == Game_engine::UppgradingTower){
        if (!isUppgraded_){
            game->remove_money(5);
            game->updateMoneybox();
            //std::cout << "uppgrade found" << std::endl;
            game->changePlayerState(Game_engine::Idle);
            set_uppgraded(true);
            game->change_infobox("Tower uppgraded");
            if (!isFreezer){

                //std::cout << "uppgraded" << std::endl;
                this->uppgrade_firerate();
            }else{
                //std::cout << "freezer" << std::endl;
                this->uppgrade_slower();
            }
        }else{
            game->changePlayerState(Game_engine::Idle);
            game->change_infobox("Tower was already uppgraded");
        }
    }
}


void Defense::uppgrade_firerate(){
    fire_rate_ -= 100;
//attacktimer->start();
}

void Defense::set_uppgraded(bool x){
    isUppgraded_ = x;
}



