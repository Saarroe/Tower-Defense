#ifndef MAP_TILE_HPP
#define MAP_TILE_HPP


class Map_tile {
public:
    // During init all map_tiles are
    Map_tile(): x_(0), y_(0), isFree(true), isPath(false), isEnd(false){};
    Map_tile(int x, int y): x_(x), y_(y), isFree(true), isPath(false), isEnd(false){};

    ~Map_tile(){};

    bool get_isFree(){
        return isFree;
    }
    bool get_isPath(){
        return isPath;
    }
    bool get_isEnd(){
        return isEnd;
    }
    void set_isPath(bool x){
        isPath = x;
    }
    void set_isFree(bool x){
        isFree=x;
    }
    void set_isEnd(bool x){
        isEnd=x;
    }
    int get_x(){
        return x_;
    }
    int get_y(){
        return x_;
    }
    void set_x(int x){
        x_=x;
    }
    void set_y(int y){
        y_=y;
    }

private:
    int x_;
    int y_;
    bool isFree;
    bool isPath;
    bool isEnd;

};

#endif // MAP_TILE_HPP
