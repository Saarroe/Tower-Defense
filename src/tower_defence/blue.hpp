#ifndef BLUE_HPP
#define BLUE_HPP


#include "balloon.hpp"


class Blue :public Balloon{
public:
    Blue(QVector<QString> path, int speed=3, int hp=1, int hasArmor=0) : Balloon(path, speed, hp, hasArmor) {
        QPixmap balloonPixmap(":/pictures/blue.png"); // Adjust the path accordingly
        setPixmap(balloonPixmap.scaled(60, 60));
    }
};

#endif // BLUE_HPP
