
#include "map_tile.hpp"



// During init all map_tiles are
Map_tile::Map_tile(QGraphicsItem* parent = nullptr):isFree(false), isPath(false) {

}

bool Map_tile::get_isFree(){
    return isFree;
}
bool Map_tile::get_isPath(){
    return isPath;
}
void Map_tile::set_isPath(bool x){
    isPath = x;
}
void Map_tile::set_isFree(bool x){
    isFree=x;
}


private:
    bool isFree;
    bool isPath;
};
