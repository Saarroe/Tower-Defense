#include <QPixmap>
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QLineF>
#include <iostream>
#include "basic_shooter.hpp"
#include "balloon.hpp"
#include "defense.hpp"
#include "game_engine.hpp"
#include "projectile.hpp"
#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>

extern Game_engine *game;

Basic_shooter::Basic_shooter() : Defense(5,270,1, 1800) { // defense parameters: int cost, int range, int damage, int firerate
    QPixmap basicTowerPixmap(":/pictures/tower.png");
    this->setPixmap(basicTowerPixmap.scaled(60, 60));
    collisiontimer = new QTimer(this);
    BasicShooting = new QMediaPlayer();
    BasicOutput = new QAudioOutput();

    // Set the audio output for the player
    BasicShooting->setAudioOutput(BasicOutput);

    // Set the media content for playback
    BasicShooting->setSource(QUrl("qrc:/sound/shooting.mp3"));

    // Set the volume of the audio output
    BasicOutput->setVolume(70);
}

Basic_shooter::~Basic_shooter(){
    delete collisiontimer;
    delete BasicShooting;
    delete BasicOutput;
}

void Basic_shooter::Attack_target(){
    if (game->currentPlayerState == Game_engine::Idle){
        attacktimer -> stop();
        //std::cout << "ended" << std::endl;
    }else{
        if (!this->get_has_target()){
            //std::cout << "finding target" << std::endl;
            colliding_items = shooting_ellipse_->collidingItems(Qt::IntersectsItemShape);
            double closest_dist = range_ +60;
            for (size_t i = 0, n = colliding_items.size(); i < n; i++){
                Balloon * enemy = dynamic_cast<Balloon *>(colliding_items[i]);
                if (enemy && enemy->get_isTarget()==false && enemy->get_armor_status() == 0){
                    //std::cout << "Enemy found "<< std::endl;
                    QLineF ln(this->get_center_pos(),enemy->GetPosition_attack());
                    double this_dist =  ln.length();
                    if (this_dist < closest_dist){
                        closest_dist = this_dist;
                        target = enemy;
                        this->change_has_target(true); // set to true
                   }
                }
            }
            if (this->get_has_target()) {
               // std::cout << "Enemy found "<< std::endl;
                Attack();
        }
    }
    }
}

void Basic_shooter::checkCollision(){
    QPointF projectilePos = projectile->pos();
    qreal distance_pr = QLineF(projectilePos, this->get_center_pos()).length();
    if (distance_pr > range_){
        //std::cout <<"Missed" << std::endl;
        game->get_scene()->removeItem(projectile);
        delete projectile; // Free memory associated with the projectile
        collisiontimer->disconnect();
        this->change_has_target(false);
        target->set_targeted(false);
    }else{
        QPointF balloonPos = target->GetPosition_attack();
        qreal collisionThreshold = qSqrt(30 * 30 + 30 * 30) + 5;
        // Calculate the distance between the projectile and the balloon
        qreal distance = QLineF(projectilePos, balloonPos).length();
        if (distance <= collisionThreshold) {
            //std::cout <<"destroyed" << std::endl;
            target->set_targeted(false);
            target->Update_hp(get_damage()); // Apply damage to the balloon
            game->get_scene()->removeItem(projectile);
            delete projectile; // Free memory associated with the projectile
            collisiontimer->disconnect();
            this->change_has_target(false);
        }
    }
}

void Basic_shooter::Attack() {
    target->set_targeted(true);
    //std::cout << "Attack started" << std::endl;
    projectile = new Projectile(5);
    projectile->setPos(x()+30, y()+30);
    QLineF ln(QPoint(x()+30, y()+30), target->GetPosition_attack());
    int angle =-1*ln.angle();
    projectile->setRotation(angle);
    BasicShooting->play();
    game->get_scene()->addItem(projectile);
    connect(collisiontimer, &QTimer::timeout, this, &Basic_shooter::checkCollision);
    collisiontimer->start(5);
}

void Basic_shooter::stoptimer(){
    collisiontimer->stop();
}

