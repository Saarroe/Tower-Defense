#ifndef BLACK_HPP
#define BLACK_HPP

#include "balloon.hpp"


class Black :public Balloon{
public:
    Black(QVector<QString> path, int speed=7, int hp=2, int hasArmor=0) : Balloon(path, speed, hp, hasArmor){
        QPixmap balloonPixmap(":/pictures/black.png"); // Adjust the path accordingly
        setPixmap(balloonPixmap.scaled(60, 60));
    }
};

#endif // BLACK_HPP
