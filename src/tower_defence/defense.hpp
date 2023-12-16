#ifndef DEFENSE_HPP
#define DEFENSE_HPP

#include <iostream>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>

class Defense : public QObject,  public QGraphicsPixmapItem{ // inherit QOject...
    Q_OBJECT
public:
    Defense(int cost, int range, int damage, int firerate, QGraphicsItem* parent = nullptr);
    virtual ~Defense();
    int Get_cost() const;
    int get_range() const;
    bool get_has_target() const;
    void change_has_target(bool state);
    //std::string& Get_name() const;

    virtual void Attack() = 0;
    virtual void Attack_target() =0;

    void connect_timer();
   // void disconnect_timer();
    int get_damage() const;
    QGraphicsEllipseItem * Get_shooting_ellipse()const;
   // virtual void create_shooting_ellipse(int x, int y) = 0;
    virtual void stoptimer() = 0 ;
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    QList<QGraphicsItem *> colliding_items; // enemies in shooting range

    //uppgrade_range();
    void uppgrade_firerate();
    void uppgrade_slower();
    void set_isFreezer(bool x);

    QTimer *attacktimer;

    QPointF get_center_pos() const;
    void create_shooting_ellipse(int x, int y);
    void set_slower(int x);
    int get_slower();
    void set_uppgraded(bool x);

protected:
    int x_int;
    int y_int;
    int cost_;
    int range_;
    int damage_;
    bool has_target_;
    QGraphicsEllipseItem * shooting_ellipse_;
    int fire_rate_;
    bool isFreezer;
    int slower_;
    bool isUppgraded_;

};


#endif // DEFENSE_HPP
