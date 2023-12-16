#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>


class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Projectile(int speed, QGraphicsItem *parent=0);
    ~Projectile();
    double getPixmapDiameter();
    QTimer *move_timer;
public slots:
    void move();
private:
    int width_;
    int height_;
    int speed_;
};
#endif // PROJECTILE_HPP
