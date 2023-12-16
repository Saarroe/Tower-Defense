#include "sniper_shooter.hpp"
#include <QPixmap>
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QLineF>
#include <iostream>
#include "balloon.hpp"
#include "defense.hpp"
#include "game_engine.hpp"
#include "projectile.hpp"
#include <QMediaPlayer>
#include <QAudioOutput>

extern Game_engine *game;

Sniper_shooter::Sniper_shooter() : Defense(5,500,1, 1500) {
    QPixmap basicTowerPixmap(":/pictures/sniper.png");
    this->setPixmap(basicTowerPixmap.scaled(60, 60));
    collisiontimer = new QTimer(this);
    SniperShooting = new QMediaPlayer();
    SniperShootingOutput = new QAudioOutput();

    // Set the audio output for the player
    SniperShooting->setAudioOutput(SniperShootingOutput);

    // Set the media content for playback
    SniperShooting->setSource(QUrl("qrc:/sound/sniper.mp3"));

    // Set the volume of the audio output
    SniperShootingOutput->setVolume(30);
}

Sniper_shooter::~Sniper_shooter(){
    delete collisiontimer;
    delete SniperShooting;
    delete SniperShootingOutput;
}

void Sniper_shooter::Attack_target(){
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
                if (enemy && enemy->get_isTarget()==false && enemy->get_armor_status() == 1){
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
                //std::cout << "Enemy found "<< std::endl;
                Attack();

            }
        }
    }
}
void Sniper_shooter::checkCollision(){
    //std::cout << "started" << std::endl;
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
        //qreal projectileRadius = projectile -> getPixmapDiameter();
        qreal collisionThreshold = qSqrt(30 * 30 + 30 * 30) + 5;
        // Calculate the distance between the projectile and the balloon
        qreal distance = QLineF(projectilePos, balloonPos).length();
        //std::cout << projectileRadius << std::endl;

        if (distance <= collisionThreshold) {
           // std::cout <<"destroyed" << std::endl;

            target->remove_armor();
            target->set_targeted(false);// remove armor
            game->get_scene()->removeItem(projectile);
            delete projectile; // Free memory associated with the projectile
            collisiontimer->disconnect();
            this->change_has_target(false);
        }
    }
}

void Sniper_shooter::Attack() {

    target->set_targeted(true);
    //std::cout << "Attack started" << std::endl;
    projectile = new Projectile(2);
    projectile->setPos(x()+30, y()+30);

    QLineF ln(QPoint(x()+30, y()+30), target->GetPosition_attack());
    int angle =-1*ln.angle();
    projectile->setRotation(angle);
    SniperShooting->play();
    game->get_scene()->addItem(projectile);

    connect(collisiontimer, &QTimer::timeout, this, &Sniper_shooter::checkCollision);
    collisiontimer->start(5);
}
void Sniper_shooter::stoptimer(){
    collisiontimer->stop();
}

