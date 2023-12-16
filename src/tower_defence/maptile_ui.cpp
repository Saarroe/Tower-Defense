
#include "maptile_ui.hpp"
#include <QPixmap>
#include <QBrush>
#include <iostream>

MapTileGraphics::MapTileGraphics(Map_tile &tile, int x, int y): tile_(tile), x_(x), y_(y), isClicked_(false){
    this->setRect(x_ * 60, y_ * 60, 60, 60);

    this->set_pixmap();
}

void MapTileGraphics::set_pixmap(){

    // if path
    if (tile_.get_isPath()){
        QPixmap pathPixmap1(":/pictures/brick.png");
        QBrush imageBrush1(pathPixmap1.scaled(60,60));
        this->setBrush(imageBrush1);

    }else{
        //std::cout << "grass" << std::endl;
        QPixmap pathPixmap2(":/pictures/grass.png");
        QBrush imageBrush2(pathPixmap2.scaled(60,60));
        this->setBrush(imageBrush2);
    }
}

Map_tile MapTileGraphics::get_tile(){
    return tile_;
}
bool MapTileGraphics::get_isClicked(){
    return isClicked_;
}

void MapTileGraphics::set_clicked(bool x){
    isClicked_ = x;
}



