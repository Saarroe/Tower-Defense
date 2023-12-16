#ifndef FINAL_BOSS_HPP
#define FINAL_BOSS_HPP

#include "balloon.hpp"

class Final_boss :public Balloon{
public:
    Final_boss(QVector<QString> path, int speed=10, int hp=7, int hasArmor=0) : Balloon(path, speed, hp, hasArmor){
        QPixmap balloonPixmap(":/pictures/boss.png"); // Adjust the path accordingly
        setPixmap(balloonPixmap.scaled(60, 60));
        this->set_boss(true);
    }
};

#endif // FINAL_BOSS_HPP
