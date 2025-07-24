//
// Created by gionimbus on 7/20/25.
//

#ifndef GLOBALMAP_H
#define GLOBALMAP_H


class GlobalMap {
public:
    ~GlobalMap();
    int getValue (int x, int y) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    static GlobalMap& getInstance();
    void initialize (int map_width, int map_height, const int* map_values);
    bool isInitialized() const;

private:
    int width;
    int height;
    int* values; //Map values can be 1 (reachable terrain) or 9 (unreachable terrain)
    bool initialized;

    GlobalMap(): width(0), height(0), values(nullptr), initialized(false) {}
};

#endif //GLOBALMAP_H
