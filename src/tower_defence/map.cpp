#ifndef MAP_CPP
#define MAP_CPP

#include <QFile>
#include "map.hpp"
#include <QTextStream>
#include <iostream>
#include <QString>

Map::Map(int rows, int cols): rows_(rows) , cols_(cols) {

    grid_.resize(rows_);
    // Init map with only grass tiles (path, free)
    for (int i = 0; i < rows_; ++i) {
        grid_[i].resize(cols_);
        for (int j = 0; j < cols_; ++j) {
            grid_[i][j] = Map_tile(j, i);
        }
    }
}

Map::~Map(){

}

int Map::get_rows(){ return rows_; }

int Map::get_cols(){ return cols_; }

QVector<QVector<Map_tile>>& Map::get_grid(){ return grid_; }

QVector<QString> Map::get_path(){ return path_; }

QPointF Map::get_startingpoint() const{ return startingpoint; }

void Map::read_path(const QString filename){
    QFile file(filename);
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //std::cout << "file not found" << std::endl;
    }
    QTextStream in(&file);
    QString line1 = in.readLine();
    int start_row = line1.toInt();
    QString line2 = in.readLine();
    int start_col = line2.toInt();
    startingpoint.setY(start_row*60);
    startingpoint.setX(start_col*60);
    grid_[start_row][start_col].set_isPath(true);
    // Read the file line by line
    while (!in.atEnd()) {
        QString line = in.readLine();
        std::string stdLine = line.toStdString();
        if (line == "R"){
            start_col++;
            grid_[start_row][start_col].set_isPath(true);
            path_.append("R");
        }else if(line == "L"){
            start_col--;
            grid_[start_row][start_col].set_isPath(true);
            path_.append("L");
        }else if(line == "D"){
            start_row++;
            grid_[start_row][start_col].set_isPath(true);
            path_.append("D");
        }else if(line == "U"){
            start_row--;
            grid_[start_row][start_col].set_isPath(true);
            path_.append("U");
        }else{
            //std::cout << "Error  " << stdLine << std::endl;
        }
    }
}

#endif // MAP_CPP
