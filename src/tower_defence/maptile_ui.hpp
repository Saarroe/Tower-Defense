#ifndef MAPTILE_UI_HPP
#define MAPTILE_UI_HPP

#include <QGraphicsRectItem>
#include <QObject>
#include "map_tile.hpp"
#include <QGraphicsSceneMouseEvent>

class MapTileGraphics :  public QGraphicsRectItem {
    //Q_OBJECT
public:
    MapTileGraphics(Map_tile &tile, int x, int y);

    ~MapTileGraphics(){};
    void set_pixmap();
    void set_clicked(bool x);
    Map_tile get_tile();
    bool get_isClicked();

    //void set_selected();

//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event)
//    {

//        set_selected();
//    }
private:

    Map_tile& tile_;
    int x_;
    int y_;
    bool isClicked_;

};
#endif // MAPTILE_UI_HPP
