#ifndef SNIPER_SHOOTER_HPP
#define SNIPER_SHOOTER_HPP

#include "projectile.hpp"
#include "balloon.hpp"
#include "defense.hpp"
#include <QGraphicsEllipseItem>
#include <QList>

class Sniper_shooter :public Defense{
public:
    Sniper_shooter();
    ~Sniper_shooter() override;
    virtual void Attack() override;
    //virtual void create_shooting_ellipse(int x, int y) override;
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
    QMediaPlayer* SniperShooting;
    QAudioOutput* SniperShootingOutput;

};

#endif // SNIPER_SHOOTER_HPP

