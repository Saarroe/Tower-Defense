#ifndef BASIC_SHOOTER_H
#define BASIC_SHOOTER_H

#include "projectile.hpp"
#include "balloon.hpp"
#include "defense.hpp"
#include <QGraphicsEllipseItem>
#include <QList>

class Basic_shooter :public Defense{
public:

    Basic_shooter();
    ~Basic_shooter() override;
    virtual void Attack() override;

    virtual void Attack_target() override;
    QList<QGraphicsItem *> colliding_items; // enemies in shooting range
    Balloon * target;
    Projectile * projectile;

    QTimer * collisiontimer;
    virtual void stoptimer() override;

private slots:
    void checkCollision();

private:
    int range_size_;
    QPointF attack_point_;
    QMediaPlayer* BasicShooting;
    QAudioOutput* BasicOutput;

};
#endif // BASIC_SHOOTER_H
