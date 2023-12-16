#ifndef MAP_HPP
#define MAP_HPP

#include <Qvector>
#include <QString>
#include <QPointF>
#include "map_tile.hpp"

// Hpp file for map class used to specify map grid, based on text file
class Map {
public:
    Map(int rows, int cols);
    ~Map();
    void read_path(const QString filename);
    int get_rows();
    int get_cols();
    QVector <QString> get_path();
    QPointF get_startingpoint() const;
    QVector<QVector<Map_tile>>& get_grid();

private:
    QVector<QString> path_;
    int rows_;
    int cols_;
    QPointF startingpoint;
    //int start_row;
    //int start_column;
    QVector<QVector<Map_tile>> grid_;
};

#endif // MAP_HPP
