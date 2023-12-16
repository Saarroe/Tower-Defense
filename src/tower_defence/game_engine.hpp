#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QtGui>
#include <QList>
#include <QPushButton>
#include <iostream>
#include <QPixmap>
#include <QVector>
#include <QMouseEvent>
#include <QTimer>
#include <QString>
#include <QGraphicsEllipseItem>
#include "map.hpp"
#include "maptile_ui.hpp"
#include "balloon.hpp"
#include "defense.hpp"


class Game_engine : public QGraphicsView {
    Q_OBJECT
public:
    Game_engine(QString map_file);
    ~Game_engine();

    enum PlayerState { Idle, PlacingTower, WaveGoing, SellingTower, Endgame, UppgradingTower, Gamewon};
    PlayerState currentPlayerState = Idle;
    void changePlayerState(PlayerState newState);
    void screen_click(double x, double y);
    void init_map();
    void read_levels(const QString filename);
    QGraphicsScene* get_scene(){return scene;};
    QGraphicsEllipseItem * get_shooting_area();
    //PlayerState getPlayerState();
    void add_money(int money);
    void updatelevelbox();
    void update_balloon_left_box();
    void updateMoneybox();
    QVector<Balloon*> get_balloons();
    QTimer *timer_spawn;
    void Boss_destroyed(QPointF position, QVector<QString> path_, int counter);
    void end_game();
    void remove_money(int x);
    void change_infobox(const QString& newText);
private slots:
    //void moveBalloon();
    void on_button_startwave_clicked();
    void on_button_exit_clicked();
    void on_button_basic_shooter_clicked();
    void on_button_fast_shooter_clicked();
    void on_button_sniper_shooter_clicked();
    void on_button_freezer_shooter_clicked();
    void on_button_sell_tower_clicked();
    void spawnBalloon();
    void removeDestroyedBalloon(Balloon *balloon);
    void on_button_uppgrade_tower_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QVector<Defense*> towers;
    Defense * tower_toplaced;
    int money_;
    int health_;
    QGraphicsScene *scene;
    //Balloon *balloon;
    QVector<Balloon*> balloons_;
    QVector<QVector<QString>> all_waves_;
    QVector<QString> wave_balloons_;
    Map map_;
    QGraphicsTextItem *moneyText;
    QGraphicsTextItem *levelText;
    QGraphicsTextItem *balloonsText;
    QGraphicsTextItem *infoText;
    int level_counter;
};

#endif // GAME_ENGINE_HPP
