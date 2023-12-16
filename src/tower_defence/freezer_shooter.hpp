#ifndef FREEZER_SHOOTER_HPP
#define FREEZER_SHOOTER_HPP

#include "balloon.hpp"
#include "defense.hpp"
#include <QGraphicsEllipseItem>
#include <QList>
#include <QVector>

class Freezer_shooter :public Defense{
public:
    Freezer_shooter();
    ~Freezer_shooter() override {};
    virtual void Attack() override {}
    virtual void Attack_target() override;
    QList<QGraphicsItem *> colliding_items; // enemies in shooting range
    virtual void stoptimer() override {}

private:

};

#endif // FREEZER_SHOOTER_HPP
