#ifndef BALLOON_HPP
#define BALLOON_HPP


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QTimer>
#include <QVector>
#include "map_tile.hpp"
#include <QString>
#include <QMediaPlayer>


// armor == 0 means no armor, armor == 1 means balloon has armor

class Balloon :public QObject , public QGraphicsPixmapItem  { // inherit QOject...
    Q_OBJECT
    public:
    Balloon(QVector<QString> path, int speed, int hp, int hasArmor, QGraphicsItem* parent = nullptr);
        ~Balloon();
        int Get_hp() const;
        int Get_speed() const;
        void Update_hp(int damage);
       // int get_x_coordinate();
       //int get_y_coordinate();
        QPointF GetPosition() const;
        QPointF GetPosition_attack() const;

//        virtual void has_armor() const=0;

        int get_armor_status() const;

        QTimer *timer;
        bool isDead;
        void set_targeted(bool value);
        bool get_isTarget();
        void destroyBalloon();
        bool get_isSlowed();
        void set_isSlowed(bool x);
        void set_speed(int sp);
        void set_speed_back();
        void remove_armor();
        void set_boss(bool x);
        void set_counter(int counter);
        void set_isSilver(bool x);
        bool get_isSilver();

    signals:
        void aboutToBeDestroyed(Balloon *balloon);

    public slots:
       void moveBalloon();
    protected:
        int speed;
        int hp;
        QVector<QString> path_;
        int counter_;
        bool isTarget;
        int hasArmor_;
        bool isSlowed;
        bool isBoss;
        bool isSilver;
        QMediaPlayer* mediaPlayer;
        QAudioOutput* audioOutput;
        QMediaPlayer* ArmorOff;
        QAudioOutput* ArmorOffOutput;

};



#endif // BALLOON_HPP
