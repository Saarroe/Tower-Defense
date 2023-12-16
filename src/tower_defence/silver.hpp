#ifndef SILVER_HPP
#define SILVER_HPP


#include "balloon.hpp"

class Silver :public Balloon{
public:
    Silver(QVector<QString> path, int speed=6, int hp=1, int hasArmor=0) : Balloon(path, speed, hp, hasArmor){
        QPixmap balloonPixmap(":/pictures/silver.png"); // Adjust the path accordingly
        setPixmap(balloonPixmap.scaled(60, 60));
        set_isSilver(true);
    }
};

#endif // SILVER_HPP
