#include "projectile.hpp"
#include <QPixmap>
#include <QTimer>


Projectile::Projectile(int speed, QGraphicsItem *parent): speed_(speed)
{
    QPixmap pixmap(":pictures/projectile.png");
    setPixmap(pixmap);
    setScale(0.03);
    move_timer = new QTimer(this);
    connect(move_timer, &QTimer::timeout, this, &Projectile::move);
    move_timer->start(speed_);
    QSize pixmapSize = pixmap.size();
    width_ = pixmapSize.width();
    height_ = pixmapSize.height();
}

void Projectile::move(){
    int stepsize=4;
    double theta=rotation();
    double dy =stepsize*qSin(qDegreesToRadians(theta));
    double dx = stepsize*qCos(qDegreesToRadians(theta));
    setPos( x()+dx, y()+dy);
}

Projectile::~Projectile() {
    delete move_timer;
}

double Projectile::getPixmapDiameter() {

    // Calculate the diagonal (hypotenuse) using Pythagorean theorem
    double diameter = std::sqrt(std::pow(width_, 2) + std::pow(height_, 2));

    return diameter;
}
