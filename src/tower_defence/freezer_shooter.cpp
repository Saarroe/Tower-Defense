#include "freezer_shooter.hpp"
#include <QPixmap>
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QLineF>
#include <iostream>
#include "balloon.hpp"
#include "defense.hpp"
#include "game_engine.hpp"
#include "mainwindow.h"

extern Game_engine *game;

Freezer_shooter::Freezer_shooter() : Defense(8,270,0, 500) {
    QPixmap basicTowerPixmap(":/pictures/high.png");
    this->setPixmap(basicTowerPixmap.scaled(60, 60));
    this->set_isFreezer(true);
    this->set_slower(7);
}

void Freezer_shooter::Attack_target(){
    if (game->currentPlayerState == Game_engine::Idle){
        attacktimer -> stop();
        //std::cout << "ended" << std::endl;
    }else{
        //std::cout << "finding target" << std::endl;
        colliding_items = shooting_ellipse_->collidingItems(Qt::IntersectsItemShape);
        double closest_dist = range_ / 2;

        for (size_t i = 0, n = colliding_items.size(); i < n; i++){
            Balloon * enemy = dynamic_cast<Balloon *>(colliding_items[i]);
            if (enemy && enemy->get_isSlowed()==false && enemy->get_isSilver()==false){
                //std::cout << "Enemy slowed" << std::endl;
                enemy->set_isSlowed(true);
                enemy->set_speed(this->get_slower());
            }
        }
        if (!game->get_balloons().isEmpty()){
           // std::cout << "checking range" << std::endl;
            for (auto it : game->get_balloons()){
                if (it->get_isSlowed()){
                QLineF ln(this->get_center_pos(), it->GetPosition_attack());
                double this_dist = ln.length();

                if (this_dist >= closest_dist) {
                    //std::cout << "back to normal" << std::endl;
                    it->set_isSlowed(false);
                    it->set_speed_back(); // Set the speed back to normal
                    }
                }
            }
        }
        }
}


