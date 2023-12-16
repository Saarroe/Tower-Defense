#ifndef ARMOR_BALLOON_HPP
#define ARMOR_BALLOON_HPP

#include "balloon.hpp"
#include <iostream>

class Armor :public Balloon{
public:
    Armor(QVector<QString> path, int speed=5, int hp=1, int hasArmor=1) : Balloon(path, speed, hp, hasArmor){
        QPixmap balloonPixmap(":/pictures/armor_balloon.png"); // Adjust the path accordingly
        setPixmap(balloonPixmap.scaled(60, 60));
    }

};



#endif // ARMOR_BALLOON_HPP
