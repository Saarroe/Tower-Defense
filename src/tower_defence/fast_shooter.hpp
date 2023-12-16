#ifndef FAST_SHOOTER_HPP
#define FAST_SHOOTER_HPP

#include "projectile.hpp"
#include "balloon.hpp"
#include "defense.hpp"
#include <QGraphicsEllipseItem>
#include <QList>

class Fast_shooter :public Defense{
public:

    Fast_shooter();
    ~Fast_shooter() override;
    virtual void Attack() override;
   // virtual void create_shooting_ellipse(int x, int y) override;
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
    QMediaPlayer* FastShooting;
    QAudioOutput* FastOutput;

};
#endif // FAST_SHOOTER_HPP
