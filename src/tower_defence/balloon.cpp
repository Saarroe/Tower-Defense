#ifndef Balloon_CPP
#define Balloon_CPP

#include "balloon.hpp"
#include "game_engine.hpp"
#include <QPixmap>
#include <QPointF>
#include <QTimer>
#include <iostream>
#include <QVector>
#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>
extern Game_engine *game;

Balloon::Balloon(QVector<QString> path, int speed, int hp, int hasArmor,  QGraphicsItem *parent)
    : path_(path), speed(speed), hp(hp), counter_(0), isTarget(false), hasArmor_(hasArmor), isSlowed(false), isBoss(false), isSilver(false){
    mediaPlayer = new QMediaPlayer();
    audioOutput = new QAudioOutput();

    // Set the audio output for the player
    mediaPlayer->setAudioOutput(audioOutput);

    // Set the media content for playback
    mediaPlayer->setSource(QUrl("qrc:/sound/balloonpop.mp3"));

    // Set the volume of the audio output
    audioOutput->setVolume(15);

    ArmorOff = new QMediaPlayer();
    ArmorOffOutput = new QAudioOutput();

    // Set the audio output for the player
    ArmorOff->setAudioOutput(ArmorOffOutput);

    // Set the media content for playback
    ArmorOff->setSource(QUrl("qrc:/sound/armor.mp3"));

    // Set the volume of the audio output
    ArmorOffOutput->setVolume(30);

    // Create a QTimer to move the balloon
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Balloon::moveBalloon);
    timer->start(speed); // Adjust the interval (in milliseconds) as needed
}

//destructor
Balloon::~Balloon(){
    delete timer;
    delete ArmorOff;
    delete ArmorOffOutput;
    delete mediaPlayer;
    delete audioOutput;
}

int Balloon::Get_hp() const{ return hp; }
int Balloon::Get_speed() const{ return speed; }
int Balloon::get_armor_status() const{ return hasArmor_; }
bool Balloon::get_isSlowed() {return isSlowed;};

void Balloon::set_isSlowed(bool x){isSlowed=x;}

void Balloon::set_isSilver(bool x){ isSilver = x; }

bool Balloon::get_isSilver(){ return isSilver; }

void Balloon::set_speed(int sp){
    int speed2 = speed+sp;
    timer->stop();
    timer->start(speed2);
}

void Balloon::set_speed_back(){
    timer->stop();
    timer->start(speed);
}

void Balloon::remove_armor(){
    ArmorOff->play();
    hasArmor_=0;
    QPixmap balloonPixmap(":/pictures/red.png"); // Adjust the path accordingly
    this->setPixmap(balloonPixmap.scaled(60, 60));
}

void Balloon::set_counter(int counter){
    counter_=counter;
}

void Balloon::Update_hp(int damage){
    hp = hp- damage;
    if(mediaPlayer->PlayingState== 1){
        mediaPlayer->setPosition(0);
    }
    if (hp==0) {
        mediaPlayer->play();
        if (isBoss){
            game->Boss_destroyed(pos(),path_, counter_);
            destroyBalloon();
        }else{
            destroyBalloon();
        }
    }
}

void Balloon::set_boss(bool x){ isBoss = x;}

QPointF Balloon::GetPosition() const {return this->pos();}

QPointF Balloon::GetPosition_attack() const {
    QPointF position = this->pos();
    position.setX(position.x() + 30);
    position.setY(position.y() + 30);
    return position;
}

void Balloon::set_targeted(bool value){ isTarget = value; }

bool Balloon::get_isTarget(){ return isTarget; }

void Balloon::moveBalloon(){
    if (!path_.isEmpty()){
    QPointF currentPos = this->GetPosition();
    QString command = path_.first();
    if (command == "R"){
        this->setPos(currentPos + QPointF(1, 0));
    }else if(command == "L"){
        this->setPos(currentPos + QPointF(-1, 0));

    }else if(command == "D"){
        this->setPos(currentPos + QPointF(0, 1));

    }else if(command == "U"){
        this->setPos(currentPos + QPointF(0, -1));

    }else{
        std::cout<<std::endl;
    }
    counter_ ++;
    if (counter_ == 59){
        path_.removeFirst();
        counter_ = 0;
    }
    } else {
        destroyBalloon();
        std::cout << game->currentPlayerState << std::endl;
        if (game->currentPlayerState != Game_engine::Endgame && game->currentPlayerState != Game_engine::Gamewon){
            game->end_game();
        }
    }
}

void Balloon::destroyBalloon() {
    emit aboutToBeDestroyed(this);
    delete this;
}

#endif // Balloon_CPP
