#ifndef RED_HPP
#define RED_HPP

#include "balloon.hpp"

class Red :public Balloon{
public:
    Red(QVector<QString> path,  int speed=5, int hp=1, int hasArmor=0) : Balloon(path, speed, hp, hasArmor){
        QPixmap balloonPixmap(":/pictures/red.png"); // Adjust the path accordingly
        setPixmap(balloonPixmap.scaled(60, 60));
    }
};

#endif // RED_HPP
