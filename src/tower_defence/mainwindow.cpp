#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPalette>
#include <QInputDialog>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "game_engine.hpp"

Game_engine *game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap background(":/pictures/main.png");
    background = background.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
    ui->start_game_btn->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->start_game_btn->setFont(QFont("Arial", 20));

    mediaPlayer = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/sound/background.mp3"));
    audioOutput->setVolume(30);
    if(mediaPlayer->PlayingState== 1){
        mediaPlayer->setPosition(0);
    }
    mediaPlayer->play();
}

MainWindow::~MainWindow()
{
    delete game;
    delete mediaPlayer;
    delete audioOutput;
    delete ui;
}

void MainWindow::on_start_game_btn_clicked(){
    QDir mapsDir(":/maps/");
    QStringList mapFiles = mapsDir.entryList(QStringList() << "*.txt", QDir::Files);
    QString selectedMap = QInputDialog::getItem(this, "Select Map", "Choose a map:", mapFiles, -1, false);

    if (!selectedMap.isEmpty()) {
        // 'selectedMap' contains the chosen map file (e.g., "map1.txt", "map2.txt")
        QMessageBox::information(this, "Selected Map", "You chose: " + selectedMap + "\nGame starting");
        mediaPlayer->stop();
        game = new Game_engine(selectedMap);
        game->show();
    } else {
        QMessageBox::critical(this, "Error", "No map selected!\n Try again to start the game!");
    }
}

